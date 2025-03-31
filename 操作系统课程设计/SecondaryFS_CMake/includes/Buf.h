#pragma once

class Buf {
public:
	bool is_dirty; //是否为脏缓冲
	bool is_new; //是否为新分配

	unsigned char* b_addr; /* 指向该缓冲区管理的缓冲区的首地址 */
	int b_blkno; /* 磁盘逻辑块号 */
};
