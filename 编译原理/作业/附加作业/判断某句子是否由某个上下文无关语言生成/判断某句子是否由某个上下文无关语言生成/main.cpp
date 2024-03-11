#include <iostream>
#include <vector>
#include <conio.h>
#include <map>
#include <string.h>
#include <stack>
using namespace std;

int main() {
	/*进行文法的输入*/
	char initChar;
	vector<char> variaSet;
	vector<char> endSet;
	map<char, vector<string>> generatives;
	//输入起始符
	cout << "请输入起始符：";
	cin >> initChar;
	variaSet.push_back(initChar);
	//输入中间变元集
	while (true) {
		char isEnd;
		cout << "是否继续输入中间变元？(y/n)：";
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
		cout << endl << "请输入中间变元：";
		cin >> varia;
		variaSet.push_back(varia);
	}
	cout << endl;
	//输入终结符集
	while (true) {
		char isEnd;
		cout << "是否继续输入终结符？(y/n)：";
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
		cout << endl << "请输入终结符：";
		cin >> end;
		endSet.push_back(end);
	}
	cout << endl;
	//输入生成式
	while (true) {
		char isEnd;
		cout << "是否继续输入生成式？(y/n)：";
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
		cout << endl << "请输入生成式左端字符：";
		cin >> leftSide;
		cout << "请输入生成式右端字符串（$字符代表空串）：";
		cin >> rightSide;
		if (generatives.count(leftSide) == 0) {
			vector<string> temp;
			generatives[leftSide] = temp;
		}
		generatives[leftSide].push_back(rightSide);
	}

	/*打印输入的上下文无关文法*/
	//打印起始符
	cout << endl << "起始符：" << initChar << endl;
	//打印变元集
	cout << "变元集：";
	for (int i = 0; i < variaSet.size(); i++) {
		cout << variaSet[i] << " ";
	}
	cout << endl;
	//打印终结符集
	cout << "终结符集：";
	for (int i = 0; i < endSet.size(); i++) {
		cout << endSet[i] << " ";
	}
	cout << endl;
	//打印生成式集
	cout << "生成式：" << endl;
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

	/*进行上下文无关语言的识别*/
	//输入需要判别的句子
	string sentence;
	cout << "请输入要判别的句子：";
	cin >> sentence;
	//初始化栈、轨迹和当前可能的分支
	vector<char> S;
	stack<string> trace;
	stack<int> branches;
	S.push_back(initChar);
	trace.push(string("" + initChar));
	branches.push(generatives[initChar].size());
	//进行深度优先搜索，寻找匹配结果
	while (true) {
		//判断当前表达式是否匹配
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
		//若匹配，则退出，该语句是该文法产生的
		if (isMatch) {
			cout << "该语句是由该上下文无关文法所产生的" << endl;
			break;
		}
		//若不匹配，则判断是否可能沿着当前路径派生出该句子
		bool canGener = true;

		if (!canGener) {
			trace.pop();
			if (trace.empty()) {
				cout << "该语句不能由该上下文无关文法生成" << endl;
				break;//栈已经弹空，说明不能再回退，该语句不能由该上下文无关文法生成
			}
			else {
				trace.pop();
				S.clear();
				branches.pop();
				for (int i = 0; i < trace.top().size(); i++) {
					S.push_back(trace.top()[i]);
				}
			}
		}//若不可能匹配，则进行回退
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
		}//若可能匹配，进行最右派生
	}
}