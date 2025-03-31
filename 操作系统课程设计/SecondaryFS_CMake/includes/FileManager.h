#pragma once
#include "FileSystem.h"
#include "OpenFileManager.h"
#include "File.h"

class FileManager {
public:
	//Ŀ¼����ģʽ
	enum DirectorySearchMode {
		OPEN = 0, //�Դ��ļ���ʽ����Ŀ¼
		CREATE = 1, //�½���ʽ
		DELETE = 2 //ɾ����ʽ
	};

	/* Functions */
public:
	FileManager();
	~FileManager();

	void FormatSystem(); //��ʽ������

	void Open(); //���ļ���ϵͳ����

	void Creat(); //�����ļ���ϵͳ����

	void Open1(Inode* pInode, int trf); //Open()��Create()ϵͳ���õĹ�������

	void Close(); //�ر��ļ�ϵͳ����

	void Seek(); //Seekϵͳ����

	void FStat(); //��ȡ�ļ���Ϣ

	void Stat(); //Fstat��ȡ�ļ���Ϣ

	void Stat1(Inode* pInode, unsigned long long statBuf); //FStat()��Stat()�Ĺ�������

	void Read(); //Read()ϵͳ����

	void Write(); //Write()ϵͳ����

	void Rdwr(int mode);  //��дϵͳ����ϵͳ����
	
	Inode* NameI(char (*func)(), enum DirectorySearchMode mode); //Ŀ¼��������·��ת��Ϊ��Ӧ��Inode
	
	static char NextChar(); //��ȡ·���е���һ���ַ�

	Inode* MakNode(unsigned int mode); //����Ϊ�������ļ������ں���Դ

	void WriteDir(Inode* pInode); //��Ŀ¼��Ŀ¼�ļ�д��һ��Ŀ¼��

	void SetCurDir(char* pathname); //���õ�ǰ����·��

	void ChDir(); //�ı䵱ǰ����Ŀ¼

	void Link(); //�����ļ�����������

	void UnLink(); //ȡ���ļ�

	void Remove(); //ɾ���ļ������ļ���
	
	void ResetFileManager(); //����

public:
	Inode* rootDirInode = NULL; //��Ŀ¼�ڴ�Inode
};

class DirectoryEntry {
	/* static members */
public:
	static const int DIRSIZE = 28; //Ŀ¼����·�����ֵ�����ַ�������

	/* Functions */
public:
	DirectoryEntry();
	~DirectoryEntry();

public:
	int m_ino; //Ŀ¼����Inode��Ų���
	char m_name[DIRSIZE]; //Ŀ¼����·��������
};