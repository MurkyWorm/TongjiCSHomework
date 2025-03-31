#include "INode.h"
#include "Kernel.h"

Inode::Inode() {
	this->is_changed = false;
	this->i_mode = 0;
	this->i_nlink = 0;
	this->i_number = -1;
	this->i_size = 0;
	for (int i = 0; i < 10; i++) {
		this->i_addr[i] = 0;
	}
}

Inode::~Inode() {
	//do nothing
}

void Inode::ReadI() {
	int lbn; //�ļ��߼����
	int bn; //lbn��Ӧ�������̿��
	int offset; //��ǰ�ַ�������ʼ����λ��
	int nbytes; //������Ŀ�����ֽ�����
	Buf* pBuf;
	State& state = Kernel::Instance().GetState();
	BufferManager& bufferManager = Kernel::Instance().GetBufferManager();

	if (0 == state.IOParam.m_Count) { //��Ҫ�����ֽ�Ϊ0���򷵻�
		return;
	}

	// һ��һ���ַ������ȫ�����ݣ�ֱ���ļ���β
	while (state.IOParam.m_Count != 0) {
		lbn = bn = state.IOParam.m_Offset / Inode::BLOCK_SIZE;
		offset = state.IOParam.m_Offset % Inode::BLOCK_SIZE;
		//�����ֽ�����ȡ����ʣ���ֽ����͵�ǰ�ַ�������Ч�ֽ����Ľ�Сֵ
		nbytes = ((Inode::BLOCK_SIZE - offset) > state.IOParam.m_Count) ? state.IOParam.m_Count : (Inode::BLOCK_SIZE - offset);
	
		int remain = this->i_size - state.IOParam.m_Offset;

		if (remain <= 0) { //����Ѷ��������ļ���β
			return;
		}

		//�����ֽ�����ȡ����ʣ���ļ��ĳ���
		nbytes = (nbytes > remain) ? remain : nbytes;

		//���߼����lbnת���������̿��bn
		if ((bn = this->Bmap(lbn)) == 0) {
			return; //û�ҵ���Ӧ��������
		}
		pBuf = bufferManager.Bread(bn);
		
		unsigned char* start = pBuf->b_addr + offset; //������������ʼ��λ��

		//�����ݴӻ�����������Ŀ������
		for (int i = 0; i < nbytes; i++) {
			*(state.IOParam.m_Base + i) = *(start + i);
		}

		//��nbytes���¶�дλ��
		state.IOParam.m_Base += nbytes;
		state.IOParam.m_Offset += nbytes;
		state.IOParam.m_Count -= nbytes;
	}
}

void Inode::WriteI() {
	int lbn; //�ļ��߼����
	int bn; //lbn��Ӧ�������̿��
	int offset; //��ǰ�ַ�������ʼ�����ַ
	int nbytes; //�����ֽ�����
	Buf* pBuf;
	State& state = Kernel::Instance().GetState();
	BufferManager& bufferManager = Kernel::Instance().GetBufferManager();

	this->is_changed = true;

	if (0 == state.IOParam.m_Count) { //��Ҫ�����ֽ���Ϊ0
		return;
	}

	while (state.IOParam.m_Count != 0) {
		lbn = state.IOParam.m_Offset / Inode::BLOCK_SIZE;
		offset = state.IOParam.m_Offset % Inode::BLOCK_SIZE;
		nbytes = ((Inode::BLOCK_SIZE - offset) > state.IOParam.m_Count) ? state.IOParam.m_Count : (Inode::BLOCK_SIZE - offset);
	
		// ���߼����ת��Ϊ������
		if ((bn = this->Bmap(lbn)) == 0) {
			return;
		}

		if (Inode::BLOCK_SIZE == nbytes) {
			//���д������������һ���ַ��飬��Ϊ����仺��
			pBuf = bufferManager.GetBlk(bn);
		}
		else {
			//д�����ݲ���һ���ַ��飬�ȶ���д
			pBuf = bufferManager.Bread(bn);
		}
		unsigned char* start = (unsigned char*)(pBuf->b_addr + offset); //���������ݵ���ʼдλ��

		//�����ݴ�Ŀ�����򿽱���������
		for (int i = 0; i < nbytes; i++) {
			*(start++) = *(state.IOParam.m_Base + i);
		}

		//��nbytes���¶�дλ��
		state.IOParam.m_Base += nbytes;
		state.IOParam.m_Offset += nbytes;
		state.IOParam.m_Count -= nbytes;

		if (state.IOParam.m_Offset % Inode::BLOCK_SIZE == 0) { //���д��һ���ַ��飬���������
			bufferManager.Bwrite(pBuf);
		}
		else {
			pBuf->is_dirty = true; //��ûд����������Ϊ�֮࣬����д������
		}

		//��ͨ�ļ���������
		if ((this->i_size < state.IOParam.m_Offset)) {
			this->i_size = state.IOParam.m_Offset;
		}
	}
}

