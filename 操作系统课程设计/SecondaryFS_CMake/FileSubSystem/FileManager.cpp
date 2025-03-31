#define _CRT_SECURE_NO_WARNINGS
#include "FileManager.h"
#include "Kernel.h"
#include "cstring"

FileManager::FileManager() {
	//do nothing
}

FileManager::~FileManager() {
	//do nothing
}

void FileManager::FormatSystem() {
	BufferManager& bufferManager = Kernel::Instance().GetBufferManager();
	DiskManager& diskManager = Kernel::Instance().GetDiskManager();
	FileManager& fileManager = Kernel::Instance().GetFileManager();
	FileSystem& fileSystem = Kernel::Instance().GetFileSystem();
	State& state = Kernel::Instance().GetState();
	OpenFileTable& openFIleTable = Kernel::Instance().GetOpenFileTable();
	InodeTable& inodeTable = Kernel::Instance().GetInodeTable();
	SuperBlock& superBlock = Kernel::Instance().GetSuperBlock();
	Space& space = Kernel::Instance().GetSpace();

	//重置所有数据结构中的内容
	bufferManager.ResetBufferManager();
	fileManager.ResetFileManager();
	state.ResetState();
	openFIleTable.ResetOpenFileTable();
	inodeTable.ResetInodeTable();
	superBlock.ResetSuperBlock();
	space.ResetSpace();

	//清空整个磁盘
	unsigned char buffer[512];
	for (int i = 0; i < 512; i++) {
		buffer[i] = 0;
	}
	for (int i = 0; i < 18000; i++) {
		diskManager.seekOneBlock(i);
		diskManager.writeOneBlock(buffer);
	}

	//初始化磁盘上的Inode
	//#1号Inode
	Inode* pInode = inodeTable.GetFreeInode();
	pInode->is_changed = true;
	pInode->i_mode = 2;
	pInode->i_nlink = 1;
	pInode->i_number = 1;
	pInode->i_size = 7 * 32;
	pInode->i_addr[0] = 1024;
	//#2号Inode
	pInode = inodeTable.GetFreeInode();
	pInode->is_changed = true;
	pInode->i_mode = 2;
	pInode->i_nlink = 1;
	pInode->i_number = 2;
	pInode->i_size = 2 * 32;
	pInode->i_addr[0] = 1025;
	//#3号Inode
	pInode = inodeTable.GetFreeInode();
	pInode->is_changed = true;
	pInode->i_mode = 2;
	pInode->i_nlink = 1;
	pInode->i_number = 3;
	pInode->i_size = 2 * 32;
	pInode->i_addr[0] = 1026;
	//#4号Inode
	pInode = inodeTable.GetFreeInode();
	pInode->is_changed = true;
	pInode->i_mode = 2;
	pInode->i_nlink = 1;
	pInode->i_number = 4;
	pInode->i_size = 3 * 32;
	pInode->i_addr[0] = 1027;
	//#5号Inode
	pInode = inodeTable.GetFreeInode();
	pInode->is_changed = true;
	pInode->i_mode = 2;
	pInode->i_nlink = 1;
	pInode->i_number = 5;
	pInode->i_size = 2 * 32;
	pInode->i_addr[0] = 1028;
	//#6号Inode
	pInode = inodeTable.GetFreeInode();
	pInode->is_changed = true;
	pInode->i_mode = 1;
	pInode->i_nlink = 1;
	pInode->i_number = 6;
	pInode->i_size = 8 * 512;
	for (int i = 0; i < 7; i++) {
		pInode->i_addr[i] = 1029 + i;
	}
	//#7号Inode
	pInode = inodeTable.GetFreeInode();
	pInode->is_changed = true;
	pInode->i_mode = 1;
	pInode->i_nlink = 1;
	pInode->i_number = 7;

	//初始化数据块
	DirectoryEntry directoryEntry;
	int* p = (int*)(&directoryEntry); //指向内存中的临时目录项，便于写入缓存
	Buf* pBuffer;
	//1024#扇区
	directoryEntry.m_ino = 1;
	std::strcpy(directoryEntry.m_name, ".");
	pBuffer = bufferManager.GetBlk(1024);
	for (int i = 0; i < 8; i++) {
		*((int*)pBuffer->b_addr + i) = *(p + i);
	} //.\0
	directoryEntry.m_ino = 1;
	std::strcpy(directoryEntry.m_name, "..");
	pBuffer = bufferManager.GetBlk(1024);
	for (int i = 0; i < 8; i++) {
		*((int*)pBuffer->b_addr + i + 8) = *(p + i);
	} //..\0
	directoryEntry.m_ino = 2;
	std::strcpy(directoryEntry.m_name, "bin");
	pBuffer = bufferManager.GetBlk(1024);
	for (int i = 0; i < 8; i++) {
		*((int*)pBuffer->b_addr + i + 16) = *(p + i);
	} //bin\0
	directoryEntry.m_ino = 3;
	std::strcpy(directoryEntry.m_name, "etc");
	pBuffer = bufferManager.GetBlk(1024);
	for (int i = 0; i < 8; i++) {
		*((int*)pBuffer->b_addr + i + 24) = *(p + i);
	} //etc\0
	directoryEntry.m_ino = 4;
	std::strcpy(directoryEntry.m_name, "dev");
	pBuffer = bufferManager.GetBlk(1024);
	for (int i = 0; i < 8; i++) {
		*((int*)pBuffer->b_addr + i + 32) = *(p + i);
	} //dev\0
	directoryEntry.m_ino = 5;
	std::strcpy(directoryEntry.m_name, "home");
	pBuffer = bufferManager.GetBlk(1024);
	for (int i = 0; i < 8; i++) {
		*((int*)pBuffer->b_addr + i + 40) = *(p + i);
	}//home\0
	directoryEntry.m_ino = 6;
	std::strcpy(directoryEntry.m_name, "shell");
	pBuffer = bufferManager.GetBlk(1024);
	for (int i = 0; i < 8; i++) {
		*((int*)pBuffer->b_addr + i + 48) = *(p + i);
	} //shell\0
	//1025#扇区
	directoryEntry.m_ino = 2;
	std::strcpy(directoryEntry.m_name, ".");
	pBuffer = bufferManager.GetBlk(1025);
	for (int i = 0; i < 8; i++) {
		*((int*)pBuffer->b_addr + i) = *(p + i);
	} //.\0
	directoryEntry.m_ino = 1;
	std::strcpy(directoryEntry.m_name, "..");
	pBuffer = bufferManager.GetBlk(1025);
	for (int i = 0; i < 8; i++) {
		*((int*)pBuffer->b_addr + i + 8) = *(p + i);
	} //..\0
	//1026#扇区
	directoryEntry.m_ino = 3;
	std::strcpy(directoryEntry.m_name, ".");
	pBuffer = bufferManager.GetBlk(1026);
	for (int i = 0; i < 8; i++) {
		*((int*)pBuffer->b_addr + i) = *(p + i);
	} //.\0
	directoryEntry.m_ino = 1;
	std::strcpy(directoryEntry.m_name, "..");
	pBuffer = bufferManager.GetBlk(1026);
	for (int i = 0; i < 8; i++) {
		*((int*)pBuffer->b_addr + i + 8) = *(p + i);
	} //..\0
	//1027#扇区
	directoryEntry.m_ino = 4;
	std::strcpy(directoryEntry.m_name, ".");
	pBuffer = bufferManager.GetBlk(1027);
	for (int i = 0; i < 8; i++) {
		*((int*)pBuffer->b_addr + i) = *(p + i);
	} //.\0
	directoryEntry.m_ino = 1;
	std::strcpy(directoryEntry.m_name, "..");
	pBuffer = bufferManager.GetBlk(1027);
	for (int i = 0; i < 8; i++) {
		*((int*)pBuffer->b_addr + i + 8) = *(p + i);
	} //..\0
	directoryEntry.m_ino = 7;
	std::strcpy(directoryEntry.m_name, "tty1");
	pBuffer = bufferManager.GetBlk(1027);
	for (int i = 0; i < 8; i++) {
		*((int*)pBuffer->b_addr + i + 16) = *(p + i);
	} //tty1\0
	//1028#扇区
	directoryEntry.m_ino = 5;
	std::strcpy(directoryEntry.m_name, ".");
	pBuffer = bufferManager.GetBlk(1028);
	for (int i = 0; i < 8; i++) {
		*((int*)pBuffer->b_addr + i) = *(p + i);
	} //.\0
	directoryEntry.m_ino = 1;
	std::strcpy(directoryEntry.m_name, "..");
	pBuffer = bufferManager.GetBlk(1028);
	for (int i = 0; i < 8; i++) {
		*((int*)pBuffer->b_addr + i + 8) = *(p + i);
	} //..\0
	//1035扇区
	pBuffer = bufferManager.GetBlk(1035);
	*((int*)pBuffer->b_addr) = 1036;
	*((int*)pBuffer->b_addr) = 1037;

	//将100个空闲inode号送入空闲inode号栈
	superBlock.s_ninode = 100;
	for (int i = 0; i < 100; i++) {
		superBlock.s_inode[i] = i + 8;
	}

	//将空闲盘块收入空闲盘块索引表
	for (int i = 11; i <= 179; i++) {
		pBuffer = bufferManager.GetBlk(i * 100);
		*((int*)pBuffer->b_addr) = 100;
		for (int j = 1; j < 101; j++) {
			*((int*)pBuffer->b_addr + j) = (i + 1) * 100 - j + 1;
		}
	}
	*((int*)pBuffer->b_addr + 1) = 0;
	superBlock.s_nfree = 63;
	for (int i = 0; i < 63; i++) {
		superBlock.s_free[i] = 1100 - i;
	}

	//置superBlock修改标志
	superBlock.s_fmod = 1;

	//将修改更新到磁盘
	fileSystem.Update();
}

