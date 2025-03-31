#pragma once
#include "INode.h"
#include "Buf.h"
#include "OpenFileManager.h"


class SuperBlock {
	/* Functions */
public:
	SuperBlock();
	~SuperBlock();

	void ResetSuperBlock();

	/* Members */
public:
	int s_isize; //外存Inode区占用的盘块数
	int s_fsize; //盘块总数

	int s_nfree; //直接管理的空闲盘块数
	int s_free[100]; //直接管理的空闲盘块索引表

	int s_ninode; //直接管理的空闲外存Inode数量
	int s_inode[100]; //直接管理的空闲外存Inode索引表

	int s_fmod; //内存中super block副本被修改标识，意味着需要更新外存对应的Super Block
	
	int padding[51]; //填充，使之占据两个扇区
};

class FileSystem {
public:
	/* static const */
	static const int SUPER_BLOCK_SECTOR_NUMBER = 0; //定义SuoerBlock在磁盘上的扇区号

	static const int ROOTINO = 1; //文件系统根目录外存Inode编号

	static const int INODE_NUMBER_PER_SECTOR = 8; //外存INode对象长度为64字节，每个磁盘块可以存放512/64=8个外存Inode
	static const int INODE_ZONE_START_SECTOR = 2; //外存INode位于磁盘上的起始扇区号
	static const int INODE_SIZE = 1024 - 2; //磁盘上外存Inode区占据的扇区数

	static const int DATA_ZONE_START_SECTOR = 1024; //数据区起始扇区号
	static const int DATA_ZONE_END_SECTOR = 18000 - 1; //数据区的结束扇区号
	static const int DATA_ZONE_SIZE = 18000 - DATA_ZONE_START_SECTOR; //数据区占据的扇区数量

	/* Functions */
public:
	FileSystem();
	~FileSystem();

	void LoadSuperBlock(); //系统初始化时读入SuperBlock

	void Update(); //将SuperBlock对象的内存副本更新到存储设备的SurperBlock中去

	Inode* IAlloc(); //分配一个空闲外存INodec

	void IFree(int number); //释放编号为number的外存INode

	Buf* Alloc(); //分配空闲磁盘块

	void Free(int blkno); //释放编号为blkno的磁盘块
};