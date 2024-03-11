#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <time.h>

// 随机选择pivot，并将元素划分为小于pivot和大于等于pivot两个部分
// 返回pivot的位置
int partition(std::vector<int>& arr, int left, int right) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(left, right);
    int pivotIndex = dis(gen);
    int pivotValue = arr[pivotIndex];

    // 将pivot交换到末尾
    std::swap(arr[pivotIndex], arr[right]);

    int storeIndex = left; // storeIndex表示小于pivot的元素的右侧位置
    for (int i = left; i < right; i++) {
        if (arr[i] < pivotValue) {
            std::swap(arr[i], arr[storeIndex]);
            storeIndex++;
        }
    }

    // 将pivot交换到storeIndex的位置
    std::swap(arr[right], arr[storeIndex]);

    return storeIndex;
}

// 在arr数组中查找第k小的元素
int linearSelect(std::vector<int>& arr, int k, int left, int right) {
    if (left == right) { // 边界条件：只剩下一个元素
        return arr[left];
    }

    int pivotIndex = partition(arr, left, right); // 将元素划分为小于pivot和大于等于pivot两个部分，并返回pivot的位置
    int pivotRank = pivotIndex - left + 1; // pivot在整个数组中的排名（即pivot左侧元素的个数+1）

    if (k == pivotRank) { // 找到第k小的元素
        return arr[pivotIndex];
    } else if (k < pivotRank) { // 在左侧部分查找第k小的元素
        return linearSelect(arr, k, left, pivotIndex - 1);
    } else { // 在右侧部分查找第k-pivotRank小的元素
        return linearSelect(arr, k - pivotRank, pivotIndex + 1, right);
    }
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
    int result = linearSelect(arr, k, 0, arr.size() - 1);

    std::cout << "第" << k << "小的元素是：" << result << std::endl;
    end = clock();   //结束时间
    std::cout<<"time = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<std::endl;  //输出时间（单位：ｓ）

    return 0;
}

