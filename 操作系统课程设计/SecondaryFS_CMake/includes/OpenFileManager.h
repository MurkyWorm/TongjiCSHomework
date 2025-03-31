#pragma once
#include "INode.h"
#include "File.h"

class InodeTable;

class OpenFileTable {
public:
	/* static consts */
	static const int NFILE = 100; //���ļ����ƿ�File�ṹ������

	/* Functions */
public:
	OpenFileTable();
	~OpenFileTable();

	File* FAlloc(); //��ϵͳ���ļ����з���һ�����е�File�ṹ

	void CloseF(File* pFile); //�ͷ�File�ṹ

	void ResetOpenFileTable(); //����

	/* Members */
public:
	File m_File[NFILE];
};

class InodeTable {
	/* static consts */
public:
	static const int NINODE = 100; //�ڴ�Inode����

	/* Functions */
public:
	InodeTable();
	~InodeTable();

	Inode* IGet(int inumber); //����Inode��Ž�������ڴ���

	void IPut(Inode* pNode); //���Ѿ�û��Ŀ¼��ָ���������ͷŴ��ļ�ռ�õĴ��̿�

	void UpdateInodeTable(); //�����б��޸Ĺ����ڴ�Inode���µ���Ӧ���Inode��

	int IsLoaded(int inumber); //�����Ϊinumber�����Inode�Ƿ����ڴ濽��

	Inode* GetFreeInode(); //���ڴ�Inode����Ѱ��һ�����е��ڴ�Inode

	void ResetInodeTable(); //����

	/* Members */
public:
	Inode m_Inode[NINODE]; //�ڴ�Inode����
};