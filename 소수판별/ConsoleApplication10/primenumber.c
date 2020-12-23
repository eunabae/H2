#include <stdio.h>
#include <math.h>

int main(void) {

	long long num=1;
	long long i, to;
	int count = 0;
	
	for (i = 0;i < 61;i++) {
		num = num * 2;
	}
	num = num - 1;
	printf("%lld\n", num);//num = 2^61-1

	to = sqrt(num)+1;
	printf("to : %lld\n", to);

	for (i = 2;i < to;i++) {
		if (num % i == 0) {
			printf("num : %lld\n i : %lld\n ==> not prime\n", num, i, num%i);
			count++;
			break;
		}
		else continue;
	}
	
	if(count ==0)	printf("prime\n");

	return 0;
}


//2^61-1 = prime number , time = 16.67s , spec = i3-7100U cpu (RAM=8GB)