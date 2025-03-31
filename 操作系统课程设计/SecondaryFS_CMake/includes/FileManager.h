#pragma once
#include "FileSystem.h"
#include "OpenFileManager.h"
#include "File.h"

class FileManager {
public:
	//目录搜索模式
	enum DirectorySearchMode {
		OPEN = 0, //以打开文件方式搜索目录
		CREATE = 1, //新建方式
		DELETE = 2 //删除方式
	};

	/* Functions */
public:
	FileManager();
	~FileManager();

	void FormatSystem(); //格式化磁盘

	void Open(); //打开文件的系统调用

	void Creat(); //创建文件的系统调用

	void Open1(Inode* pInode, int trf); //Open()和Create()系统调用的公共部分

	void Close(); //关闭文件系统调用

	void Seek(); //Seek系统调用

	void FStat(); //获取文件信息

	void Stat(); //Fstat获取文件信息

	void Stat1(Inode* pInode, unsigned long long statBuf); //FStat()和Stat()的共享例程

	void Read(); //Read()系统调用

	void Write(); //Write()系统调用

	void Rdwr(int mode);  //读写系统公用系统调用
	
	Inode* NameI(char (*func)(), enum DirectorySearchMode mode); //目录搜索，将路径转化为相应的Inode
	
	static char NextChar(); //获取路径中的下一个字符

	Inode* MakNode(unsigned int mode); //用于为创建新文件分配内核资源

	void WriteDir(Inode* pInode); //向父目录的目录文件写入一个目录项

	void SetCurDir(char* pathname); //设置当前工作路径

	void ChDir(); //改变当前工作目录

	void Link(); //创建文件的异名引用

	void UnLink(); //取消文件

	void Remove(); //删除文件或者文件夹
	
	void ResetFileManager(); //重置

public:
	Inode* rootDirInode = NULL; //根目录内存Inode
};

class DirectoryEntry {
	/* static members */
public:
	static const int DIRSIZE = 28; //目录项中路径部分的最大字符串长度

	/* Functions */
public:
	DirectoryEntry();
	~DirectoryEntry();

public:
	int m_ino; //目录项中Inode编号部分
	char m_name[DIRSIZE]; //目录项中路径名部分
};