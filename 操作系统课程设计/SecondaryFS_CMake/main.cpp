#define _CRT_SECURE_NO_WARNINGS
#include "Kernel.h"
#include <fstream>
#include <conio.h>
#include <string>
using namespace std;

//ȫ�ֱ���
FileManager& fileManager = Kernel::Instance().GetFileManager();
DiskManager& diskManager = Kernel::Instance().GetDiskManager();
State& state = Kernel::Instance().GetState();
FileSystem& fileSystem = Kernel::Instance().GetFileSystem();
InodeTable& inodeTable = Kernel::Instance().GetInodeTable();
BufferManager& bufferManager = Kernel::Instance().GetBufferManager();
SuperBlock& superBlock = Kernel::Instance().GetSuperBlock();
OpenFileTable& openFileTable = Kernel::Instance().GetOpenFileTable();
Space& space = Kernel::Instance().GetSpace();

//�����������ָ��ת��Ϊ�����ĺ���
string transInstruction(string instruction) {
	string op;
	string tmp;
	State& state = Kernel::Instance().GetState();
	Space& space = Kernel::Instance().GetSpace();

	int segCount = 0; //����ָ���Կո�ֿ��Ķ���
	char* p = (char*)state.arg;
	for (int i = 0; i < instruction.length(); i++) {
		if (instruction[i] != ' ') {
			tmp += instruction[i];
		}
		if (instruction[i] == ' ' || i == instruction.length() - 1) {
			if (segCount == 0) {
				op = tmp;
			}
			else if (segCount >= 1) {
				for (int j = 0; j < tmp.length(); j++) {
					*(p++) = tmp[j];
					if (j == tmp.length() - 1) {
						*(p++) = 0;
					}
				}
			}
			segCount++;
			tmp.clear();
		}
	}
	if (op == "ls" && segCount != 1 && segCount != 2) {
		return "error";
	}
	else if ((op == "cd" || op == "mkdir" || op == "rm" || op == "open" || op == "close" || op == "create" || op == "unlink" || op == "rm" || op == "cat") && segCount != 2) {
		return "error";
	}
	else if ((op == "shutdown" || op == "exit" || op == "format") && segCount != 1) {
		return "error";
	}
	else if (op == "lseek" && segCount != 4) {
		return "error";
	}
	else if ((op == "read" || op == "write" || op == "link" || op == "fin" || op == "fout") && segCount != 3) {
		return "error";
	}

	//����ָ��Ĳ�������
	if (op == "ls" && segCount == 1) {
		*((char*)state.arg) = '\0';
	}
	if (op == "ls" || op == "cd" || op == "mkdir" || op == "rm" || op == "open" || op == "close" || op == "lseek" || op == "read" || op == "write" || op == "create" || op == "link" || op == "unlink" || op == "rm" || op == "fin" || op == "fout" || op == "cat") {
		p = (char*)state.arg;
		for (int j = 0; true; j++) {
			space.pathParam[j] = *(p++);
			if (space.pathParam[j] == 0) {
				break;
			}
		}
		state.dirp = space.pathParam;
	}
	if (op == "lseek" || op == "read" || op == "write") {
		int fd = 0;
		int offset = 0;
		Inode* pInode = fileManager.NameI(fileManager.NextChar, FileManager::OPEN);
		if (pInode == NULL) {
			return "error";
		}
		for (int i = 0; i < OpenFiles::NOFILES; i++) {
			File* tmp = state.ofiles.OpenFileTable[i];
			if (tmp != NULL && tmp->is_av == false && tmp->f_inode->i_number == pInode->i_number) {
				fd = i;
				break;
			}
		}
		while (*p != 0) {
			offset = offset * 10 + (*p - 48);
			p++;
		}
		state.arg[0] = fd;
		state.arg[1] = offset;
		
	}
	if (op == "lseek") {
		int choice = 0;
		p++;
		string tmp;
		while (*p != 0) {
			tmp = tmp + *p;
			p++;
		}
		if (tmp == "SEEK_SET") {
			choice = 0;
		}
		else if (tmp == "SEEK_CUR") {
			choice = 1;
		}
		else if (tmp == "SEEK_END") {
			choice = 2;
		}
		else {
			return "error";
		}
		state.arg[2] = choice;
	}
	if (op == "link" || op == "fin" || op == "fout") {
		char* i = (char*)state.arg;
		while (true) {
			*(i++) = *(p++);
			if (*(i - 1) == 0) {
				break;
			}
		}
		if (op == "fin") {
			state.dirp = (char*)state.arg;
		}
	}

	return op;
}