int Inode::Bmap(int lbn) {
	Buf* pFirstBuf;
	Buf* pSecondBuf;
	int phyBlkno; //ת����������̿��
	int* iTable; //���ڷ��������̿���һ�μ�ӡ����μ��������
	int index;
	BufferManager& bufferManager = Kernel::Instance().GetBufferManager();
	FileSystem& fileSystem = Kernel::Instance().GetFileSystem();


	if (lbn >= Inode::HUGE_FILE_BLOCK) {
		return 0;
	}

	if (lbn < 6) { //С���ļ�ֱ�Ӵӻ����������ȡ����
		phyBlkno = this->i_addr[lbn];

		//������߼��黹û����֮��Ӧ�������̿�ţ���Ҫ���з���
		if (phyBlkno == 0 && (pFirstBuf = fileSystem.Alloc()) != NULL) {
			phyBlkno = pFirstBuf->b_blkno;
			//���߼���ӳ�䵽�����̿��phyBlkno
			this->i_addr[lbn] = phyBlkno;
			this->is_changed = true;
		}

		return phyBlkno;
	}
	else { //�����ļ����߾����ļ�
		if (lbn < Inode::LARGE_FILE_BLOCK) { //�����ļ�
			index = (lbn - Inode::SMALL_FILE_BLOCK) / Inode::ADDRESS_PER_INDEX_BLOCK + 6;
		}
		else { //�����ļ�
			index = (lbn - Inode::LARGE_FILE_BLOCK) / (Inode::ADDRESS_PER_INDEX_BLOCK * Inode::ADDRESS_PER_INDEX_BLOCK) + 8;
		}

		phyBlkno = this->i_addr[index];
		if (0 == phyBlkno) { //��ʾ��������Ӧ�ļ��������
			this->is_changed = true;
			if ((pFirstBuf = fileSystem.Alloc()) == NULL) { //����һ�������̿��ż��������
				return 0; //����ʧ��
			}
			pFirstBuf->is_dirty = true;
			this->i_addr[index] = pFirstBuf->b_blkno; //��¼���������������̿��
		}
		else {
			pFirstBuf = bufferManager.Bread(phyBlkno);
		}
		iTable = (int*)pFirstBuf->b_addr; //��ȡ�������׵�ַ

		if (index >= 8) { //�����ļ�
			//�Ծ����ļ����ԣ�������ݶ��μ���������ҵ�һ�μ��������
			index = ((lbn - Inode::LARGE_FILE_BLOCK) / Inode::ADDRESS_PER_INDEX_BLOCK) % Inode::ADDRESS_PER_INDEX_BLOCK;
		
			phyBlkno = iTable[index]; //ָ����μ��������
			if (0 == phyBlkno) { //�����ڸ�һ�μ��������
				if ((pSecondBuf = fileSystem.Alloc()) == NULL) { //������̷���ʧ��
					return 0;
				}
				iTable[index] = pSecondBuf->b_blkno; //��һ�μ����������̿�ż�����μ����������Ӧ��
				pFirstBuf->is_dirty = true;
				if (pSecondBuf->b_blkno == 4461) {
					int i = 0;
				}
			}
			else {
				if (phyBlkno == 4461) {
					int i = 0;
				}
				pSecondBuf = bufferManager.Bread(phyBlkno);
			}
			pFirstBuf = pSecondBuf; //��pFirstBufͳһָ��һ��������
			iTable = (int*)pFirstBuf->b_addr;
		}

		//�����߼����lbn����λ��һ�μ���������еı������index
		if (lbn < Inode::LARGE_FILE_BLOCK) {
			index = (lbn - Inode::SMALL_FILE_BLOCK) % Inode::ADDRESS_PER_INDEX_BLOCK;
		}
		else {
			index = (lbn - Inode::LARGE_FILE_BLOCK) % Inode::ADDRESS_PER_INDEX_BLOCK;
		}

		if ((phyBlkno = iTable[index]) == 0 && (pSecondBuf = fileSystem.Alloc()) != NULL) {
			phyBlkno = pSecondBuf->b_blkno; //�����䵽���ļ������̿�ŵǼ���һ�μ����������
			iTable[index] = phyBlkno;
			pFirstBuf->is_dirty = true;
			pSecondBuf->is_dirty = true;
		}

		return phyBlkno;
	}
}

