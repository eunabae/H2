#include <stdio.h>

#define MAX_TERMS 101

struct {
	float coef;
	int expon;
}terms[MAX_TERMS] = { {8,3},{7,1},{1,0},{10,3},{3,2},{1,0} };  // A=8x^3+7x+1, B=10x^3+3X^2+1

int avail = 6;  // 결과 저장 시작 위치

char compare(int a, int b) {
	if (a > b) return '>';
	else if (a == b) return '=';
	if (a < b) return '<';
}

void attach(float coef, int expon) {
	if (avail > MAX_TERMS) {
		fprintf(stderr, "항의 개수 초과");
		exit(1);
	}
	terms[avail].coef = coef;
	terms[avail++].expon = expon;  // 모두 저장 후 배열 이동, avail값 증가
}

poly_add(int As, int Ae, int Bs, int Be, int *Cs, int *Ce)  // C다항식 계산 결과 추가되면서 Cs, Ce 이동하기 때문에 포인터 변수 사용
{
	float tempcoef;
	*Cs = avail;
	while (As<=Ae && Bs<=Be)
		switch (compare(terms[As].expon, terms[Bs].expon)) {  //차수비교
		case '>':   // A 차수가 더 크므로
			attach(terms[As].coef, terms[As].expon);  // A의 값을 붙여넣음 
			As++;	break;
		case '=':   // 차수가 같으므로
			tempcoef = terms[As].coef + terms[Bs].coef;
			if(tempcoef)
			attach(tempcoef, terms[As].expon);  // A, B 값을 계산, 차수 동일하므로 As 대신 Bs 가능
			Bs++;	As++;	break;
		case '<':   // B 차수가 더 크므로
			attach(terms[Bs].coef, terms[Bs].expon);  // B의 값을 붙여넣음 
			Bs++;	break;
		} //까지 while에 걸리는 부분
	
	for (;As <= Ae;As++)
		attach(terms[As].coef, terms[As].expon);  //계산 후 남은 A의 항 이동
	for (;Bs <= Be;Bs++)
		attach(terms[Bs].coef, terms[Bs].expon);  //계산 후 남은 B의 항 이동
	*Ce = avail - 1;  // 기존 acail은 다음 항목 삽입 위치 -> 계산 끝났으므로 C다항식의 마지막 값의 위치로 이동시키려 -1
}


void main() {
	int Cs, Ce;
	int expon, coef;
	poly_add(0, 2, 3, 5, &Cs, &Ce); //0,2: A위치 ,3,5: B위치, C는 포인터변수이므로 &붙여서 주소값 할당
	int As = 0;
	int Bs = 3;
	printf("다항식 A: ");
	for (;As <= 2; As++) {				// 다항식 C프린트
		expon = terms[As].expon;
		coef = (int)terms[As].coef;
		printf("%dx^%d", coef, expon);
		for (;As < 2;) { printf(" + "); break; }
	}
	printf("\n");
	

	printf("다항식 B: ");
	for (;Bs <= 5; Bs++) {				// 다항식 C프린트
		expon = terms[Bs].expon;
		coef = (int)terms[Bs].coef;
		printf("%dx^%d", coef, expon);
		for (;Bs < 5;) { printf(" + "); break; }
	}
	printf("\n");
	

	printf("다항식 C(결과): ");
	for (;Cs <= Ce;	Cs++) {				// 다항식 C프린트
			expon = terms[Cs].expon;
			coef = (int)terms[Cs].coef;
			printf("%dx^%d", coef, expon);
			for (;Cs < Ce;) { printf(" + "); break; }
		}
	printf("\n");

}