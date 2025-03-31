#include "OpenFileManager.h"
#include "Kernel.h"

OpenFileTable::OpenFileTable() {
	//do nothing
}

OpenFileTable::~OpenFileTable() {
	//do nothing
}

File* OpenFileTable::FAlloc() {
	int fd;
	State& state = Kernel::Instance().GetState();

	fd = state.ofiles.AllocFreeSlot(); //在打开文件描述符表中获取一个空闲项

	if (fd < 0) { //如果寻找空闲项失败
		return NULL;
	}

	for (int i = 0; i < OpenFileTable::NFILE; i++) {
		if (this->m_File[i].is_av == true) {
			state.ofiles.SetF(fd, &this->m_File[i]);
			this->m_File[i].is_av = false;
			this->m_File[i].f_offset = 0;
			return (&this->m_File[i]);
		}
	}
	return NULL;
}

void OpenFileTable::CloseF(File* pFile) {
	pFile->is_av = true;
}

void OpenFileTable::ResetOpenFileTable() {
	File tmpFile;

	for (int i = 0; i < NFILE; i++) {
		this->m_File[i] = tmpFile;
	}
}

InodeTable::InodeTable() {
	//do nothing
}

InodeTable::~InodeTable() {
	//do nothing
}

Inode* InodeTable::IGet(int inumber) {
	Inode* pInode;

	int index = this->IsLoaded(inumber); //检查编号为inumber的外存Inode是否有内存拷贝
	if (index >= 0) { //找到内存拷贝
		pInode = &(this->m_Inode[index]);
		return pInode;
	}
	else {
		pInode = this->GetFreeInode();
		if (NULL == pInode) { //若内存Inode表已满
			return NULL;
		}
		else { //分配空闲Inode成功，将外存Inode读入新分配的内存Inode
			pInode->i_number = inumber;

			BufferManager& bufferManager = Kernel::Instance().GetBufferManager();
			//将外存Inode读入缓冲区
			Buf* pBuf = bufferManager.Bread(FileSystem::INODE_ZONE_START_SECTOR + inumber / FileSystem::INODE_NUMBER_PER_SECTOR);

			//将缓冲区的外存Inode信息拷贝到内存Inode中
			pInode->ICopy(pBuf, inumber);
			return pInode;
		}
	}
	return NULL; //GCC likes it!
}

void InodeTable::IPut(Inode* pNode) {
	if (pNode->i_number == 1) {
		return;
	}

	FileSystem& fileSystem = Kernel::Instance().GetFileSystem();

	if (pNode->i_nlink <= 0) {
		//释放该文件占据的数据盘块
		pNode->ITrunc();
		pNode->i_mode = 0;
		//释放对应的外存Inode
		fileSystem.IFree(pNode->i_number);
	}

	pNode->IUpdate(); //更新外存Inode信息
	pNode->is_changed = false; //置为未修改过
	pNode->i_number = -1; //内存Inode空闲标志之一
}

void InodeTable::UpdateInodeTable() {
	for (int i = 0; i < InodeTable::NINODE; i++) {
		if (this->m_Inode[i].i_number != -1) {
			this->m_Inode[i].IUpdate();
		}
	}
}

int InodeTable::IsLoaded(int inumber) {
	for (int i = 0; i < InodeTable::NINODE; i++) {
		if (this->m_Inode[i].i_number == inumber) {
			return i;
		}
	}
	return -1;
}

Inode* InodeTable::GetFreeInode() {
	for (int i = 0; i < InodeTable::NINODE; i++) {
		if (this->m_Inode[i].i_number == -1) {
			return &(this->m_Inode[i]);
		}
	}
	return NULL;
}

void InodeTable::ResetInodeTable() {
	Inode tmpInode;

	for (int i = 0; i < NINODE; i++) {
		this->m_Inode[i] = tmpInode;
	}
}