void Inode::IUpdate() {
	Buf* pBuf;
	DiskInode dInode;
	BufferManager& bufferManager = Kernel::Instance().GetBufferManager();

	if (this->is_changed) {
		pBuf = bufferManager.Bread(FileSystem::INODE_ZONE_START_SECTOR + this->i_number / FileSystem::INODE_NUMBER_PER_SECTOR);
		dInode.d_mode = this->i_mode;
		dInode.d_nlink = this->i_nlink;
		dInode.d_size = this->i_size;
		for (int i = 0; i < 10; i++) {
			dInode.d_addr[i] = this->i_addr[i];
		}

		//pָ�򻺴����о����Inode��ƫ��λ��
		unsigned char* p = pBuf->b_addr + (this->i_number % FileSystem::INODE_NUMBER_PER_SECTOR) * sizeof(DiskInode);
		DiskInode* pNode = &dInode;

		//��dInode�е������ݸ��ǻ����еľ����Inode
		for (int i = 0; i < sizeof(DiskInode) / sizeof(unsigned char); i++) {
			*(p + i) = *((unsigned char*)(pNode) + i);
		}
		pBuf->is_dirty = true;
	}
}

void Inode::ITrunc() {
	BufferManager& bufferManager = Kernel::Instance().GetBufferManager();
	FileSystem& fileSystem = Kernel::Instance().GetFileSystem();

	for (int i = 9; i >= 0; i--) {
		//���i_addr[]�еĵ�i�����
		if (this->i_addr[i] != 0) {
			//�����i_addr[]�е�һ�μ�ӡ����μ������
			if (i >= 6 && i <= 9) {
				Buf* pFirstBuf = bufferManager.Bread(this->i_addr[i]); //�������������뻺��
				int* pFirst = (int*)pFirstBuf->b_addr;

				//����ÿ�ż���������128�����̿��
				for (int j = 128 - 1; j >= 0; j--) {
					if (pFirst[j] != 0) { //��������������
						if (i >= 8 && i <= 9) {
							Buf* pSecondBuf = bufferManager.Bread(pFirst[j]);
							int* pSecond = (int*)pSecondBuf->b_addr;

							for (int k = 128 - 1; k >= 0; k--) {
								if (pSecond[k] != 0) {
									fileSystem.Free(pSecond[k]); //�ͷ�ָ���Ĵ��̿�
								}
							}
						}
						fileSystem.Free(pFirst[j]);
					}
				}
			}
			//�ͷ�ֱ�ӵ�����
			fileSystem.Free(this->i_addr[i]);
			this->i_addr[i] = 0;
		}
	}

	this->i_size = 0; //�ļ���С����
	this->is_changed = true; //Inode���޸Ĺ�����Ҫͬ�������
	this->i_nlink = 1;
}

void Inode::Clean() {
	//�ض�����IAllpc()��������·���DIskInode��ԭ�����ݣ������ļ���Ϣ
	this->i_mode = 0;
	this->i_nlink = 0;
	this->i_size = 0;
	for (int i = 0; i < 10; i++) {
		this->i_addr[i] = 0;
	}
}

void Inode::ICopy(Buf* bp, int inumber) {
	DiskInode dInode;
	DiskInode* pNode = &dInode;

	//��pָ�򻺴����б��Ϊinumber���Inode��ƫ��λ��
	unsigned char* p = bp->b_addr + (inumber % FileSystem::INODE_NUMBER_PER_SECTOR) * sizeof(DiskInode);
	//�������е�Inode���ݿ�����dInode��
	//��dInode�е������ݸ��ǻ����еľ����Inode
	for (int i = 0; i < sizeof(DiskInode) / sizeof(unsigned char); i++) {
		*((unsigned char*)(pNode)+i) = *(p + i);
	}

	//���Ƶ��ڴ�Inode��
	this->i_mode = dInode.d_mode;
	this->i_nlink = dInode.d_nlink;
	this->i_size = dInode.d_size;
	for (int i = 0; i < 10; i++) {
		this->i_addr[i] = dInode.d_addr[i];
	}
}

DiskInode::DiskInode() {
	this->d_mode = 0;
	this->d_nlink = 0;
	this->d_size = 0;
	for (int i = 0; i < 10; i++) {
		this->d_addr[i] = 0;
	}
	for (int i = 0; i < 3; i++) {
		this->padding[i] = 0;
	}
}

DiskInode::~DiskInode() {
	//do nothing
}