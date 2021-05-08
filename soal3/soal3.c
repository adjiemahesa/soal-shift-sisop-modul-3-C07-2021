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

    folderExtension = getExt((char *)arg);

    if(folderExtension == NULL)
	{
        strcpy(folderDest, "Unknown");
    }
    else{
        strcpy(folderDest, folderExtension);
        int i;
        for(i = 0; i < strlen(folderDest); i++){
            if(folderDest[i] > 64 && folderDest[i] < 91)
                folderDest[i] += 32;
        }
    }
    
    if(mkdir(folderDest, 0777) == -1);

    char pathDestination[5000];
    snprintf(pathDestination, 5000, "%s/%s/%s", curDir, folderDest, getFilename((char *)arg));
    moveFileUtil((char *)arg, pathDestination);
}

char* searchExtension(char str[]){
    char* pch = searchfileName(str);
    char* result = strchr(pch, '.');
    if(result == NULL)
	{
		return NULL;
	}
    else return (result+1);
}

 int main(void)
{
	int i=0;
	int err;
	char array[1000];
    curDir = getcwd(array, 1000);
	while(i<3) // loop sejumlah thread
	{
		err=pthread_create(&(tid[i]),NULL,&move,NULL); //membuat thread
		if(err!=0) //cek error
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