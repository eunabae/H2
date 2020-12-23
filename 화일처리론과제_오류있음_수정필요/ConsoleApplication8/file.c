#include <stdio.h>
typedef struct Record {
	// ���ڵ� ���Ǻ�    
	int code;
	int key; //����ȣ
	char name[15];
	char addr[40];
	char car[10];
	char company[10];
	char tel[8];
	char filler[2];
} Record;

FILE *masterFile; // ������ ����
FILE *transFile;        // Ʈ����� ����
FILE *new_masterFile;        // �� ������ ���� 
Record master;                // ������ ���� ���ڵ� ����
Record trans;                // Ʈ����� ���� ���ڵ� ����

char szBuffer[100];            // �ӽ� ���� 
void sequentialUpdate();    // �������� ����
void getNextTrans();        // ���� Ʈ������ ���� ���ڵ�
void getNextMaster();        // ���� ������ ���� ���ڵ�
void noMatch();

int main(void) {
	char s[100];

	masterFile = fopen("masterFile.dat", "w");
	transFile = fopen("transFile.dat", "w");
	
	printf("\ninput old master\n");
	if ((masterFile = fopen("masterFile.dat", "w")) == NULL) {
		printf("File could not be opened\n");
	}
	else {
		printf("Enter the key, name, addr, car, company and tel \n");
		printf("Enter the EOF to end input\n");
		printf("? ");
		scanf("%d %s %s %s %s %s", &master.key, master.name, master.addr, master.car, master.company, master.tel);
		while (!feof(stdin)) {
			fprintf(masterFile, "%d %s %s %s %s %s\n", master.key, master.name, master.addr, master.car, master.company, master.tel);
			printf("? ");
			scanf("%d %s %s %s %s %s", &master.key, master.name, master.addr, master.car, master.company, master.tel);
		}
		fclose(masterFile);
	}
	
	printf("\ninput transaction\n");
	if ((transFile = fopen("transFile.dat", "w")) == NULL) {
		printf("File could not be opened\n");
	}
	else {
		printf("Enter the key, name, addr, car, company, tel and code\n");;
		printf("Enter the EOF to end input\n");
		printf("? ");
		scanf("%d %d %s %s %s %s %s", &trans.code, &trans.key, trans.name, trans.addr, trans.car, trans.company, trans.tel);
		while (!feof(stdin)) {
			fprintf(transFile, "%d %d %s %s %s %s %s\n", trans.code, trans.key, trans.name, trans.addr, trans.car, trans.company, trans.tel);
			printf("? ");
			scanf("%d %d %s %s %s %s %s", &trans.code, &trans.key, trans.name, trans.addr, trans.car, trans.company, trans.tel);
		}
		fclose(transFile);
	}
	sequentialUpdate();

	return 0;
}

