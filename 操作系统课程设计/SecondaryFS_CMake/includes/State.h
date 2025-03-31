#pragma once
#include "File.h"
#include "INode.h"
#include "FileManager.h"

class State {
public:
	int arg[10] = {}; //系统调用的参数
	char* dirp = NULL; //系统调用参数，一般用于Pathname指针

	Inode* cdir = NULL; //指向当前目录的Inode指针
	Inode* pdir = NULL; //指向父目录的Inode指针

	DirectoryEntry dent; //当前目录的目录项
	char dbuf[DirectoryEntry::DIRSIZE] = {}; //当前路径分量
	char curdir[128] = {}; //当前工作目录的完整路径

	OpenFiles ofiles; //打开文件描述符对象

	IOParameter IOParam; //记录当前读、写文件的偏移量，用户目标区域和剩余字节参数

public:
	State();
	~State();

	void ResetState(); //重置状态
};