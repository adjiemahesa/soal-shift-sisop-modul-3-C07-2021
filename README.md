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
