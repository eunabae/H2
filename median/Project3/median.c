#include<stdio.h>
#define Size 45
#define G_Size 5
#define M_Size 9

int sort(int arr[], int size) {
	int i, j, key;
	for (i = 1; i < size;i++) {
		key = arr[i];
		for (j = i - 1; j >= 0 && arr[j] > key;j--)
			arr[j + 1] = arr[j];
		arr[j + 1] = key;
	}
}

int main() {
	int median1=0;
	int median2=0;
	int temp0[G_Size], temp1[G_Size], temp2[G_Size], temp3[G_Size], temp4[G_Size], temp5[G_Size], temp6[G_Size], temp7[G_Size], temp8[G_Size];
	int temp[M_Size];
	int i = 0;
	
	int arr[Size] = {48, 43, 38, 33, 28, 23, 18, 13, 8, 
					49, 44, 39, 34, 29, 24, 19, 14, 9,
					50, 45, 40, 35, 30, 25, 20, 15, 10,
					51, 46, 41, 36, 31, 26, 21, 16, 53,
					52, 47, 42, 37, 32, 27, 22, 17, 54};
	
	for (i = 0; i < Size; i++) {
		switch (i % M_Size)
		{
		case 0: temp0[i / M_Size] = arr[i]; break;
		case 1: temp1[i / M_Size] = arr[i]; break;
		case 2: temp2[i / M_Size] = arr[i]; break;
		case 3: temp3[i / M_Size] = arr[i]; break;
		case 4: temp4[i / M_Size] = arr[i]; break;
		case 5: temp5[i / M_Size] = arr[i]; break;
		case 6: temp6[i / M_Size] = arr[i]; break;
		case 7: temp7[i / M_Size] = arr[i]; break;
		case 8: temp8[i / M_Size] = arr[i]; break;
		default:
			break;
		}
	}

	sort(temp0, G_Size);	sort(temp1, G_Size);		sort(temp2, G_Size);		sort(temp3, G_Size);		sort(temp4, G_Size);
	sort(temp5, G_Size);		sort(temp6, G_Size);		sort(temp7, G_Size);		sort(temp8, G_Size);
	
	temp[0] = temp0[G_Size / 2 ];
	temp[1] = temp1[G_Size / 2 ];
	temp[2] = temp2[G_Size / 2 ];
	temp[3] = temp3[G_Size / 2 ];
	temp[4] = temp4[G_Size / 2 ];
	temp[5] = temp5[G_Size / 2 ];
	temp[6] = temp6[G_Size / 2 ];
	temp[7] = temp7[G_Size / 2 ];
	temp[8] = temp8[G_Size / 2 ];

	sort(temp,M_Size);
	
	median1 = temp[M_Size/ 2];

	printf("median of medians = %d\n", median1);
	
	
	median2 = arr[Size / 2];
	printf("sort median = %d\n", median2);

}