void FileManager::ResetFileManager() {
	this->rootDirInode = NULL;
}

void FileManager::Open() {
	Inode* pInode;
	State& state = Kernel::Instance().GetState();

	pInode = this->NameI(NextChar, FileManager::OPEN);
	//如果没有找到对应的Inode
	if (NULL == pInode) {
		return;
	}
	this->Open1(pInode, 0);
}

void FileManager::Creat() {
	Inode* pInode;
	State& state = Kernel::Instance().GetState();

	//搜索目录的模式为1，表示创建；若父目录不可写，出错返回
	pInode = this->NameI(NextChar, FileManager::CREATE);
	//没有找到相应的Inode或者NameI出错
	if (NULL == pInode) {
		pInode = this->MakNode(1);
		if (NULL == pInode) {
			return;
		}
		this->Open1(pInode, 2);
	}
	else {
		this->Open1(pInode, 1);
		pInode->i_mode = 1;
	}
}

void FileManager::Open1(Inode* pInode, int trf) {
	State& state = Kernel::Instance().GetState();
	OpenFileTable& openFIleTable = Kernel::Instance().GetOpenFileTable();
	InodeTable& inodeTable = Kernel::Instance().GetInodeTable();

	if (1 == trf) { //如果要创建的文件已经存在
		pInode->ITrunc();
	}

	//分配File结构
	File* pFile = openFIleTable.FAlloc();
	if (NULL == pFile) {
		inodeTable.IPut(pInode);
		return;
	}
	pFile->is_av = false;
	pFile->f_inode = pInode;
}

