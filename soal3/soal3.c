#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <stdbool.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <libgen.h>

pthread_t threads[100000];
int threadCount = 2;

int currID;
char *currDirect;
int errCheck;

char *get_file_extension(char str[]);
void listFiles(char *oriPath);
void newFilePath(char source[], char dest[]);
char *noPathFolderName(char str[]);

void *moveFile(void *arg)
{
    char *fileName = (char *)arg;
    char fileOriginal[1000], tempFile[1000];
    strcpy(fileOriginal, fileName);
    strcpy(tempFile, fileName);

    char *ext = get_file_extension(fileName);
    char *noPathName = noPathFolderName(tempFile);

    char nameFolder[120];

    if (noPathName[0] == '.'){
        sprintf(nameFolder, "Hidden");
    }
    else if (ext == NULL){
        sprintf(nameFolder, "Unknown");
    }
    else{
        for (int i = 0; ext[i]; i++)
        {
            ext[i] = tolower(ext[i]);
        }
        sprintf(nameFolder, "%s", ext);
    }
    mkdir(nameFolder, 0777);
    
    char directDest[200];
    sprintf(directDest, "%s/%s/%s", currDirect, nameFolder, noPathFolderName(fileOriginal));

    newFilePath(fileOriginal, directDest);
    return NULL;
}



void listFiles(char *oriPath)
{
    char path[1000], pathThread[1000];
    struct dirent **namelist;
    int i = 0;
    int n = scandir(oriPath, &namelist, NULL, alphasort);;
    if (n < 0)
        return;
    else
    {
        while (i < n)
        {
            if (strcmp(namelist[i]->d_name, ".") != 0 && strcmp(namelist[i]->d_name, "..") != 0)
            {
                strcpy(path, oriPath);
                strcat(path, "/");
                strcat(path, namelist[i]->d_name);

                strcat(pathThread, "/");
                strcat(pathThread, namelist[i]->d_name);

                if (namelist[i]->d_type != DT_DIR)
                {
                    int err;
                    err = pthread_create(&(threads[threadCount - 2]), NULL, &moveFile, (void *)path);

                    if (err != 0){
                        errCheck++;
                        printf("File %d: Sad, gagal :(\n", threadCount - 1);
                    }
                    else
                        printf("File %d : Berhasil Dikategorikan\n", threadCount - 1);
                        threadCount++;

                    for (int p = 0; p < (threadCount - 1); p++){
                        pthread_join(threads[p], NULL);
                    }
                }
                listFiles(path);
            }
            free(namelist[i]);
            ++i;
        }
        free(namelist);
    }
}

void newFilePath(char source[], char dest[])
{
    int ch;
    FILE *filePath1, *filePath2;

    filePath1 = fopen(source, "r");
    filePath2 = fopen(dest, "w");

    if (!filePath1){
        printf("Unable to open source file to read!!\n");
        fclose(filePath2);
        return;
    }

    if (!filePath2){
        printf("Unable to open target file to write\n");
        return;
    }

    while ((ch = fgetc(filePath1)) != EOF){
        fputc(ch, filePath2);
    }
    fclose(filePath1);
    fclose(filePath2);

    remove(source);
    return;
}

char *noPathFolderName(char str[])
{
    char *pch;
    char *result;
    pch = strchr(str, '/');
    if (pch == NULL){
        return str;
    }
    while (pch != NULL){
        result = pch + 1;
        pch = strchr(pch + 1, '/');
    }
    return result;
}

char *get_file_extension(char str[])
{
    char *pch = noPathFolderName(str);
    // cari . pertama
    char *result = strchr(pch, '.');
    if (result == NULL){
        return NULL;
    }
    else{
        // menghapus . pada nama file
        return (result + 1);
    }
}

int main(int argc, char **argv)
{
    char arr[1000];
    currDirect = getcwd(arr, 1000);

    int i = 2;
    int err, p;
    
    if (strcmp(argv[1], "-f") == 0){
        while (argv[i] != NULL){
            err = pthread_create(&(threads[i - 2]), NULL, &moveFile, (void *)argv[i]);
            if (err != 0)
                printf("File %d: Sad, gagal :(\n", i - 1);
            else
                printf("File %d : Berhasil Dikategorikan\n", i - 1);
            i++;
        }

        for (p = 0; p < (i - 1); p++){
            pthread_join(threads[p], NULL);
        }
        return 0;
    }
    else if (strcmp(argv[1], "-d") == 0){
        listFiles(argv[2]);
        if (errCheck == 0){
            printf("Direktori sukses disimpan!\n");
        }
        else{
            printf("Yah, gagal disimpan:(\n");
        }
    }
    else if (strcmp(argv[1], "*") == 0){
        listFiles(".");
        if (errCheck == 0){
            printf("Direktori sukses disimpan!\n");
        }
        else{
            printf("Yah, gagal disimpan:(\n");
        }
    }
    return 0;
}
