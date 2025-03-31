#pragma once
#include "File.h"
#include "INode.h"
#include "FileManager.h"

class State {
public:
	int arg[10] = {}; //ϵͳ���õĲ���
	char* dirp = NULL; //ϵͳ���ò�����һ������Pathnameָ��

	Inode* cdir = NULL; //ָ��ǰĿ¼��Inodeָ��
	Inode* pdir = NULL; //ָ��Ŀ¼��Inodeָ��

	DirectoryEntry dent; //��ǰĿ¼��Ŀ¼��
	char dbuf[DirectoryEntry::DIRSIZE] = {}; //��ǰ·������
	char curdir[128] = {}; //��ǰ����Ŀ¼������·��

	OpenFiles ofiles; //���ļ�����������

	IOParameter IOParam; //��¼��ǰ����д�ļ���ƫ�������û�Ŀ�������ʣ���ֽڲ���

public:
	State();
	~State();

	void ResetState(); //����״̬
};