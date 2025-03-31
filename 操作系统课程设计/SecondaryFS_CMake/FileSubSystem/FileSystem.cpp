#include "FileSystem.h"
#include "Kernel.h"

SuperBlock::SuperBlock() {
	this->s_isize = FileSystem::INODE_SIZE;
	this->s_fsize = 18000;
	this->s_nfree = 0;
	this->s_ninode = 0;
	for (int i = 0; i < 100; i++) {
		this->s_free[i] = 0;
		this->s_inode[i] = 0;
	}
	this->s_fmod = 0;
	for (int i = 0; i < 51; i++) {
		padding[i] = 0;
	}
}

SuperBlock::~SuperBlock() {
	//do nothing
}

void SuperBlock::ResetSuperBlock() {
	this->s_isize = FileSystem::INODE_SIZE;
	this->s_fsize = 18000;
	this->s_nfree = 0;
	this->s_ninode = 0;
	for (int i = 0; i < 100; i++) {
		this->s_free[i] = 0;
		this->s_inode[i] = 0;
	}
	this->s_fmod = 0;
	for (int i = 0; i < 51; i++) {
		padding[i] = 0;
	}
}

FileSystem::FileSystem() {
	//do nothing
}

FileSystem::~FileSystem() {
	//do nothing
}

void FileSystem::LoadSuperBlock() {
	BufferManager& bufferManager = Kernel::Instance().GetBufferManager();
	SuperBlock& superBlock = Kernel::Instance().GetSuperBlock();

	Buf* pBuf;

	for (int i = 0; i < 2; i++) {
		unsigned char* p = (unsigned char*)(&superBlock) + i * 512;

		pBuf = bufferManager.Bread(FileSystem::SUPER_BLOCK_SECTOR_NUMBER + i);

		//拷贝到内存
		for (int i = 0; i < 512; i++) {
			*(p + i) = *(pBuf->b_addr + i);
		}
	}
}

void FileSystem::Update() {
	Buf* pBuf;
	BufferManager& bufferManager = Kernel::Instance().GetBufferManager();
	SuperBlock& superBlock = Kernel::Instance().GetSuperBlock();
	InodeTable& inodeTable = Kernel::Instance().GetInodeTable();

	//同步SuperBlock到磁盘
	if (superBlock.s_fmod == 0) { //如果内存副本没有被修改过
		return;
	}

	superBlock.s_fmod = 0; //清修改标志

	//执行写入操作
	for (int i = 0; i < 2; i++) {
		unsigned char* p = (unsigned char*)(&superBlock) + i * 512;

		pBuf = bufferManager.GetBlk(FileSystem::SUPER_BLOCK_SECTOR_NUMBER + i);

		for (int i = 0; i < 512; i++) {
			*(pBuf->b_addr + i) = *(p + i);
		}

		bufferManager.Bwrite(pBuf);
	}

	inodeTable.UpdateInodeTable();

	bufferManager.Bflush(); //将延迟写的缓存块写到磁盘上
}

