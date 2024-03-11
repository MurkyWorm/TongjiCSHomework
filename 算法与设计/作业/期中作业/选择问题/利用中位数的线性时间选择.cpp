#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

// 获取数组中的中位数
int getMedian(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end());  // 对数组排序
    return arr[arr.size() / 2];          // 返回中位数
}

// 利用中位数的线性时间选择算法
int linearSelect(std::vector<int>& arr, int k, int left, int right) {
    if (left == right) {   // 只有一个元素
        return arr[left];
    }
    // 计算中位数
    int pivot = getMedian(arr);
    // 划分数组
    std::vector<int> leftArr, rightArr, equalArr;
    for (int i = left; i <= right; ++i) {
        if (arr[i] < pivot) {
            leftArr.push_back(arr[i]);
        } else if (arr[i] > pivot) {
            rightArr.push_back(arr[i]);
        } else {
            equalArr.push_back(arr[i]);
        }
    }
    if (k <= leftArr.size()) {   // 第 k 小的数在左半边
        return linearSelect(leftArr, k, 0, leftArr.size() - 1);
    } else if (k <= leftArr.size() + equalArr.size()) {   // 第 k 小的数是中位数
        return pivot;
    } else {    // 第 k 小的数在右半边
        return linearSelect(rightArr, k - leftArr.size() - equalArr.size(), 0, rightArr.size() - 1);
    }
}

int main() {
	clock_t start,end;
    start = clock();
    int n, k;
    std::cin >> n >> k;
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    int result = linearSelect(arr, k, 0, arr.size() - 1);
    std::cout << "第 " << k << " 小的元素是：" << result << std::endl;
    end = clock();   //结束时间
    std::cout<<"time = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<std::endl;  //输出时间（单位：ｓ）

    return 0;
}

