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
//	cout<<"�����ڴ����"<<endl;
//	cin>>n;
//	cout<<"�����������"<<endl;
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
//	cout << "ȱҳ����:" << cnt <<endl;
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
	
	cout<<"�����ڴ����"<<endl;
	cin>>n;
	cout<<"�����������"<<endl;
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
	cout << "ȱҳ����:" << cnt <<endl;
	return 0;
}
