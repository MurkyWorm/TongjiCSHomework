#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <time.h>

// ���ѡ��pivot������Ԫ�ػ���ΪС��pivot�ʹ��ڵ���pivot��������
// ����pivot��λ��
int partition(std::vector<int>& arr, int left, int right) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(left, right);
    int pivotIndex = dis(gen);
    int pivotValue = arr[pivotIndex];

    // ��pivot������ĩβ
    std::swap(arr[pivotIndex], arr[right]);

    int storeIndex = left; // storeIndex��ʾС��pivot��Ԫ�ص��Ҳ�λ��
    for (int i = left; i < right; i++) {
        if (arr[i] < pivotValue) {
            std::swap(arr[i], arr[storeIndex]);
            storeIndex++;
        }
    }

    // ��pivot������storeIndex��λ��
    std::swap(arr[right], arr[storeIndex]);

    return storeIndex;
}

// ��arr�����в��ҵ�kС��Ԫ��
int linearSelect(std::vector<int>& arr, int k, int left, int right) {
    if (left == right) { // �߽�������ֻʣ��һ��Ԫ��
        return arr[left];
    }

    int pivotIndex = partition(arr, left, right); // ��Ԫ�ػ���ΪС��pivot�ʹ��ڵ���pivot�������֣�������pivot��λ��
    int pivotRank = pivotIndex - left + 1; // pivot�����������е���������pivot���Ԫ�صĸ���+1��

    if (k == pivotRank) { // �ҵ���kС��Ԫ��
        return arr[pivotIndex];
    } else if (k < pivotRank) { // ����ಿ�ֲ��ҵ�kС��Ԫ��
        return linearSelect(arr, k, left, pivotIndex - 1);
    } else { // ���Ҳಿ�ֲ��ҵ�k-pivotRankС��Ԫ��
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

    std::cout << "��" << k << "С��Ԫ���ǣ�" << result << std::endl;
    end = clock();   //����ʱ��
    std::cout<<"time = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<std::endl;  //���ʱ�䣨��λ����

    return 0;
}