void sequentialUpdate() {
	// ����, ����, ���� Ʈ������� ó��   
	// �ϳ��� ������ ���ڵ忡 �ϳ��� Ʈ����Ǹ� ����   
	// ���� �ڵ� I: ����, C: ����, D: ����    

	masterFile = fopen("masterFile.dat", "r");
	transFile = fopen("transFile.dat", "r");
	new_masterFile = fopen("newmasterFile.dat", "w");
	getNextTrans();
	getNextMaster();

	while (master.key != EOF && trans.key != EOF) {
		// �� ������ ���� ��� �ٴٸ� �� ���� �ݺ�      
		if (master.key < trans.key) {
			// ������ ���ڵ忡 ������ Ʈ������� ���� ���        
			fprintf(new_masterFile, "%d %s %s %s %s %s\n",
				master.key, master.name, master.addr, master.car, master.company, master.tel);
			printf("%d %s %s %s %s %s\n",
				master.key, master.name, master.addr, master.car, master.company, master.tel);
			getNextMaster();
		}
		else { // master.key >= trans.key�� ���          
			if (master.key == trans.key) {
				switch (trans.code)
				{
				case 0:
					printf("error: duplicate record key(%d)\n", trans.key);
					getNextTrans();
					break;
				case 1:
					fprintf(new_masterFile, "%d %s %s %s %s %s\n",
						master.key, master.name, master.addr, trans.car, master.company, master.tel);
					printf("%d %s %s %s %s %s\n",
						master.key, master.name, master.addr, trans.car, master.company, master.tel);
					getNextTrans();
					getNextMaster();
					break;
				case 3:
					fprintf(new_masterFile, "%d %s %s %s %s %s\n",
						master.key, master.name, trans.addr, master.car, master.company, master.tel);
					printf("%d %s %s %s %s %s\n",
						master.key, master.name, trans.addr, master.car, master.company, master.tel);
					getNextTrans();
					getNextMaster();
					break;
				case 5:
					fprintf(new_masterFile, "%d %s %s %s %s %s\n",
						master.key, master.name, master.addr, master.car, trans.company, master.tel);
					printf("%d %s %s %s %s %s\n",
						master.key, master.name, master.addr, master.car, trans.company, master.tel);
					getNextTrans();
					getNextMaster();
					break;
				case 4:
					fprintf(new_masterFile, "%d %s %s %s %s %s\n",
						master.key, master.name, master.addr, master.car, master.company, trans.tel);
					printf("%d %s %s %s %s %s\n",
						master.key, master.name, master.addr, master.car, master.company, trans.tel);
					getNextTrans();
					getNextMaster();
					break;
				case 2:
					getNextMaster();
					getNextTrans();
					break;
				default:
					printf("error: invalid update code(%c)\n", trans.code);
					getNextTrans();
					break;
				} // end case       

			}
			else { // master.key > trans.key�� ���  
				noMatch();
			}
		}
	}     // ���� �� ������ ������ �� ��ó��   
	if (master.key == EOF) {
		while (trans.key != EOF)
			noMatch();
	}
	if (trans.key == EOF) {
		while (master.key != EOF) {
			fprintf(new_masterFile, "%d %s %s %s %s %s\n",
				master.key, master.name, master.addr, master.car, master.company, master.tel);
			printf("%d %s %s %s %s %s\n",
				master.key, master.name, master.addr, master.car, master.company, master.tel);
			getNextMaster();
			if (master.key != EOF)
				fputc('\n', new_masterFile);
		}
	}

	fclose(masterFile);
	fclose(transFile);
	fclose(new_masterFile);
}
void getNextTrans() {
	if (feof(transFile))
		// Ʈ����� ������ EOF(������ �� �϶�)     
		trans.key = EOF;
	else {
		fgets(szBuffer, sizeof(szBuffer), transFile);
		if (szBuffer[0] == 2)
			sscanf(szBuffer, "%d %d", &trans.code, &trans.key);
		else
			sscanf(szBuffer, "%d %d %s %s %s %s %s",
				&trans.code, &trans.key, trans.name, trans.addr, trans.car, trans.company, trans.tel);
	}
}
void getNextMaster() {
	if (feof(masterFile))
		// ������ ������ EOF(������ �� �϶�)     
		master.key = EOF;
	else
		fscanf(masterFile, "%d %s %s %s %s %s",
			&master.key, master.name, master.addr, master.car, master.company, master.tel);
}
void noMatch()    // master.key > trans.key�� ���
{
	switch (trans.code) {
	case 0:
		fprintf(new_masterFile, "%d %s %s %s %s %s\n",
			trans.key, trans.name, trans.addr, trans.car, trans.company, trans.tel);
		printf("%d %s %s %s %s %s\n",
			trans.key, trans.name, trans.addr, trans.car, trans.company, trans.tel);
		getNextTrans();
		if (trans.key != EOF)
			fputc('\n', new_masterFile);
		break;
	case 1:
		printf("error: no matching master record for trans key(%d)\n", trans.key);
		getNextTrans();
		break;
	case 2:
		printf("error: no matching master record for trans key(%d)\n", trans.key);
		getNextTrans();
		break;
	case 3:
		printf("error: no matching master record for trans key(%d)\n", trans.key);
		getNextTrans();
		break;
	case 4:
		printf("error: no matching master record for trans key(%d)\n", trans.key);
		getNextTrans();
		break;
	case 5:
		printf("error: no matching master record for trans key(%d)\n", trans.key);
		getNextTrans();
		break;
	default:
		printf("error: invalid update code(%c)\n", trans.code);
		getNextTrans();
		break;
	}
}