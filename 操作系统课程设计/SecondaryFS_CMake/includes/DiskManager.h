#pragma once
#include <stdio.h>

class DiskManager {
private:
	const char* diskPath = "SecondaryFS.img"; //磁盘镜像路径
	FILE* diskFd;

public:
	DiskManager();
	~DiskManager();

	void createDisk(); //创建磁盘
	void openDisk(); //打开硬盘
	void seekOneBlock(int blkno); //选择一个块的一个位置
	void readOneBlock(unsigned char* buffer); //读出一个块
	void writeOneBlock(unsigned char* buffer); //写入一个块
	void closeDisk();//关闭硬盘
};