void FileManager::Close() {
	State& state = Kernel::Instance().GetState();
	OpenFileTable& openFileTable = Kernel::Instance().GetOpenFileTable();
	int fd = state.arg[0];

	//获取打开文件控制块File结构
	File* pFile = state.ofiles.GetF(fd);
	if (NULL == pFile) {
		return;
	}

	//释放打开文件描述符fd，递减File结构引用计数
	state.ofiles.SetF(fd, NULL);
	openFileTable.CloseF(pFile);
}

void FileManager::Seek() {
	File* pFile;
	State& state = Kernel::Instance().GetState();
	int fd = state.arg[0];

	pFile = state.ofiles.GetF(fd);
	if (NULL == pFile) {
		return; //若FIle不存在
	}

	int offset = state.arg[1];

	//如果state.arg[2]在3-5之间，则长度单位由字节变为512字节
	if (state.arg[2] > 2) {
		offset = offset << 9;
		state.arg[2] -= 3;
	}

	switch (state.arg[2]) {
	//读写位置设置为offset
	case 0:
		pFile->f_offset = offset;
		break;
	//读写位置加offset
	case 1:
		pFile->f_offset += offset;
		break;
	//读写位置调整为文件长度加offsest
	case 2:
		pFile->f_offset = pFile->f_inode->i_size + offset;
		break;
	}
}

