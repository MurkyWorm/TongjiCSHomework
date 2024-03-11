#include <iostream>
#include <vector>
#include <conio.h>
#include <map>
#include <string.h>
#include <stack>
using namespace std;

int main() {
	/*�����ķ�������*/
	char initChar;
	vector<char> variaSet;
	vector<char> endSet;
	map<char, vector<string>> generatives;
	//������ʼ��
	cout << "��������ʼ����";
	cin >> initChar;
	variaSet.push_back(initChar);
	//�����м��Ԫ��
	while (true) {
		char isEnd;
		cout << "�Ƿ���������м��Ԫ��(y/n)��";
		while (true) {
			isEnd = _getch();
			if (isEnd == 'y' || isEnd == 'n') {
				break;
			}
		}
		if (isEnd == 'n') {
			break;
		}
		char varia;
		cout << endl << "�������м��Ԫ��";
		cin >> varia;
		variaSet.push_back(varia);
	}
	cout << endl;
	//�����ս����
	while (true) {
		char isEnd;
		cout << "�Ƿ���������ս����(y/n)��";
		while (true) {
			isEnd = _getch();
			if (isEnd == 'y' || isEnd == 'n') {
				break;
			}
		}
		if (isEnd == 'n') {
			break;
		}
		char end;
		cout << endl << "�������ս����";
		cin >> end;
		endSet.push_back(end);
	}
	cout << endl;
	//��������ʽ
	while (true) {
		char isEnd;
		cout << "�Ƿ������������ʽ��(y/n)��";
		while (true) {
			isEnd = _getch();
			if (isEnd == 'y' || isEnd == 'n') {
				break;
			}
		}
		if (isEnd == 'n') {
			break;
		}
		char leftSide;
		string rightSide;
		cout << endl << "����������ʽ����ַ���";
		cin >> leftSide;
		cout << "����������ʽ�Ҷ��ַ�����$�ַ�����մ�����";
		cin >> rightSide;
		if (generatives.count(leftSide) == 0) {
			vector<string> temp;
			generatives[leftSide] = temp;
		}
		generatives[leftSide].push_back(rightSide);
	}

	/*��ӡ������������޹��ķ�*/
	//��ӡ��ʼ��
	cout << endl << "��ʼ����" << initChar << endl;
	//��ӡ��Ԫ��
	cout << "��Ԫ����";
	for (int i = 0; i < variaSet.size(); i++) {
		cout << variaSet[i] << " ";
	}
	cout << endl;
	//��ӡ�ս����
	cout << "�ս������";
	for (int i = 0; i < endSet.size(); i++) {
		cout << endSet[i] << " ";
	}
	cout << endl;
	//��ӡ����ʽ��
	cout << "����ʽ��" << endl;
	for (int i = 0; i < variaSet.size(); i++) {
		cout << variaSet[i] << " -> ";
		for (int j = 0; j < generatives[variaSet[i]].size(); j++) {
			cout << generatives[variaSet[i]][j];
			if (j != generatives[variaSet[i]].size() - 1) {
				cout << "/";
			}
		}
		cout << endl;
	}

	/*�����������޹����Ե�ʶ��*/
	//������Ҫ�б�ľ���
	string sentence;
	cout << "������Ҫ�б�ľ��ӣ�";
	cin >> sentence;
	//��ʼ��ջ���켣�͵�ǰ���ܵķ�֧
	vector<char> S;
	stack<string> trace;
	stack<int> branches;
	S.push_back(initChar);
	trace.push(string("" + initChar));
	branches.push(generatives[initChar].size());
	//�����������������Ѱ��ƥ����
	while (true) {
		//�жϵ�ǰ���ʽ�Ƿ�ƥ��
		bool isMatch = true;
		if (sentence.size() == S.size()) {
			for (int i = 0; i < S.size(); i++) {
				if (S[i] != sentence[i]) {
					isMatch = false;
				}
			}
		}
		else {
			isMatch = false;
		}
		//��ƥ�䣬���˳���������Ǹ��ķ�������
		if (isMatch) {
			cout << "��������ɸ��������޹��ķ���������" << endl;
			break;
		}
		//����ƥ�䣬���ж��Ƿ�������ŵ�ǰ·���������þ���
		bool canGener = true;

		if (!canGener) {
			trace.pop();
			if (trace.empty()) {
				cout << "����䲻���ɸ��������޹��ķ�����" << endl;
				break;//ջ�Ѿ����գ�˵�������ٻ��ˣ�����䲻���ɸ��������޹��ķ�����
			}
			else {
				trace.pop();
				S.clear();
				branches.pop();
				for (int i = 0; i < trace.top().size(); i++) {
					S.push_back(trace.top()[i]);
				}
			}
		}//��������ƥ�䣬����л���
		else {
			vector<char> temS;
			int recLastVaria = 0;
			for (int i = 0; i < S.size(); i++) {
				temS.push_back(S[i]);
				if (S[i] >= 'A' && S[i] <= 'Z') {
					recLastVaria = i;
				}
			}
			S.clear();
			for (int i = 0; i < recLastVaria; i++) {
				S.push_back(temS[i]);
			}
		}//������ƥ�䣬������������
	}
}