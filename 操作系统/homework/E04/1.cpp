#include<iostream>
#include<vector>
#include<algorithm>
using namespace std; 

//LRU 
//int main()
//{
//	vector<int> vl;
//	int n;
//	int num;
//	int tmp;
//	int cnt = 0;
//	
//	cout<<"输入内存块数"<<endl;
//	cin>>n;
//	cout<<"输入操作个数"<<endl;
//	cin>>num;
//	
//	for(int i = 0; i < num; ++i){
//		cin >> tmp;
//		auto it = find_if(vl.begin(),vl.end(),[=](int x){ return x == tmp;}
//		);
//		if(it == vl.end()){
//			if(vl.size() < n){
//				vl.push_back(tmp);
//			}
//			else{
//				vl.erase(vl.begin());
//				vl.push_back(tmp);
//			}
//			++cnt;
//			cout<<"*";
//		}
//		else{
//			vl.erase(it);
//			vl.push_back(tmp);
//		}
//		cout<< tmp <<":\t";
//		for_each(vl.begin(),vl.end(),[](int x){ cout<< x <<' ';
//		}) ;
//		cout<<endl;
//	}
//	cout << "缺页次数:" << cnt <<endl;
//	return 0;
//}

//FIFO
int main()
{
	vector<int> vl;
	int n;
	int num;
	int tmp;
	int cnt = 0;
	
	cout<<"输入内存块数"<<endl;
	cin>>n;
	cout<<"输入操作个数"<<endl;
	cin>>num;
	
	for(int i = 0; i < num; ++i){
		cin >> tmp;
		auto it = find_if(vl.begin(),vl.end(),[=](int x){ return x == tmp;}
		);
		
		if(it == vl.end()){
			if(vl.size() < n){
				vl.push_back(tmp);
			}
			else{
				vl.erase(vl.begin());
				vl.push_back(tmp);
			}
			++cnt;
			cout<<"*";
		}
		else{

		}
		cout<< tmp <<":\t";
		for_each(vl.begin(),vl.end(),[](int x){ cout<< x <<' ';
		}) ;
		cout<<endl;
	}
	cout << "缺页次数:" << cnt <<endl;
	return 0;
}