void FileManager::FStat() {
	File* pFile;
	State& state = Kernel::Instance().GetState();
	int fd = state.arg[0];

	pFile = state.ofiles.GetF(fd);
	if (NULL == pFile) {
		return;
	}
	this->Stat1(pFile->f_inode, state.arg[1]);
}

void FileManager::Stat() {
	Inode* pInode;
	State& state = Kernel::Instance().GetState();
	InodeTable& inodeTable = Kernel::Instance().GetInodeTable();

	pInode = this->NameI(NextChar, FileManager::OPEN);
	if (NULL == pInode) {
		return;
	}
	this->Stat1(pInode, state.arg[1]);
	inodeTable.IPut(pInode);
}

void FileManager::Stat1(Inode* pInode, unsigned long long statBuf) {
	Buf* pBuf;
	BufferManager& bufferManager = Kernel::Instance().GetBufferManager();

	pInode->IUpdate();
	pBuf = bufferManager.Bread(FileSystem::INODE_ZONE_START_SECTOR + pInode->i_number / FileSystem::INODE_NUMBER_PER_SECTOR);

	unsigned char* p = pBuf->b_addr + (pInode->i_number % FileSystem::INODE_NUMBER_PER_SECTOR) * sizeof(DiskInode);
	for (int i = 0; i < sizeof(DiskInode) / sizeof(int); i++) {
		*((int*)statBuf + i) = *(p + i);
	}
}

void FileManager::Read() {
	this->Rdwr(1);
}

void FileManager::Write() {
	this->Rdwr(2);
}

void FileManager::Rdwr(int mode) {
	File* pFile;
	State& state = Kernel::Instance().GetState();
	Space& space = Kernel::Instance().GetSpace();

	//根据系统调用的参数fd获取打开文件结构的控制块
	pFile = state.ofiles.GetF(state.arg[0]);
	if (NULL == pFile) {
		//不存在该打开文件
		return;
	}

	state.IOParam.m_Base = space.buffer;
	state.IOParam.m_Count = state.arg[1]; //要求读写的字节

	//进行文件的读写
	state.IOParam.m_Offset = pFile->f_offset;
	if (mode == 1) {
		pFile->f_inode->ReadI();
	}
	else {
		pFile->f_inode->WriteI();
	}
	//根据读写字数，移动文件读写偏移指针
	pFile->f_offset += state.arg[1] - state.IOParam.m_Count;
}

