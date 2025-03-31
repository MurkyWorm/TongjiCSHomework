#pragma once
#include <stdio.h>

class DiskManager {
private:
	const char* diskPath = "SecondaryFS.img"; //���̾���·��
	FILE* diskFd;

public:
	DiskManager();
	~DiskManager();

	void createDisk(); //��������
	void openDisk(); //��Ӳ��
	void seekOneBlock(int blkno); //ѡ��һ�����һ��λ��
	void readOneBlock(unsigned char* buffer); //����һ����
	void writeOneBlock(unsigned char* buffer); //д��һ����
	void closeDisk();//�ر�Ӳ��
};