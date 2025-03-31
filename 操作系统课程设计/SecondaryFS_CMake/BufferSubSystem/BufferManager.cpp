#include "BufferManager.h"
#include "Kernel.h"

BufferManager::BufferManager() {
	this->usedBufNum = 0;
	for (int i = 0; i < NBUF; i++) {
		this->m_Buf[i].is_dirty = false;
		this->m_Buf[i].is_new = false;
		this->m_Buf[i].b_addr = this->Buffer[i];
		this->m_Buf[i].b_blkno = -1; //��ʾ��û�ж�Ӧ�Ĵ��̿�
	}
}

BufferManager::~BufferManager() {
	//do nothing
}

Buf* BufferManager::GetBlk(int blkno) {
	DiskManager& diskManager = Kernel::Instance().GetDiskManager();
	//���ÿ��Ƿ��Ѿ��������˻���
	for (int i = 0; i < NBUF; i++) {
		if (this->m_Buf[i].b_blkno == blkno) {
			for (int j = 0; j < this->usedBufNum; j++) {
				int tmp = this->bufQueue.front();
				this->bufQueue.pop();
				if (tmp != i) {
					this->bufQueue.push(tmp);
				}
			}
			this->bufQueue.push(i);
			return &(this->m_Buf[i]);
		}
	}

	//���û�������·����
	if (this->usedBufNum < NBUF) { //����δ������Ļ���
		for (int i = 0; i < NBUF; i++) {
			if (this->m_Buf[i].b_blkno == -1) {
				this->m_Buf[i].b_blkno = blkno;
				this->m_Buf[i].is_dirty = true;
				this->m_Buf[i].is_new = true;
				this->bufQueue.push(i);
				this->usedBufNum++;
				return &(this->m_Buf[i]);
			}
		}
	}
	else { //��������Ѿ����꣬������̭
		int eliminateBufId = this->bufQueue.front();
		this->bufQueue.pop(); //ժ�����׻���

		if (m_Buf[eliminateBufId].is_dirty) { //����ÿ��࣬����д��
			diskManager.seekOneBlock(m_Buf[eliminateBufId].b_blkno);
			diskManager.writeOneBlock(m_Buf[eliminateBufId].b_addr);
		}

		this->m_Buf[eliminateBufId].b_blkno = blkno;
		this->m_Buf[eliminateBufId].is_dirty = true;
		this->m_Buf[eliminateBufId].is_new = true;
		this->bufQueue.push(eliminateBufId); //������µĿ�
		return &(this->m_Buf[eliminateBufId]);
	}

	return NULL;
}

Buf* BufferManager::Bread(int blkno) {
	Buf* bp;
	DiskManager& diskManager = Kernel::Instance().GetDiskManager();

	bp = this->GetBlk(blkno); //�����ַ�������뻺��

	if (bp->is_new == false) { //��������·���Ŀ�
		return bp;
	}
	else { //������·���Ŀ�
		diskManager.seekOneBlock(blkno);
		diskManager.readOneBlock(bp->b_addr);
		bp->is_new = false;
		bp->is_dirty = false;
		return bp;
	}
}

void BufferManager::Bwrite(Buf* bp) {
	DiskManager& diskManager = Kernel::Instance().GetDiskManager();
	if (bp->is_dirty == false) { //����û��治��
		return;
	}
	else {
		diskManager.seekOneBlock(bp->b_blkno);
		diskManager.writeOneBlock(bp->b_addr);
		bp->is_dirty = false;
	}
}

void BufferManager::Bflush() {
	DiskManager& diskManager = Kernel::Instance().GetDiskManager();
	for (int i = 0; i < NBUF; i++) {
		if (this->m_Buf[i].b_blkno == -1 || this->m_Buf[i].is_dirty == false) {
			continue;
		}
		else {
			diskManager.seekOneBlock(this->m_Buf[i].b_blkno);
			diskManager.writeOneBlock(this->m_Buf[i].b_addr);
			this->m_Buf[i].is_dirty = false;
		}
	}
}

void BufferManager::ResetBufferManager() {
	this->usedBufNum = 0;
	for (int i = 0; i < NBUF; i++) {
		this->m_Buf[i].is_dirty = false;
		this->m_Buf[i].is_new = false;
		this->m_Buf[i].b_addr = this->Buffer[i];
		this->m_Buf[i].b_blkno = -1; //��ʾ��û�ж�Ӧ�Ĵ��̿�
	}
	while (!bufQueue.empty()) {
		bufQueue.pop();
	}
}