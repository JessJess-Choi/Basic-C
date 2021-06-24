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
	인자로 받은 두 수를 교환하는 함수
	함수 종료 후에도 교환한 값을 유지하기 위해
	포인터 사용
*/

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
	맨 끝 index부터 시작하여 값을 비교한다.
	최댓값을 찾으면 배열의 맨 뒤로 보낸다.
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
	i보다 작은 j에 대해서 모든 배열의 값을 비교한 후
	오름차순으로 정렬한다
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
	배열에서 arr[1]부터 arr[n-1]까지 자신보다 작은
	index에 있는 값이 자신보다 클 경우 바꿔준다
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
	index가 0부터 n-1까지 이므로 그 중앙값을 mid로 설정한다
	그리고 시작부터 mid, mid+1부터 끝까지 재귀함수를 호출한다
	그리고 나서 정렬하고 합쳐주면 mergeSort가 된다
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
	mergeSort에서 나누어진 배열을 정렬하고 합쳐주는 함수
	tmp에 정렬된 것을 저장하고 마지막에 arr에 복사해 준다
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
	인자로 받아온 배열의 양끝 index를 비교해 한쪽이 큰 경우
	partition을 진행하고 재귀함수를 호출한다
*/

void quickSort(int arr[], int p, int r) {
	if (p < r) {
		int q = partition(arr, p, r);
		quickSort(arr, p, q - 1);
		quickSort(arr, q, r);
	}
}

/*
	맨 끝값을 pivot으로 설정하고 왼쪽부터는 pivot보다 큰 값을
	오른쪽부터는 pivot보다 작은 값을 찾는다
	그 후 둘을 바꿔준 후 p를 리턴한다
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
	arr를 힙 구조로 만들면 루트노드에 있는 값이 최솟값이다
	따라서 루트노드를 맨 끝값과 바꿔주고 다시 힙 구조로
	바꿔주는 과정을 반복한다
*/

void heapSort(int arr[], int n) {
	for (int i = n / 2 - 1; i >= 0; i--)heapify(arr, n, i);
	for (int i = n; i > 1; i--) {
		swap(&arr[0], &arr[i - 1]);
		heapify(arr, i - 1, 0);
	}
}

/*
	왼쪽자식은 부모*2+1, 오른쪽자식은 부모*2+2이다
	그리고 항상 자식보다 부모가 작은 값을 가져야 한다
	부모가 인자로 받은 값이 아닐 경우 값을 서로 바꾸고
	재귀함수를 호출한다
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