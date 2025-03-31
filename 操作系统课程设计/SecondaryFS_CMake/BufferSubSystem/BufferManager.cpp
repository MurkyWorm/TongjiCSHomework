#include "BufferManager.h"
#include "Kernel.h"

BufferManager::BufferManager() {
	this->usedBufNum = 0;
	for (int i = 0; i < NBUF; i++) {
		this->m_Buf[i].is_dirty = false;
		this->m_Buf[i].is_new = false;
		this->m_Buf[i].b_addr = this->Buffer[i];
		this->m_Buf[i].b_blkno = -1; //表示还没有对应的磁盘块
	}
}

BufferManager::~BufferManager() {
	//do nothing
}

Buf* BufferManager::GetBlk(int blkno) {
	DiskManager& diskManager = Kernel::Instance().GetDiskManager();
	//检测该块是否已经被分配了缓存
	for (int i = 0; i < NBUF; i++) {
		if (this->m_Buf[i].b_blkno == blkno) {
			for (int j = 0; j < this->usedBufNum; j++) {
				int tmp = this->bufQueue.front();
				this->bufQueue.pop();
				if (tmp != i) {
					this->bufQueue.push(tmp);
				}
			}
			this->bufQueue.push(i);
			return &(this->m_Buf[i]);
		}
	}

	//如果没有则需新分配块
	if (this->usedBufNum < NBUF) { //还有未被分配的缓存
		for (int i = 0; i < NBUF; i++) {
			if (this->m_Buf[i].b_blkno == -1) {
				this->m_Buf[i].b_blkno = blkno;
				this->m_Buf[i].is_dirty = true;
				this->m_Buf[i].is_new = true;
				this->bufQueue.push(i);
				this->usedBufNum++;
				return &(this->m_Buf[i]);
			}
		}
	}
	else { //若缓存块已经用完，则需淘汰
		int eliminateBufId = this->bufQueue.front();
		this->bufQueue.pop(); //摘除队首缓存

		if (m_Buf[eliminateBufId].is_dirty) { //如果该块脏，则需写回
			diskManager.seekOneBlock(m_Buf[eliminateBufId].b_blkno);
			diskManager.writeOneBlock(m_Buf[eliminateBufId].b_addr);
		}

		this->m_Buf[eliminateBufId].b_blkno = blkno;
		this->m_Buf[eliminateBufId].is_dirty = true;
		this->m_Buf[eliminateBufId].is_new = true;
		this->bufQueue.push(eliminateBufId); //分配给新的块
		return &(this->m_Buf[eliminateBufId]);
	}

	return NULL;
}

Buf* BufferManager::Bread(int blkno) {
	Buf* bp;
	DiskManager& diskManager = Kernel::Instance().GetDiskManager();

	bp = this->GetBlk(blkno); //根据字符块号申请缓存

	if (bp->is_new == false) { //如果不是新分配的块
		return bp;
	}
	else { //如果是新分配的块
		diskManager.seekOneBlock(blkno);
		diskManager.readOneBlock(bp->b_addr);
		bp->is_new = false;
		bp->is_dirty = false;
		return bp;
	}
}

void BufferManager::Bwrite(Buf* bp) {
	DiskManager& diskManager = Kernel::Instance().GetDiskManager();
	if (bp->is_dirty == false) { //如果该缓存不脏
		return;
	}
	else {
		diskManager.seekOneBlock(bp->b_blkno);
		diskManager.writeOneBlock(bp->b_addr);
		bp->is_dirty = false;
	}
}

void BufferManager::Bflush() {
	DiskManager& diskManager = Kernel::Instance().GetDiskManager();
	for (int i = 0; i < NBUF; i++) {
		if (this->m_Buf[i].b_blkno == -1 || this->m_Buf[i].is_dirty == false) {
			continue;
		}
		else {
			diskManager.seekOneBlock(this->m_Buf[i].b_blkno);
			diskManager.writeOneBlock(this->m_Buf[i].b_addr);
			this->m_Buf[i].is_dirty = false;
		}
	}
}

void BufferManager::ResetBufferManager() {
	this->usedBufNum = 0;
	for (int i = 0; i < NBUF; i++) {
		this->m_Buf[i].is_dirty = false;
		this->m_Buf[i].is_new = false;
		this->m_Buf[i].b_addr = this->Buffer[i];
		this->m_Buf[i].b_blkno = -1; //表示还没有对应的磁盘块
	}
	while (!bufQueue.empty()) {
		bufQueue.pop();
	}
}