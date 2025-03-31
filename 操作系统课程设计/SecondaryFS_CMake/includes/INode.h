#pragma once
#include "Buf.h"

class Inode {
public:
	/* static const member */
	static const int BLOCK_SIZE = 512; //�ļ��߼����С
	static const int ADDRESS_PER_INDEX_BLOCK = BLOCK_SIZE / sizeof(int); //ÿ������������������̿��

	static const int SMALL_FILE_BLOCK = 6; //С���ļ���ֱ������������Ѱַ���߼����
	static const int LARGE_FILE_BLOCK = 128 * 2 + 6; //�����ļ���һ�μ������������Ѱַ���߼����
	static const int HUGE_FILE_BLOCK = 128 * 128 * 2 + 128 * 2 + 6; //�����ļ��������μ����������Ѱַ�ļ��߼����

	/* Functions */
public:
	Inode();
	~Inode();

	void ReadI(); //����Inode�����е�������̿���������ȡ��Ӧ�ļ�����

	void WriteI(); //����Inode�����е�������̿�������������д���ļ�

	int Bmap(int lbn); //���ļ����߼����ת���ɶ�Ӧ�������̿��

	void IUpdate(); //�������Inode

	void ITrunc(); //�ͷ�Inode��Ӧ�ļ�ռ�õĴ��̿�

	void Clean(); //���Inode���������

	void ICopy(Buf* bp, int number); //���������Inode�ַ�������Ϣ�������ڴ�Inode��

	/* Members */
public:
	bool is_changed; //��Inode�Ƿ��޸Ĺ�����Ҫ���µ����

	unsigned int i_mode; //��Inode�Ƿ�ʹ���Լ�����

	int i_nlink; //�ļ��������

	int i_number; //���inode���еı��

	int i_size; //�ļ���С���ֽ�Ϊ��λ
	int i_addr[10]; //�����ļ��߼���ź�������ת���Ļ���������
};

class DiskInode {
	/* Functions */
public:
	DiskInode();
	~DiskInode();

	/* Members */
public:
	unsigned int d_mode; //��inode�Ƿ�ʹ��
	int d_nlink; //�ļ��������

	int d_size; //�ļ���С���ֽ�Ϊ��λ
	int d_addr[10]; //�����ļ��߼���ź������ŵĻ���������

	int padding[3]; //16�ֽ����
};