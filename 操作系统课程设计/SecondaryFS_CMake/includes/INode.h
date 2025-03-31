#pragma once
#include "Buf.h"

class Inode {
public:
	/* static const member */
	static const int BLOCK_SIZE = 512; //文件逻辑块大小
	static const int ADDRESS_PER_INDEX_BLOCK = BLOCK_SIZE / sizeof(int); //每个索引块包含的物理盘块号

	static const int SMALL_FILE_BLOCK = 6; //小型文件：直接索引表最多可寻址的逻辑块号
	static const int LARGE_FILE_BLOCK = 128 * 2 + 6; //大型文件：一次间接索引表最多可寻址的逻辑块号
	static const int HUGE_FILE_BLOCK = 128 * 128 * 2 + 128 * 2 + 6; //巨型文件：经二次间接索引最大可寻址文件逻辑块号

	/* Functions */
public:
	Inode();
	~Inode();

	void ReadI(); //根据Inode对象中的物理磁盘块索引表，读取相应文件数据

	void WriteI(); //根据Inode对象中的物理磁盘块索引表，将数据写入文件

	int Bmap(int lbn); //将文件的逻辑块号转换成对应的物理盘块号

	void IUpdate(); //更新外存Inode

	void ITrunc(); //释放Inode对应文件占用的磁盘块

	void Clean(); //清空Inode对象的数据

	void ICopy(Buf* bp, int number); //将包含外存Inode字符块中信息拷贝到内存Inode中

	/* Members */
public:
	bool is_changed; //该Inode是否被修改过，需要更新到外存

	unsigned int i_mode; //该Inode是否被使用以及类型

	int i_nlink; //文件连结计数

	int i_number; //外存inode区中的编号

	int i_size; //文件大小，字节为单位
	int i_addr[10]; //用于文件逻辑块号和物理块号转换的基本索引表
};

class DiskInode {
	/* Functions */
public:
	DiskInode();
	~DiskInode();

	/* Members */
public:
	unsigned int d_mode; //该inode是否被使用
	int d_nlink; //文件连结计数

	int d_size; //文件大小，字节为单位
	int d_addr[10]; //用于文件逻辑块号和物理块号的基本索引表

	int padding[3]; //16字节填充
};