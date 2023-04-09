#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int enough(int* R,int* processrequest,int nofR);
void Rreturn(int* R, int* processallocation, int nofR);

int main() {
	int** pall;
	int** preq;
	int* R;
	int* P;
	int change = 1;
	int nofR = 0;
	int nofP = 0;
	int dead = 0;//setting variable

	FILE* fp = fopen("input.txt", "r");
	if (fp == NULL) {
		printf("Can't open input.txt");
		exit(1);
	}

	fscanf(fp, "%d %d", &nofP, &nofR);
	printf("Number of Process:%d\nNumber of Resource:%d\n\n", nofP, nofR);

	R = malloc(sizeof(int) * nofR);
	P = malloc(sizeof(int) * nofP);
	memset(P, 0, sizeof(int) * nofP);
	for (int i = 0; i < nofR; i++) {
		fscanf(fp, "%d", R+i);
		printf("Resource %d: %d\n", i+1, R[i]);
	}//input print

	pall = malloc(sizeof(int*) * nofP);
	preq = malloc(sizeof(int*) * nofP);
	for (int i = 0; i < nofP; i++) {
		pall[i] = malloc(sizeof(int) * nofR);
		preq[i] = malloc(sizeof(int) * nofR);
	} //make Allocation matrix and Request matrix

	printf("\nAllocation matrix:\n");
	for (int i = 0; i < nofP; i++) {
		printf("p%d: ", i + 1);
		for (int j = 0; j < nofR; j++) {
			fscanf(fp, "%d", pall[i]+j);
			R[j] -= pall[i][j];
			printf("%d ",pall[i][j]);
		}
		printf("\n");
	}//Allocation print

	printf("\nRequest matrix:\n");
	for (int i = 0; i < nofP; i++) {
		printf("p%d: ", i + 1);
		for (int j = 0; j < nofR; j++) {
			fscanf(fp, "%d", preq[i]+j);
			printf("%d ", preq[i][j]);
		}
		printf("\n");
	}//Requset print
	fclose(fp);
	printf("\n\n");

	while(change==1) {
		change = 0;
		for (int i = 0; i < nofP; i++) {
			if (P[i]==0) {
				if (enough(R, preq[i], nofR)==1) {
					Rreturn(R, pall[i], nofR);
					P[i] = 1;
					dead += P[i];
					change = 1;
				}
			}
		}
	}

	
	if (dead == nofP) {
		printf("It is Not DeadLock state\n");
	}
	else {
		printf("It is DeadLock state\n");
		printf("DeadLock Process List: ");
		for (int i = 0; i < nofP; i++) {
			if (P[i] == 0)
				printf("P%d ", i + 1);
		}
		printf("\n");
	}


	for (int i = 0; i < nofP; i++) {
		free(pall[i]);
		free(preq[i]);
	}
	free(pall);
	free(preq);//delete memory for All.MatriX and Request matrix
	free(R);
	free(P);
	return 0;
}

int enough(int* R, int* processrequest, int nofR) {
	for (int k = 0; k < nofR; k++) {
		if (processrequest[k] > R[k]) {
			return -1;
		}
	}
	return 1;
}

void Rreturn(int* R, int* processallocation, int nofR) {
	for (int k = 0; k < nofR; k++) {
		R[k] += processallocation[k];
	}
}