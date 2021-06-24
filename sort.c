#pragma warning(disable:4996)

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define INF 2123456789
#define N 20000

void swap(int*, int*);
void selectionSort(int[], int);
void bubbleSort(int[], int);
void insertionSort(int[], int);
void mergeSort(int[], int, int);
void merge(int[], int, int, int);
void quickSort(int[], int, int);
int partition(int[], int, int);
void heapSort(int[], int);
void heapify(int[], int, int);

int main() {
	srand((unsigned int)time(NULL));
	int arr[N];
	for (int i = 0; i < N; i++) 
		arr[i] = rand() % N;

	clock_t start, finish;
	double time = 0.0;

	start = clock();
	selectionSort(arr, N);
	finish = clock();
	time = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("selectionSort_Time : %lf\n\n", time);

	for (int i = 0; i < N; i++)
		arr[i] = rand() % N;
	start = clock();
	bubbleSort(arr, N);
	finish = clock();
	time = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("bubbleSort_Time : %lf\n\n", time);

	for (int i = 0; i < N; i++)
		arr[i] = rand() % N;
	start = clock();
	insertionSort(arr, N);
	finish = clock();
	time = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("insertionSort_Time : %lf\n\n", time);

	for (int i = 0; i < N; i++)
		arr[i] = rand() % N;
	start = clock();
	mergeSort(arr, 0, N-1);
	finish = clock();
	time = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("mergeSort_Time : %lf\n\n", time);

	for (int i = 0; i < N; i++)
		arr[i] = rand() % N;
	start = clock();
	quickSort(arr, 0, N-1);
	finish = clock();
	time = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("quickSort_Time : %lf\n\n", time);

	for (int i = 0; i < N; i++)
		arr[i] = rand() % N;
	start = clock();
	heapSort(arr, N);
	finish = clock();
	time = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("heapSort_Time : %lf\n\n", time);


	return 0;
}

/*
	���ڷ� ���� �� ���� ��ȯ�ϴ� �Լ�
	�Լ� ���� �Ŀ��� ��ȯ�� ���� �����ϱ� ����
	������ ���
*/

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
	�� �� index���� �����Ͽ� ���� ���Ѵ�.
	�ִ��� ã���� �迭�� �� �ڷ� ������.
*/

void selectionSort(int arr[], int n) {
	for (int i = n - 1; i >= 0; i--) {
		int max = -INF;
		int index = -INF;
		for (int j = i; j >= 0; j--) {
			if (arr[j] > max) {
				max = arr[j];
				index = j;
			}
		}
		swap(&arr[index], &arr[i]);
	}
}

/*
	i���� ���� j�� ���ؼ� ��� �迭�� ���� ���� ��
	������������ �����Ѵ�
*/

void bubbleSort(int arr[], int n) {
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < i; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}

/*
	�迭���� arr[1]���� arr[n-1]���� �ڽź��� ����
	index�� �ִ� ���� �ڽź��� Ŭ ��� �ٲ��ش�
*/

void insertionSort(int arr[], int n) {
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (arr[i] < arr[j]) {
				swap(&arr[i], &arr[j]);
			}
		}
	}
}


/*
	index�� 0���� n-1���� �̹Ƿ� �� �߾Ӱ��� mid�� �����Ѵ�
	�׸��� ���ۺ��� mid, mid+1���� ������ ����Լ��� ȣ���Ѵ�
	�׸��� ���� �����ϰ� �����ָ� mergeSort�� �ȴ�
*/

void mergeSort(int arr[], int p, int r) {
	int mid;
	if (p < r) {
		mid = (p + r) / 2;
		mergeSort(arr, p, mid);
		mergeSort(arr, mid + 1, r);
		merge(arr, p, mid, r);
	}
}

/*
	mergeSort���� �������� �迭�� �����ϰ� �����ִ� �Լ�
	tmp�� ���ĵ� ���� �����ϰ� �������� arr�� ������ �ش�
*/

void merge(int arr[], int p, int q, int r) {
	int low = p;
	int mid = q + 1;
	int high = r;
	int tmp[N];
	int index = 0;
	while (low <= q && mid <= r) {
		if (arr[low] < arr[mid])
			tmp[index++] = arr[low++];
		else
			tmp[index++] = arr[mid++];
	}
	if (low > q)
		for (int i = mid; i <= r; i++)
			tmp[index++] = arr[i];
	else
		for (int i = low; i <= q; i++)
			tmp[index++] = arr[i];

	for (int i = p; i <= r; i++)
		arr[i] = tmp[i - p];
}

/*
	���ڷ� �޾ƿ� �迭�� �糡 index�� ���� ������ ū ���
	partition�� �����ϰ� ����Լ��� ȣ���Ѵ�
*/

void quickSort(int arr[], int p, int r) {
	if (p < r) {
		int q = partition(arr, p, r);
		quickSort(arr, p, q - 1);
		quickSort(arr, q, r);
	}
}

/*
	�� ������ pivot���� �����ϰ� ���ʺ��ʹ� pivot���� ū ����
	�����ʺ��ʹ� pivot���� ���� ���� ã�´�
	�� �� ���� �ٲ��� �� p�� �����Ѵ�
*/

int partition(int arr[], int p, int r) {
	int pivot = arr[r - 1];
	while (p <= r) {
		while (arr[p] < pivot)
			p++;
		while (arr[r] > pivot)
			r--;
		if (p <= r) {
			swap(&arr[p], &arr[r]);
			p++;
			r--;
		}
	}
	return p;
}

/*
	arr�� �� ������ ����� ��Ʈ��忡 �ִ� ���� �ּڰ��̴�
	���� ��Ʈ��带 �� ������ �ٲ��ְ� �ٽ� �� ������
	�ٲ��ִ� ������ �ݺ��Ѵ�
*/

void heapSort(int arr[], int n) {
	for (int i = n / 2 - 1; i >= 0; i--)heapify(arr, n, i);
	for (int i = n; i > 1; i--) {
		swap(&arr[0], &arr[i - 1]);
		heapify(arr, i - 1, 0);
	}
}

/*
	�����ڽ��� �θ�*2+1, �������ڽ��� �θ�*2+2�̴�
	�׸��� �׻� �ڽĺ��� �θ� ���� ���� ������ �Ѵ�
	�θ� ���ڷ� ���� ���� �ƴ� ��� ���� ���� �ٲٰ�
	����Լ��� ȣ���Ѵ�
*/

void heapify(int arr[], int h, int m) {
	int parent = m;
	int left = parent * 2 + 1;
	int right = parent * 2 + 2;
	if (left < h && arr[left] > arr[parent])parent = left;
	if (right < h && arr[right] > arr[parent])parent = right;
	if (parent != m) {
		swap(&arr[m], &arr[parent]);
		heapify(arr, h, parent);
	}
}