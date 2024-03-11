#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

// ��ȡ�����е���λ��
int getMedian(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end());  // ����������
    return arr[arr.size() / 2];          // ������λ��
}

// ������λ��������ʱ��ѡ���㷨
int linearSelect(std::vector<int>& arr, int k, int left, int right) {
    if (left == right) {   // ֻ��һ��Ԫ��
        return arr[left];
    }
    // ������λ��
    int pivot = getMedian(arr);
    // ��������
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
    if (k <= leftArr.size()) {   // �� k С����������
        return linearSelect(leftArr, k, 0, leftArr.size() - 1);
    } else if (k <= leftArr.size() + equalArr.size()) {   // �� k С��������λ��
        return pivot;
    } else {    // �� k С�������Ұ��
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
    std::cout << "�� " << k << " С��Ԫ���ǣ�" << result << std::endl;
    end = clock();   //����ʱ��
    std::cout<<"time = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<std::endl;  //���ʱ�䣨��λ����

    return 0;
}

