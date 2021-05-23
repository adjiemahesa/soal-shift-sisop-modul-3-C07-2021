# soal-shift-modul-3-C07-2021

# Soal 3
Soal ini meminta kami untuk melakukan pengkategorian sesuai ektensi file yang ada pada file-file yang diberikan. Pengkategorian akan dilakukan dengan memindahkan file-file tersebut ke folder-folder yang akan dibuat sesuai ekstensi nya. 

## 3A
Untuk soal 3A program akan menerima perintah ``-f`` untuk memindahkan file secara pilihan tertentu sebanyak yang diinginkan user. Untuk itu kami menggunakan pembedaan argumen dimana program identifikasi kalau argumen yang diberikan adalah ``-f`` seperti berikut
```
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
```
Setelah masuk kedalam syarat tersebut, program akan masuk kedalam fungsi *moveFile* dan *get_file_extension*. Untuk fungsi tersebut digunakan untuk memindahkan file tersebut dan untuk mencari ekstensi file. Bagi fungsi mencari ekstensi sebagai berikut:
```
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
```
Pada fungsi tersebut kami menggunakan pertama sebuah fungsi *noPathFolderName* untuk menghapuskan string path pada file agar bisa mengambil string nama file tersebut. Lalu, kita menggunakan fungsi string yang mencari character "." menandakan ekstensi. Lalu, dicek apakah ada ekstensinya atau tidak dan jika ada kita gunakan +1 agar penamaan yang keluar jadi hanya ekstensinya saja. Setelah itu, ada juga fungsi untuk memindahkan file dengan *moveFile* sebagai berikut:
```
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
```
Pada fungsi ini akan dilakukan pemeriksaan terhadap file dengan mengambil nama ekstensi tiap file yang diperiksa dan digunakan untuk membuat folder-folder sesuai nama ekstensinya. Hasil dari soal ini sebagai berikut:
![image](https://user-images.githubusercontent.com/55140514/119259883-7e4b1500-bbfa-11eb-8cd4-a83d5c2a4be5.png)
![image](https://user-images.githubusercontent.com/55140514/119259898-8c993100-bbfa-11eb-97dd-693bd8c3c0b3.png)

## 3B
Pada soal ini dimintakan untuk melakukan operasi pengkategorian pada suatu directory. Operasi ini hanya dilakukan pada satu directory saja tiap perjalanan program tidak seperti pada soal 3A. Untuk melakukan ini program diminta untuk bisa menerima perintah ``-d``. Setelah menerima dan menjalankan perintah output program akan menyimpan folder-folder yang terbentuk pada working directory program C kita dan menuliskan kata-kata seperti berikut
```
Berhasil = print “Direktori sukses disimpan!”
Gagal = print “Yah, gagal disimpan :(“
```
Langkah pertama adalah untuk program menerima perintah atau argumen ``-d`` seperti berikut
```
 else if (strcmp(argv[1], "-d") == 0){
        listFiles(argv[2]);
        if (errCheck == 0){
            printf("Direktori sukses disimpan!\n");
        }
        else{
            printf("Yah, gagal disimpan:(\n");
        }
    }
```
Lalu, sesuai persyaratan soal, kita buat fungsi untuk melakukan pemeriksaan secara recursive pada funsgi *listFiles* seperti berikut
```
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
```
Fungsi ini bekerja dengan melakukan pengecekan apakah file yang sedang di periksa benar-benar ada dengan melakukan ``strcmp`` pada list file untuk memeriksa apakah ada "." atau ".." karena jika ada maka menandakan bahwa bukan file. Lalu, akan dilakukann pemindahan file  file yang terdapat thread pada `` err = pthread_create(&(threads[threadCount - 2]), NULL, &moveFile, (void *)path);``. Setelah itu baru akan masuk ke fungsi *moveFile* seperti Soal 3A.

Hasil seperti berikut:
![image](https://user-images.githubusercontent.com/55140514/119260535-67f28880-bbfd-11eb-9064-288270566b79.png)
![image](https://user-images.githubusercontent.com/55140514/119260542-7476e100-bbfd-11eb-893d-3e01b157c4cb.png)

## 3C


