#include <iostream>
using namespace std;

void heapify(int arr[], int n, int i) {
    int largest = i; 
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    int n, *arr;
	cin >> n;
	arr = (int*)malloc(n * sizeof(int));
	if (!arr)
		exit(-1);
	for (int i = 0; i < n; ++i) 
		cin >> arr[i];

    heapSort(arr, n);
    int same = arr[0];
    int count = 0;
    for (int i = 0; i < n; ++i) {
    	if (same == arr[i])
    		++count;
    	else {
    		same = arr[i];
    		count = 1;
		}
    	if (count > n/2) {
    		cout << arr[i];
    		return 0;
		}
	}
	cout << "ÎÞÖ÷ÔªËØ" <<endl; 

    return 0;
}