//format����
void format() {
	fileManager.FormatSystem();
	//����Ϊ��ʼ״̬����ո�ʽ��ʱ�õ����ڴ��е����ݽṹ
	fileManager.ResetFileManager();
	state.ResetState();
	inodeTable.ResetInodeTable();
	bufferManager.ResetBufferManager();
	superBlock.ResetSuperBlock();
	openFileTable.ResetOpenFileTable();
	space.ResetSpace();
}

//open����
void open() {
	fileManager.Open();
}

//close����
void close() {
	Inode* pInode = fileManager.NameI(fileManager.NextChar, FileManager::OPEN);
	for (int i = 0; i < OpenFiles::NOFILES; i++) {
		File* tmp = state.ofiles.OpenFileTable[i];
		if (tmp != NULL && tmp->is_av == false && tmp->f_inode->i_number == pInode->i_number) {
			state.arg[0] = i;
			fileManager.Close();
			break;
		}
	}
}

//lseek����
void lseek() {
	fileManager.Seek();
}

//read����
void read() {
	fileManager.Read();
}

//write����
void write() {
	fileManager.Write();
}

//create����
void create() {
	fileManager.Creat();
}

//cat����
void cat() {
	fileManager.Open();
	state.dirp = space.pathParam;
	int fd = 0;
	Inode* pInode = fileManager.NameI(fileManager.NextChar, FileManager::OPEN);
	if (pInode == NULL || pInode->i_mode == 2) {
		return;
	}
	for (int i = 0; i < OpenFiles::NOFILES; i++) {
		File* tmp = state.ofiles.OpenFileTable[i];
		if (tmp != NULL && tmp->is_av == false && tmp->f_inode->i_number == pInode->i_number) {
			fd = i;
			break;
		}
	}
	int lSize = pInode->i_size;
	state.arg[0] = fd;
	state.arg[1] = lSize;
	fileManager.Read();
	for (int i = 0; i < lSize; i++) {
		cout << char(*(space.buffer + i));
	}
	cout << endl;
	fileManager.Close();
}

//link����
void link() {
	fileManager.Link();
}

//unlink����
void unlink() {
	fileManager.UnLink();
}

void rm() {
	fileManager.Remove();
}

//ls����
void ls() {
	Inode* pInode = fileManager.NameI(fileManager.NextChar, FileManager::OPEN);
	if (pInode == NULL || pInode->i_mode == 1) {
		return;
	}
	int blockNum = pInode->i_size / Inode::BLOCK_SIZE;
	if (pInode->i_size % Inode::BLOCK_SIZE > 0) {
		blockNum++;
	}
	//��ȡ�����Ŀ¼��
	int j = 0;
	int neg = 0;
	for (int i = 0; i < blockNum; i++) {
		int phyBlockNum = pInode->Bmap(i);
		Buf* buf = bufferManager.Bread(phyBlockNum);
		for (int l = 0; l < 16; l++) {
			if (j >= pInode->i_size / (sizeof(int) * 8)) {
				break;
			}
			if (j > 1) {
				int k = 0;
				if (*((int*)(buf->b_addr + 32 * (j % 16))) == 0) {
					j++;
					neg--;
					continue;
				}
				while (true) {
					if (*(buf->b_addr + 32 * (j % 16) + 4 + k) == 0) {
						break;
					}
					cout << *(buf->b_addr + 32 * (j % 16) + 4 + k);
					k++;
				}
				cout << " ";
			}
			j++;
		}
	}
	if (j + neg == 2) {
		cout << "no file in this directory";
	}
	cout << endl;
}

//cd����
void cd() {
	fileManager.ChDir();
}

//mkdir����
void mkdir() {
	fileManager.NameI(fileManager.NextChar, FileManager::CREATE);
	fileManager.MakNode(2);
}