Inode* FileManager::NameI(char (*func)(), enum DirectorySearchMode mode) {
	Inode* pInode;
	Buf* pBuf;
	char curchar;
	char* pChar;
	int freeEntryOffset; //创建文件模式搜索目录时，记录空闲目录项的偏移量
	State& state = Kernel::Instance().GetState();
	BufferManager& bufferManager = Kernel::Instance().GetBufferManager();
	InodeTable& inodeTable = Kernel::Instance().GetInodeTable();

	//如果路径以'/'开头，则从根目录开始搜索
	pInode = state.cdir;
	if ('/' == (curchar = (*func)())) {
		pInode = this->rootDirInode;
	}

	//检查该Inode是否正在正常使用
	inodeTable.IGet(pInode->i_number);

	//允许出现////a//b 这种路径 这种路径等价于/a/b
	while ('/' == curchar) {
		curchar = (*func)();
	}

	//如果试图更改或删除当前目录文件则出错
	if ('\0' == curchar && mode != FileManager::OPEN) {
		goto out;
	}

	//外层循环每次处理pathname中一段路径分量
	while (true) {
		//整个路径搜索完毕
		if ('\0' == curchar) {
			return pInode;
		}

		//如果要进行搜索的不是目录文件，释放相关资源后退出
		if (pInode->i_mode != 2) {
			break;
		}

		//将当前准备进行匹配的路径分量拷贝到state中,便于和目录项进行比较
		pChar = &(state.dbuf[0]);
		while ('/' != curchar && '\0' != curchar) {
			if (pChar < &(state.dbuf[DirectoryEntry::DIRSIZE])) {
				*pChar = curchar;
				pChar++;
			}
			curchar = (*func)();
		}
		//将dbuf中剩余的部分填充为'\0'
		while (pChar < &(state.dbuf[DirectoryEntry::DIRSIZE])) {
			*pChar = '\0';
			pChar++;
		}

		//允许出现////a//b 这种路径 这种路径等价于/a/b
		while ('/' == curchar) {
			curchar = (*func)();
		}
		//内层循环部分对于state.dbuf[]中的路径名分量，诸葛搜寻匹配的目录项
		state.IOParam.m_Offset = 0;
		//设置目录项的个数，含空白的目录项
		state.IOParam.m_Count = pInode->i_size / (DirectoryEntry::DIRSIZE + 4);
		freeEntryOffset = 0;
		pBuf = NULL;

		while (true) {
			//对目录项已经搜索完毕
			if (0 == state.IOParam.m_Count) {
				//如果是创建新文件
				if (FileManager::CREATE == mode && curchar == '\0') {
					//将父目录Inode指针保存起来
					state.pdir = pInode;

					if (freeEntryOffset) {
						state.IOParam.m_Offset = freeEntryOffset - (DirectoryEntry::DIRSIZE + 4);
					}
					else {
						pInode->is_changed = true;
					}
					return NULL;
				}

				goto out;
			}

			//已经读完目录文件当前盘块，需要读入下一目录项数据盘块
			if (0 == state.IOParam.m_Offset % Inode::BLOCK_SIZE) {
				//计算要读的物理盘块号
				int phyBlkno = pInode->Bmap(state.IOParam.m_Offset / Inode::BLOCK_SIZE);
				pBuf = bufferManager.Bread(phyBlkno);
			}

			//没有读完当前目录项盘块，则阅读下一目录项至state.dent
			int* src = (int*)(pBuf->b_addr + (state.IOParam.m_Offset % Inode::BLOCK_SIZE));
			for (int i = 0; i < sizeof(DirectoryEntry) / sizeof(int); i++) {
				*((int*)&state.dent + i) = *(src + i);
			}

			state.IOParam.m_Offset += (DirectoryEntry::DIRSIZE + 4);
			state.IOParam.m_Count--;

			//如果是空闲目录项，记录该项位于目录文件中偏移量
			if (0 == state.dent.m_ino) {
				if (0 == freeEntryOffset) {
					freeEntryOffset = state.IOParam.m_Offset;
				}
				continue;
			}

			int i;
			bool success = false;
			for (i = 0; i < DirectoryEntry::DIRSIZE; i++) {
				if (state.dbuf[i] != state.dent.m_name[i]) {
					break; //不匹配，跳出循环
				}
				if (state.dbuf[i] == 0) {
					success = true;
				}
			}
			if (!success) {
				continue; //不是要搜索的目录项
			}
			else {
				break; //目录项匹配成功
			}
		}

		//跳到这里说明pathname当前路径分量匹配成功了，还需匹配pathname中下一路径分量，知道'\0'结束
		
		//如果是删除操作，则返回父目录Inode，而要删除的文件的Inode号在state.dent.m_ino中
		if (FileManager::DELETE == mode && '\0' == curchar) {
			return pInode;
		}

		//匹配目录项成功，则释放当前目录Inode，根据匹配成功的目录项m_ino字段获取相应下一级目录或文件的Inode
		inodeTable.IPut(pInode);
		pInode = inodeTable.IGet(state.dent.m_ino);

		//回到外层while(true)循环，继续匹配Pathname中下一分量路径

		if (NULL == pInode) {
			return NULL;
		}
	}
out:
	inodeTable.IPut(pInode);
	return NULL;
}

char FileManager::NextChar() {
	State& state = Kernel::Instance().GetState();

	return *state.dirp++;
}

