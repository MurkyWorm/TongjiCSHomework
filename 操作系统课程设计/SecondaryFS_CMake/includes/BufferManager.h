#pragma once
#include <queue>
#include "Buf.h"
using namespace std;

class BufferManager {
public:
	/* static const member */
	static const int NBUF = 15;			/* 缓存控制块、缓冲区的数量 */
	static const int BUFFER_SIZE = 512;	/* 缓冲区大小。 以字节为单位 */

public:
	BufferManager();
	~BufferManager();

	Buf* GetBlk(int blkno); //申请一块缓存，用于读写字符块blkno

	Buf* Bread(int blkno); //读一个磁盘块

	void Bwrite(Buf* bp); //写一个磁盘块

	void Bflush(); //将缓存全部输出到磁盘

	void ResetBufferManager(); //重置

private:
	int usedBufNum; // 被使用的缓存块的数量
	Buf m_Buf[NBUF]; //缓存管理块
	unsigned char Buffer[NBUF][BUFFER_SIZE] = {}; //缓存区
	queue<int> bufQueue; //被分配给块的缓存队列
};
