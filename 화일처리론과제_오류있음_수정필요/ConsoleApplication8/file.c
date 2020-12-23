#include <stdio.h>
typedef struct Record {
	// 레코드 정의부    
	int code;
	int key; //고객번호
	char name[15];
	char addr[40];
	char car[10];
	char company[10];
	char tel[8];
	char filler[2];
} Record;

FILE *masterFile; // 마스터 파일
FILE *transFile;        // 트랜잭션 파일
FILE *new_masterFile;        // 뉴 마스터 파일 
Record master;                // 마스터 파일 레코드 버퍼
Record trans;                // 트랜잭션 파일 레코드 버퍼

char szBuffer[100];            // 임시 버퍼 
void sequentialUpdate();    // 순차파일 갱신
void getNextTrans();        // 다음 트랜젝션 파일 레코드
void getNextMaster();        // 다음 마스터 파일 레코드
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
	// 삽입, 변경, 삭제 트랜잭션을 처리   
	// 하나의 마스터 레코드에 하나의 트랜잭션만 수행   
	// 갱신 코드 I: 삽입, C: 수정, D: 삭제    

	masterFile = fopen("masterFile.dat", "r");
	transFile = fopen("transFile.dat", "r");
	new_masterFile = fopen("newmasterFile.dat", "w");
	getNextTrans();
	getNextMaster();

	while (master.key != EOF && trans.key != EOF) {
		// 두 파일의 끝에 모두 다다를 때 까지 반복      
		if (master.key < trans.key) {
			// 마스터 레코드에 적용할 트랜잭션이 없는 경우        
			fprintf(new_masterFile, "%d %s %s %s %s %s\n",
				master.key, master.name, master.addr, master.car, master.company, master.tel);
			printf("%d %s %s %s %s %s\n",
				master.key, master.name, master.addr, master.car, master.company, master.tel);
			getNextMaster();
		}
		else { // master.key >= trans.key인 경우          
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
			else { // master.key > trans.key인 경우  
				noMatch();
			}
		}
	}     // 둘중 한 파일이 끝났을 시 뒷처리   
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
		// 트랜잭션 파일이 EOF(파일의 끝 일때)     
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
		// 마스터 파일이 EOF(파일의 끝 일때)     
		master.key = EOF;
	else
		fscanf(masterFile, "%d %s %s %s %s %s",
			&master.key, master.name, master.addr, master.car, master.company, master.tel);
}
void noMatch()    // master.key > trans.key인 경우
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