Inode* FileManager::MakNode(unsigned int mode) {
	Inode* pInode;
	State& state = Kernel::Instance().GetState();
	FileSystem& fileSystem = Kernel::Instance().GetFileSystem();

	//分配一个空闲DIskInode，里面的内容已经完全清空
	pInode = fileSystem.IAlloc();
	if (NULL == pInode) {
		return NULL;
	}

	pInode->is_changed = true;
	pInode->i_mode = mode;
	pInode->i_nlink = 1;

	//如果创建的是目录
	if (mode == 2) {
		DirectoryEntry direcroty[2];
		//设置目录项中的编号部分
		direcroty[0].m_ino = pInode->i_number;
		direcroty[1].m_ino = state.pdir->i_number;
		//设置目录项中pathname分量部分
		direcroty[0].m_name[0] = '.';
		direcroty[0].m_name[1] = '\0';
		direcroty[1].m_name[0] = '.';
		direcroty[1].m_name[1] = '.';
		direcroty[1].m_name[2] = '\0';

		state.IOParam.m_Count = 2 * (DirectoryEntry::DIRSIZE + 4);
		state.IOParam.m_Base = (unsigned char*)direcroty;
		state.IOParam.m_Offset = 0;

		pInode->WriteI();
	}

	this->WriteDir(pInode);
	return pInode;
}

void FileManager::WriteDir(Inode* pInode) {
	State& state = Kernel::Instance().GetState();
	InodeTable& inodeTable = Kernel::Instance().GetInodeTable();

	//设置目录项中的编号部分
	state.dent.m_ino = pInode->i_number;

	//设置目录项中pathname分量部分
	for (int i = 0; i < DirectoryEntry::DIRSIZE; i++) {
		state.dent.m_name[i] = state.dbuf[i];
	}

	state.IOParam.m_Count = DirectoryEntry::DIRSIZE + 4;
	state.IOParam.m_Base = (unsigned char*)&state.dent;
	state.IOParam.m_Offset = state.pdir->i_size;

	//将目录项写入父目录文件
	state.pdir->WriteI();
	inodeTable.IPut(state.pdir);
}

void FileManager::SetCurDir(char* pathname) {
	State& state = Kernel::Instance().GetState();

	//若路径不是从根目录开始，则在现有state.curdir后面加上当前路径分量
	if (pathname[0] != '/') {
		int length = 0;
		while (true) {
			if (state.curdir[length] == 0) {
				break;
			}
			length++;
		}
		if (length > 0 && state.curdir[length - 1] != '/') {
			state.curdir[length] = '/';
			length++;
		}
		int i = 0;
		while (true) {
			state.curdir[length + i] = pathname[i];
			i++;
			if (pathname[i] == 0) {
				break;
			}
		}
	}
	else {
		int i = 0;
		while (true) {
			state.curdir[i] = pathname[i];
			if (state.curdir[i] == 0) {
				break;
			}
			i++;
		}
	}
	//后处理，处理.和/
	char tmp[20][128]; //用于存储分割出的路径
	int num = 0; //分割出的路径的数量
	int i = 0;
	while (true) {
		while (state.curdir[i] == '/') {
			i++;
		}
		int p = 0;
		while (state.curdir[i] != '\0' && state.curdir[i] != '/') {
			tmp[num][p++] = state.curdir[i++];
		}
		tmp[num][p] = 0;
		num++;
		if (p == 1 && tmp[num - 1][0] == '.') {
			num--;
		}
		else if (p == 2 && tmp[num - 1][0] == '.' && tmp[num - 1][1] == '.') {
			num = num - 2;
			if (num < 0) {
				num = 0;
			}
		}
		if (state.curdir[i] == 0) {
			break;
		}
	}
	int offsetDir = 0; //路径偏移
	for (int i = 0; i < num; i++) {
		state.curdir[offsetDir++] = '/';
		int j = 0;
		while (tmp[i][j] != 0) {
			state.curdir[offsetDir++] = tmp[i][j++];
		}
	}
	if (num == 0) {
		state.curdir[offsetDir++] = '/';
	}
	state.curdir[offsetDir++] = '\0';
	for (int i = offsetDir; i < DirectoryEntry::DIRSIZE; i++) {
		state.curdir[i] = '\0';
	}
}

