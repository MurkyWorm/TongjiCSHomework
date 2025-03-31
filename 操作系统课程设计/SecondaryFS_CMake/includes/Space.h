#pragma once

class Space {
	/* Members */
public:
	char pathParam[128]; //路径参数
	unsigned char* buffer; //用于读写的缓冲区

	/* Functions */
public:
	Space();
	~Space();

	void ResetSpace(); //重置
};