Inode* FileSystem::IAlloc() {
	Buf* pBuf;
	Inode* pNode;
	BufferManager& bufferManager = Kernel::Instance().GetBufferManager();
	SuperBlock& superBlock = Kernel::Instance().GetSuperBlock();
	InodeTable& inodeTable = Kernel::Instance().GetInodeTable();
	int ino; //分配到的空闲外存的编号

	//如果SuperBlock直接管理的空闲Inode索引表已空
	if (superBlock.s_ninode <= 0) {
		ino = 0; //外存编号从1开始

		//依次读入磁盘Inode区中的磁盘块，搜索空闲外存，记入空闲Inode索引表
		for (int i = 0; i < superBlock.s_isize; i++) {
			pBuf = bufferManager.Bread(FileSystem::INODE_ZONE_START_SECTOR + i);
		
			int* p = (int*)pBuf->b_addr; //获取缓冲区首址

			//检查缓冲区中每个外存Inode的i_mode是否不为0，表明已被占用
			for (int j = 0; j < FileSystem::INODE_NUMBER_PER_SECTOR; j++) {
				ino++;

				int mode = *(p + j * sizeof(DiskInode) / sizeof(int));

				if (mode != 0) {
					continue;
				}

				//还要检查是否是内存Inode还未写到外存
				if (inodeTable.IsLoaded(ino) == -1) {
					//若没有，则记入
					superBlock.s_inode[superBlock.s_ninode++] = ino;

					//如果空闲索引表已经装满，则不继续搜索
					if (superBlock.s_ninode >= 100) {
						break;
					}
				}
			}
			if (superBlock.s_ninode >= 100) {
				break;
			}
		}

		//若磁盘没有可用的外存Inode
		if (superBlock.s_ninode <= 0) {
			return NULL;
		}
	}

	//获取空闲Inode
	while (true) {
		ino = superBlock.s_inode[--superBlock.s_ninode];

		pNode = inodeTable.IGet(ino); //将空闲Inode读入内存

		//如果未能分配到内存
		if (NULL == pNode) {
			return NULL;
		}

		//如果该Inode空闲，清空Inode中的数据
		if (0 == pNode->i_mode) {
			pNode->Clean();
			superBlock.s_fmod = 1;
			return pNode;
		}
		else {
			inodeTable.IPut(pNode);
			continue;
		}
	}
	return NULL; //GCC likes it!
}

void FileSystem::IFree(int number) {
	SuperBlock& superBlock = Kernel::Instance().GetSuperBlock();

	if (superBlock.s_ninode >= 100) {
		return;
	}

	superBlock.s_inode[superBlock.s_ninode++] = number;

	superBlock.s_fmod = 1;
}

Buf* FileSystem::Alloc() {
	int blkno;
	Buf* pBuf;
	BufferManager& bufferManager = Kernel::Instance().GetBufferManager();
	SuperBlock& superBlock = Kernel::Instance().GetSuperBlock();

	blkno = superBlock.s_free[--superBlock.s_nfree];

	if (0 == blkno) { //已分配尽所有空闲磁盘
		superBlock.s_nfree = 0;
		return NULL;
	}
	
	if (superBlock.s_nfree <= 0) { //直接管理的空闲盘块为空
		pBuf = bufferManager.Bread(blkno); //读进对应的缓存块

		int* p = (int*)pBuf->b_addr; //用p指向存储上一个100块的位置

		superBlock.s_nfree = *p++; // 先读出空闲盘块数

		for (int i = 0; i < 100; i++) { //填充空闲磁盘栈
			superBlock.s_free[i] = *(p + i);
		}
	}

	//普通情况分配到一空闲磁盘
	pBuf = bufferManager.GetBlk(blkno); //为该磁盘申请缓存
	for (int i = 0; i < 128; i++) {
		*((int*)(pBuf->b_addr) + i) = 0;
	}
	if (blkno == 4461) {
		int i = 0;
	}
	pBuf->is_dirty = true;
	superBlock.s_fmod = 1; //设置SuperBlock被修改标志

	return pBuf;
}

void FileSystem::Free(int blkno) {
	Buf* pBuf;
	BufferManager& bufferManager = Kernel::Instance().GetBufferManager();
	SuperBlock& superBlock = Kernel::Instance().GetSuperBlock();

	superBlock.s_fmod = 1; //设置SuperBlock被修改标志

	//如果之前系统中没有空闲盘块
	if (superBlock.s_nfree <= 0) {
		superBlock.s_nfree = 1;
		superBlock.s_free[0] = 0;
	}

	//如果SuperBlock直接管理的空闲磁盘块号的栈已满
	if (superBlock.s_nfree >= 100) {
		pBuf = bufferManager.GetBlk(blkno);

		int* p = (int*)pBuf->b_addr;

		*p++ = superBlock.s_nfree;

		for (int i = 0; i < 100; i++) {
			*(p + i) = superBlock.s_free[i];
		}

		superBlock.s_nfree = 0;

		bufferManager.Bwrite(pBuf);
	}
	superBlock.s_free[superBlock.s_nfree++] = blkno;
}