void FileManager::ChDir() {
	Inode* pInode;
	State& state = Kernel::Instance().GetState();
	InodeTable& inodeTable = Kernel::Instance().GetInodeTable();

	pInode = this->NameI(NextChar, OPEN);
	if (NULL == pInode) {
		return;
	}
	//如果搜索到的文件不是目录文件
	if (pInode->i_mode != 2) {
		inodeTable.IPut(pInode);
		return;
	}
	inodeTable.IPut(state.cdir);
	state.cdir = pInode;

	this->SetCurDir((char*)state.arg);
}

void FileManager::Link() {
	Inode* pInode;
	Inode* pNewInode;
	State& state = Kernel::Instance().GetState();
	InodeTable& inodeTable = Kernel::Instance().GetInodeTable();

	pInode = this->NameI(NextChar, OPEN);
	//打开文件失败
	if (NULL == pInode) {
		return;
	}
	//链接数量已经最大
	if (pInode->i_nlink >= 255) {
		inodeTable.IPut(pInode);
		return;
	}
	state.dirp = (char*)state.arg;
	pNewInode = this->NameI(NextChar, CREATE);
	//如果文件已经存在
	if (NULL != pNewInode) {
		inodeTable.IPut(pNewInode);
	}
	this->WriteDir(pInode);
	pInode->i_nlink++;
	pInode->is_changed = true;
	inodeTable.IPut(pInode);
}

void FileManager::UnLink() {
	Inode* pInode;
	Inode* pDeleteInode;
	State& state = Kernel::Instance().GetState();
	InodeTable& inodeTable = Kernel::Instance().GetInodeTable();

	pDeleteInode = this->NameI(NextChar, DELETE);
	if (NULL == pDeleteInode) {
		return;
	}
	
	pInode = inodeTable.IGet(state.dent.m_ino);
	//写入清零后的目录项
	state.IOParam.m_Offset -= (DirectoryEntry::DIRSIZE + 4);
	state.IOParam.m_Base = (unsigned char*)&state.dent;
	state.IOParam.m_Count = DirectoryEntry::DIRSIZE + 4;

	state.dent.m_ino = 0;
	pDeleteInode->WriteI();

	//修改Inode项
	pInode->i_nlink--;
	pInode->is_changed = true;

	inodeTable.IPut(pInode);
	inodeTable.IPut(pDeleteInode);
}

void FileManager::Remove() {
	BufferManager& bufferManager = Kernel::Instance().GetBufferManager();
	Space& space = Kernel::Instance().GetSpace();
	State& state = Kernel::Instance().GetState();


	char tmp[128];
	for (int i = 0; i < 128; i++) {
		tmp[i] = *(state.dirp + i);
		if (tmp[i] == 0) {
			break;
		}
	}
	Inode* pInode = NameI(NextChar, FileManager::OPEN);
	if (pInode == NULL) {
		return;
	}
	if (pInode->i_mode == 2) {
		int blockNum = pInode->i_size / Inode::BLOCK_SIZE;
		int j = 0;
		for (int i = 0; i < blockNum; i++) {
			int phyBlockNum = pInode->Bmap(i);
			Buf* buf = bufferManager.Bread(phyBlockNum);
			for (int l = 0; l < 16; l++) {
				if (j >= pInode->i_size / (sizeof(int) * 8)) {
					break;
				}
				if (j > 1) {
					int k = 0;
					if (*((int*)(buf->b_addr + 32 * (j % 16))) == 0) {
						j++;
						continue;
					}
					while (true) {
						space.pathParam[k] = *(buf->b_addr + 32 * (j % 16) + 4 + k);
						k++;
						if (*(buf->b_addr + 32 * (j % 16) + 4 + k) == 0) {
							break;
						}
					}
					state.dirp = space.pathParam;
					Remove();
				}
				j++;
			}
		}
	}
	state.dirp = tmp;
	UnLink();
}

DirectoryEntry::DirectoryEntry() {
	this->m_ino = 0;
	this->m_name[0] = '\0';
}

DirectoryEntry::~DirectoryEntry() {
	//do nothing
}