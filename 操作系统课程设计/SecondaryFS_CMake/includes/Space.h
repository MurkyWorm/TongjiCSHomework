#pragma once

class Space {
	/* Members */
public:
	char pathParam[128]; //·������
	unsigned char* buffer; //���ڶ�д�Ļ�����

	/* Functions */
public:
	Space();
	~Space();

	void ResetSpace(); //����
};