//fin����
void fin() {
	//��Windowsϵͳ�е��ļ�
	FILE* pFile;
	pFile = fopen(space.pathParam, "rb");
	if (pFile == NULL) {
		exit(-1);
	}
	//��ȡ�ļ���С
	fseek(pFile, 0, SEEK_END);
	int lSize = ftell(pFile);
	rewind(pFile);
	//���ļ���ȡ���ڴ�
	fread(space.buffer, 1, lSize, pFile);

	fileManager.Creat();
	state.dirp = (char*)state.arg;
	Inode* pInode = fileManager.NameI(fileManager.NextChar, FileManager::OPEN);
	int fd = 0;
	for (int i = 0; i < OpenFiles::NOFILES; i++) {
		File* tmp = state.ofiles.OpenFileTable[i];
		if (tmp != NULL && tmp->is_av == false && tmp->f_inode->i_number == pInode->i_number) {
			fd = i;
			break;
		}
	}
	state.arg[0] = fd;
	state.arg[1] = lSize;
	fileManager.Write();
	fclose(pFile);
}

void fout() {
	FILE* pFile;
	pFile = fopen((char*)state.arg, "wb");
	fileManager.Open();
	state.dirp = space.pathParam;
	int fd = 0;
	Inode* pInode = fileManager.NameI(fileManager.NextChar, FileManager::OPEN);
	if (pInode == NULL || pInode->i_mode == 2) {
		return;
	}
	for (int i = 0; i < OpenFiles::NOFILES; i++) {
		File* tmp = state.ofiles.OpenFileTable[i];
		if (tmp != NULL && tmp->is_av == false && tmp->f_inode->i_number == pInode->i_number) {
			fd = i;
			break;
		}
	}
	int lSize = pInode->i_size;
	state.arg[0] = fd;
	state.arg[1] = lSize;
	fileManager.Read();
	fwrite(space.buffer, lSize, 1, pFile);
	fileManager.Close();
	fclose(pFile);
}

//shutdown����
void shutdown() {
	fileSystem.Update();
	inodeTable.UpdateInodeTable();
	bufferManager.Bflush();
}

//exit����
void exit() {
	//do nothing
}

void test() {
	Inode* pInode = new Inode;
	cout << pInode->Bmap(1000) << endl;
}

int main() {
	ifstream f("SecondaryFS.img");
	if (!f.good()) {
		cout << "no disk��want format?(y/n)��" << endl;
		char choice;
		while (true) {
			choice = _getch();
			if (choice == 'y') {
				diskManager.createDisk();
				format();
				break;
			}
			else if (choice == 'n') {
				cout << "already exit" << endl;
				return 0;
			}
		}
	}
	else {
		diskManager.openDisk();
	}

	//ϵͳ��ʼ��
	fileSystem.LoadSuperBlock(); //���볬����
	fileManager.rootDirInode = inodeTable.IGet(1); //�����Inode���ڴ�
	state.cdir = fileManager.rootDirInode;
	
	string instruction;
	while (true) {
		cout << state.curdir << ":>";
		getline(cin, instruction);
		string op = transInstruction(instruction);
		if (op == "open") {
			open();
		}
		else if (op == "close") {
			close();
		}
		else if (op == "lseek") {
			lseek();
		}
		else if (op == "read") {
			read();
		}
		else if (op == "write") {
			write();
		}
		else if (op == "create") {
			create();
		}
		else if (op == "cat") {
			cat();
		}
		else if (op == "link") {
			link();
		}
		else if (op == "unlink") {
			unlink();
		}
		else if (op == "rm") {
			rm();
		}
		else if (op == "ls") {
			ls();
		}
		else if (op == "cd") {
			cd();
		}
		else if (op == "mkdir") {
			mkdir();
		}
		else if (op == "fin") {
			fin();
		}
		else if (op == "fout") {
			fout();
		}
		else if (op == "shutdown") {
			shutdown();
			break;
		}
		else if (op == "exit") {
			exit();
			break;
		}
		else if (op == "format") {
			format();
			fileSystem.LoadSuperBlock(); //���볬����
			fileManager.rootDirInode = inodeTable.IGet(1); //�����Inode���ڴ�
			state.cdir = fileManager.rootDirInode;
		}
		else {
			cout << "instruction error" << endl;
		}
	}
	cout << "already exit" << endl;

	return 0;
}