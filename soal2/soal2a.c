#include<stdio.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>

int baris=0;
int matriksA[4][3] ;
int matriksB[3][6];
int hasil[4][6];

void MatrixInput(){
int i = 0;
int j = 0;

 printf("Input matriks A (4x3) :\n");
	for (i = 0; i < 4; i++) {
    	for (j = 0; j < 3; j++) {
		printf("input elemen A%d%d:\n", i+1, j+1);
      		scanf("%d", &matriksA[i][j]);
   	 	}
  	}
	printf("\n");
        for (i = 0; i < 4; i++) {
    	for (j = 0; j < 3; j++) {
		printf("%d\t",matriksA[i][j]);
   	 	}
		printf("\n");
  	}

    
  printf("\nInput matriks B (3x6) :\n");
	for (i = 0; i < 3; i++) {
    	for (j = 0; j < 6; j++) {
		printf("input elemen B%d%d:\n", i+1, j+1);
      		scanf("%d", &matriksB[i][j]);
   	 	}
  	}
	printf("\n");	
	for (i = 0; i < 3; i++) {
    	for (j = 0; j < 6; j++) {
		printf("%d\t",matriksB[i][j]);
   	 	}
		printf("\n");
  	}

}

void* multiplymatrices(void* arg){
  
  int x;
 
  x = baris++;

  for(int y=0; y<6; y++){
    for(int z=0; z<3; z++){
      hasil[x][y] += matriksA[x][z] * matriksB[z][y];
    }
  }
}

int main(){
  int i=4;
  int j=6;
  int (*matriks)[j];
  int a=0;
  pthread_t t[4];
  inputMatrix();

  for(int a=0; a<4; a++){
    pthread_create(&t[a], NULL, &multiplymatrices, NULL);
  }
  for (int a=0; a<4; a++){
    pthread_join(t[a], NULL);
  }

key_t key = 1234;
int shmid = shmget(key, sizeof(int)*i*j, IPC_CREAT | 0666);
matriks =  shmat(shmid, NULL, 0);

printf("\nHasil : \n");
for(int b=0; b<i; b++){
  for(int c=0; c<j ; c++){
    printf("%d\t", hasil[b][c]);
  }
  printf("\n");
}

int* p = (int *)matriks;

memcpy(p, hasil, sizeof(int)*i*j);

shmdt(matriks);
}
