#include <stdio.h>
#include <stdlib.h>
#include <time.h>
# define MAX 100000

long long sorted[MAX]; 

void rnum(long long arr[]) {
	srand((unsigned int)time(NULL));
	for (long long i = 0; i < MAX;i++) {
		arr[i] = rand() % 100000;
	}
}


void check(long long arr[]) {
	for (long long i = 0; i < MAX; i++) {
		if (arr[i] <= arr[i + 1]) continue;
		else if (i = MAX - 1) {
			printf("finish\n");
			break;
		}
		else {
			printf("false\n"); break;
		}
	}
}
// �߰����� ������ �ʿ�
// i: ���ĵ� ���� ����Ʈ�� ���� �ε���
// j: ���ĵ� ������ ����Ʈ�� ���� �ε���
// k: ���ĵ� ����Ʈ�� ���� �ε���
/* 2���� ������ �迭 list[left...mid]�� list[mid+1...right]�� �պ� ���� */
/* (������ ���ڵ��� ���ĵǴ� ����) */

void merge(long long list[], long long left, long long mid, long long right) {
	long long i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	/* ���� ���ĵ� list�� �պ� */
	while (i <= mid && j <= right) {
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}

	// ���� �ִ� ������ �ϰ� ����
	if (i>mid) {
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	}
	// ���� �ִ� ������ �ϰ� ����
	else {
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	}

	// �迭 sorted[](�ӽ� �迭)�� ����Ʈ�� �迭 list[]�� �纹��
	for (l = left; l <= right; l++) {
		list[l] = sorted[l];
	}
}

// �պ� ����
void merge_sort(long long list[], long long left, long long right) {
	long long mid;

	if (left<right) {
		mid = (left + right) / 2; // �߰� ��ġ�� ����Ͽ� ����Ʈ�� �յ� ���� -����(Divide)
			merge_sort(list, left, mid); // ���� �κ� ����Ʈ ���� -����(Conquer)
		merge_sort(list, mid + 1, right); // ���� �κ� ����Ʈ ���� -����(Conquer)
		merge(list, left, mid, right); // ���ĵ� 2���� �κ� �迭�� �պ��ϴ� ���� -����(Combine)
	}
}

void main() {
	clock_t start, end;
	long long i;
	long long n = MAX;
	long long arr[MAX];
	for (i = 0; i < MAX;i++) {
		arr[i] = 0;
	}
	rnum(arr);

	// �պ� ���� ����(left: �迭�� ���� = 0, right: �迭�� �� = 7)
	start = clock();
	merge_sort(arr, 0, n - 1);
	end = clock();

	// ���� ��� ���
	/*
	for (i = 0; i<n; i++) {
		printf("%lld\n", arr[i]);
	}*/
	printf("�ɸ� �ð�: %f�� \n", (double)(end - start) / 1000);
	check(arr);
}
