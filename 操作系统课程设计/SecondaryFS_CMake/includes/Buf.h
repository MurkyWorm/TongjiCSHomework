#pragma once

class Buf {
public:
	bool is_dirty; //�Ƿ�Ϊ�໺��
	bool is_new; //�Ƿ�Ϊ�·���

	unsigned char* b_addr; /* ָ��û���������Ļ��������׵�ַ */
	int b_blkno; /* �����߼���� */
};
