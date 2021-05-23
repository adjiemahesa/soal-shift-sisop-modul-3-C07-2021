#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

int matriksInput[4][6];
int matriks[4][6];
unsigned long long matriksfaktorial[4][6];

typedef struct data {
	int matriksA;
    int matriksB;
	int x,y;
}data;

void MatriksInput(){
    printf("Input matriks 4x6 :\n");
	for (int i = 0; i < 4; i++) {
    	for (int j = 0; j < 6; j++) {
		printf("input elemen B%d%d:\n", i+1, j+1);
      		scanf("%d", & matriksInput[i][j]);
   	 	}
  	}
	printf("\n");
        for (int i = 0; i < 4; i++) {
    	for (int j = 0; j < 6; j++) {
		printf("%d\t",matriksInput[i][j]);
   	 	}
		printf("\n");}
}


unsigned long long factorial(int n) 
{ 
	if(n==0)return 1;
	else
		return n*factorial(n-1);
}

void *operasi_soal(void* arg)
{
	data* d = (data*) arg;
	int a = d->matriksA;
	
	int b = d->matriksB;
	int x = d->x;
	int y = d->y;
	
	if(a==0 || b==0){
		matriksfaktorial[x][y] = 0;}
	else if (a>=b){
		int temp = a-b;
		matriksfaktorial[x][y] = factorial(a)/factorial(temp);}
	else if(b>a){
		matriksfaktorial[x][y] = factorial(a);}
}



void main(){
	key_t key = 1234;
        int i=4,j=6;
        int (*hasil)[j];
	int shmid = shmget(key, sizeof(int)*i*j, IPC_CREAT | 0666);
	hasil = shmat(shmid, NULL, 0);

	int* p = (int *)hasil;
	memcpy(matriks,hasil,sizeof(int)*i*j);

	pthread_t tid[i][j];
        
MatriksInput();
	

printf("\nHasil perkalian Matrix di soal A : \n");
	for(int b=0; b<i; b++){
		for(int c=0; c<j ; c++){
			printf("%d\t", hasil[b][c]);
		}
		printf("\n");}

	for(int i= 0;i<4;i++)
	{
        for(int j=0;j<6;j++){
	    data *index = (data *)malloc(sizeof(data));
            index->matriksA = matriks[i][j];
            index->matriksB = matriksInput[i][j];
            index->x = i;
            index->y = j;
			pthread_create(&tid[i][j],NULL, &operasi_soal, (void*)index);
			sleep(1);
        }
		
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			pthread_join(tid[i][j], NULL);
		}
	}

	printf("\nHasil Operasi Matrix : \n");
	for(int b=0; b<i; b++){
		for(int c=0; c<j ; c++){
			printf("%llu\t", matriksfaktorial[b][c]);
		}
		printf("\n");
	}
	printf("\n");
	shmdt(hasil);
	shmctl(shmid, IPC_RMID, NULL);
}
