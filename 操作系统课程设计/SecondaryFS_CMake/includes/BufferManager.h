#pragma once
#include <queue>
#include "Buf.h"
using namespace std;

class BufferManager {
public:
	/* static const member */
	static const int NBUF = 15;			/* ������ƿ顢������������ */
	static const int BUFFER_SIZE = 512;	/* ��������С�� ���ֽ�Ϊ��λ */

public:
	BufferManager();
	~BufferManager();

	Buf* GetBlk(int blkno); //����һ�黺�棬���ڶ�д�ַ���blkno

	Buf* Bread(int blkno); //��һ�����̿�

	void Bwrite(Buf* bp); //дһ�����̿�

	void Bflush(); //������ȫ�����������

	void ResetBufferManager(); //����

private:
	int usedBufNum; // ��ʹ�õĻ���������
	Buf m_Buf[NBUF]; //��������
	unsigned char Buffer[NBUF][BUFFER_SIZE] = {}; //������
	queue<int> bufQueue; //���������Ļ������
};
