#pragma once
#include "INode.h"
#include "stddef.h"

class File {
public:
	File();
	~File();

	bool is_av; //是否空闲
	Inode* f_inode; //指向打开文件的内存Inode指针
	int f_offset; //文件读写位置指针
};

class OpenFiles {
	/* static members */
public:
	static const int NOFILES = 100; //允许打开的最大文件数

	/* Functions */
public:
	OpenFiles();
	~OpenFiles();

	int AllocFreeSlot(); //打开文件时，在打开文件描述符表中分配一个空闲表项

	File* GetF(int fd); //根据文件描述符参数找到对应的打开文件控制块File结构

	void SetF(int fd, File* pFile); //为已分配到的空闲描述符fd和空闲File对象建立勾连关系

public:
	File* OpenFileTable[NOFILES]; //File对象指针数组，指向系统打开文件表中的File对象
};

class IOParameter {
	/* Function */
public:
	IOParameter();
	~IOParameter();

	/* Members */
public:
	unsigned char* m_Base; //当前读写目标区域首地址
	int m_Offset; //当前读、写文件的字节偏移量
	int m_Count; //当前还剩余的读、写字节数量
};