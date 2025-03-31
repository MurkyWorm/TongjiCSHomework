#pragma once
#include "INode.h"
#include "File.h"

class InodeTable;

class OpenFileTable {
public:
	/* static consts */
	static const int NFILE = 100; //打开文件控制块File结构的数量

	/* Functions */
public:
	OpenFileTable();
	~OpenFileTable();

	File* FAlloc(); //在系统打开文件表中分配一个空闲的File结构

	void CloseF(File* pFile); //释放File结构

	void ResetOpenFileTable(); //重置

	/* Members */
public:
	File m_File[NFILE];
};

class InodeTable {
	/* static consts */
public:
	static const int NINODE = 100; //内存Inode数量

	/* Functions */
public:
	InodeTable();
	~InodeTable();

	Inode* IGet(int inumber); //根据Inode编号将其读入内存中

	void IPut(Inode* pNode); //若已经没有目录项指向它，则释放此文件占用的磁盘块

	void UpdateInodeTable(); //将所有被修改过的内存Inode更新到对应外存Inode中

	int IsLoaded(int inumber); //检查编号为inumber的外存Inode是否有内存拷贝

	Inode* GetFreeInode(); //在内存Inode表中寻找一个空闲的内存Inode

	void ResetInodeTable(); //重置

	/* Members */
public:
	Inode m_Inode[NINODE]; //内存Inode数组
};