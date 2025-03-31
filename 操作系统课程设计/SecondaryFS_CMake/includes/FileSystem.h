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
	int s_isize; //���Inode��ռ�õ��̿���
	int s_fsize; //�̿�����

	int s_nfree; //ֱ�ӹ���Ŀ����̿���
	int s_free[100]; //ֱ�ӹ���Ŀ����̿�������

	int s_ninode; //ֱ�ӹ���Ŀ������Inode����
	int s_inode[100]; //ֱ�ӹ���Ŀ������Inode������

	int s_fmod; //�ڴ���super block�������޸ı�ʶ����ζ����Ҫ��������Ӧ��Super Block
	
	int padding[51]; //��䣬ʹ֮ռ����������
};

class FileSystem {
public:
	/* static const */
	static const int SUPER_BLOCK_SECTOR_NUMBER = 0; //����SuoerBlock�ڴ����ϵ�������

	static const int ROOTINO = 1; //�ļ�ϵͳ��Ŀ¼���Inode���

	static const int INODE_NUMBER_PER_SECTOR = 8; //���INode���󳤶�Ϊ64�ֽڣ�ÿ�����̿���Դ��512/64=8�����Inode
	static const int INODE_ZONE_START_SECTOR = 2; //���INodeλ�ڴ����ϵ���ʼ������
	static const int INODE_SIZE = 1024 - 2; //���������Inode��ռ�ݵ�������

	static const int DATA_ZONE_START_SECTOR = 1024; //��������ʼ������
	static const int DATA_ZONE_END_SECTOR = 18000 - 1; //�������Ľ���������
	static const int DATA_ZONE_SIZE = 18000 - DATA_ZONE_START_SECTOR; //������ռ�ݵ���������

	/* Functions */
public:
	FileSystem();
	~FileSystem();

	void LoadSuperBlock(); //ϵͳ��ʼ��ʱ����SuperBlock

	void Update(); //��SuperBlock������ڴ渱�����µ��洢�豸��SurperBlock��ȥ

	Inode* IAlloc(); //����һ���������INodec

	void IFree(int number); //�ͷű��Ϊnumber�����INode

	Buf* Alloc(); //������д��̿�

	void Free(int blkno); //�ͷű��Ϊblkno�Ĵ��̿�
};