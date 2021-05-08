#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<dirent.h>

pthread_t tid[5000];
char *curDir;

char folderDest[5000];
char* searchfileName(char str[]);
char* searchExtension(char str[]);
void* move(void *arg);
void* moveChoosen(void *arg);

void* move(void *arg){
    pthread_t id = pthread_self();
    char *folderExtension;

    folderExtension = searchExtension((char *)arg);

    if(folderExtension == NULL)
	{
        strcpy(folderDest, NULL);
    }
    else{
        strcpy(folderDest, folderExtension);
		
        }
    }
    if(mkdir(folderDest, );
}

char* searchExtension(char str[]){
    char* pch = searchfileName(str);
    char* result = strchr(pch, '.');
    if(result == NULL)
	{
		return NULL;
	}
    else return (result);
}

 int main(void)
{
	int i=2;
	int j;
	int err;
	char array[1000];
    curDir = getcwd(array, 1000);
	while(i<3) // loop sejumlah thread
	{
		ierr=pthread_create(&(tid[i]),NULL,&move,NULL); 
		if(err!=0) 
		{
			printf("\n can't create thread : [%s]",strerror(err));
		}
		else
		{
			printf("\n create thread success\n");
		}
		i++;
	}
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	exit(0);
	return 0;
}