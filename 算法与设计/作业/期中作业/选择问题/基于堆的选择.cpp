#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <fstream>
#include <time.h>

void findTopK(std::vector<int>& arr, int k) {
    std::priority_queue<int, std::vector<int>, std::less<int>> minHeap;

    for (int i = 0; i < arr.size(); i++) {
        if (i < k) { 
            minHeap.push(arr[i]);
        } else { 
            if (arr[i] < minHeap.top()) {
                minHeap.pop();
                minHeap.push(arr[i]);
            }
        }
    }

    std::cout << "��" << k << "С��Ԫ���ǣ�" << minHeap.top() << std::endl;
}

int main() {
	clock_t start,end;
    start = clock(); 
    int n, k;
    std::cin >> n;
    std::cin >> k;
    std::vector<int> arr(n);
    for (int i = 0; i <n; ++i) {
    	std::cin >> arr[i];
	}

    findTopK(arr, k);
    end = clock();   //����ʱ��
    std::cout<<"time = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<std::endl;  //���ʱ�䣨��λ����

    return 0;
}

