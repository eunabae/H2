#include <stdio.h>

#define MAX_TERMS 101

struct {
	float coef;
	int expon;
}terms[MAX_TERMS] = { {8,3},{7,1},{1,0},{10,3},{3,2},{1,0} };  // A=8x^3+7x+1, B=10x^3+3X^2+1

int avail = 6;  // ��� ���� ���� ��ġ

char compare(int a, int b) {
	if (a > b) return '>';
	else if (a == b) return '=';
	if (a < b) return '<';
}

void attach(float coef, int expon) {
	if (avail > MAX_TERMS) {
		fprintf(stderr, "���� ���� �ʰ�");
		exit(1);
	}
	terms[avail].coef = coef;
	terms[avail++].expon = expon;  // ��� ���� �� �迭 �̵�, avail�� ����
}

poly_add(int As, int Ae, int Bs, int Be, int *Cs, int *Ce)  // C���׽� ��� ��� �߰��Ǹ鼭 Cs, Ce �̵��ϱ� ������ ������ ���� ���
{
	float tempcoef;
	*Cs = avail;
	while (As<=Ae && Bs<=Be)
		switch (compare(terms[As].expon, terms[Bs].expon)) {  //������
		case '>':   // A ������ �� ũ�Ƿ�
			attach(terms[As].coef, terms[As].expon);  // A�� ���� �ٿ����� 
			As++;	break;
		case '=':   // ������ �����Ƿ�
			tempcoef = terms[As].coef + terms[Bs].coef;
			if(tempcoef)
			attach(tempcoef, terms[As].expon);  // A, B ���� ���, ���� �����ϹǷ� As ��� Bs ����
			Bs++;	As++;	break;
		case '<':   // B ������ �� ũ�Ƿ�
			attach(terms[Bs].coef, terms[Bs].expon);  // B�� ���� �ٿ����� 
			Bs++;	break;
		} //���� while�� �ɸ��� �κ�
	
	for (;As <= Ae;As++)
		attach(terms[As].coef, terms[As].expon);  //��� �� ���� A�� �� �̵�
	for (;Bs <= Be;Bs++)
		attach(terms[Bs].coef, terms[Bs].expon);  //��� �� ���� B�� �� �̵�
	*Ce = avail - 1;  // ���� acail�� ���� �׸� ���� ��ġ -> ��� �������Ƿ� C���׽��� ������ ���� ��ġ�� �̵���Ű�� -1
}


void main() {
	int Cs, Ce;
	int expon, coef;
	poly_add(0, 2, 3, 5, &Cs, &Ce); //0,2: A��ġ ,3,5: B��ġ, C�� �����ͺ����̹Ƿ� &�ٿ��� �ּҰ� �Ҵ�
	int As = 0;
	int Bs = 3;
	printf("���׽� A: ");
	for (;As <= 2; As++) {				// ���׽� C����Ʈ
		expon = terms[As].expon;
		coef = (int)terms[As].coef;
		printf("%dx^%d", coef, expon);
		for (;As < 2;) { printf(" + "); break; }
	}
	printf("\n");
	

	printf("���׽� B: ");
	for (;Bs <= 5; Bs++) {				// ���׽� C����Ʈ
		expon = terms[Bs].expon;
		coef = (int)terms[Bs].coef;
		printf("%dx^%d", coef, expon);
		for (;Bs < 5;) { printf(" + "); break; }
	}
	printf("\n");
	

	printf("���׽� C(���): ");
	for (;Cs <= Ce;	Cs++) {				// ���׽� C����Ʈ
			expon = terms[Cs].expon;
			coef = (int)terms[Cs].coef;
			printf("%dx^%d", coef, expon);
			for (;Cs < Ce;) { printf(" + "); break; }
		}
	printf("\n");

}