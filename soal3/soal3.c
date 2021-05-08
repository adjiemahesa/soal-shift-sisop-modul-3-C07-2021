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

void moveFileUtil(char source[], char dest[]);
char* searchfileName(char str[]);
char* searchExtension(char str[]);
void* move(void *arg);
void* moveChoosen(void *arg);

char* searchExtension(char str[]){
    char* pch = searchfileName(str);
    char* result = strchr(pch, '.');
    if(result == NULL)
	{
		return NULL;
	}
    else return (result+1);
}

int main(int argc, char **argv){
	char array[1000];
    curDir = getcwd(array, 1000);
    int i;

    if(strcmp(argv[1], "-f") == 0){
        while(argv[i] != NULL){
            pthread_create(&(tid[i-2]), NULL, &move, (void *)argv[i]);
            i++;
        }
        for(j = 0; j < (i-1); j++){
            pthread_join(tid[j], NULL);
        }
    }
	
}