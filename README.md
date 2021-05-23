# soal-shift-modul-3-C07-2021

# Soal 2

## 2A
untuk soal 2 A kami diminta untuk membuat program untuk menghitung perkalian matriks 4x3 dan 3x6

__penyelesaian__

```
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
```

bagian diatas adalah fungsi untuk menginput elemen-elemen pada matriks 4x3 dan matriks 3x6


```
void* multiplymatrices(void* arg){
  
  int x;
 
  x = baris++;

  for(int y=0; y<6; y++){
    for(int z=0; z<3; z++){
      hasil[x][y] += matriksA[x][z] * matriksB[z][y];
    }
  }
}
```
bagian diatas adalah fungsi untuk menghitung perkalian 2 matriks tersebut dan memasukkan kedalam array hasil

```
for(int a=0; a<4; a++){
    pthread_create(&t[a], NULL, &multiplymatrices, NULL);
  }
  for (int a=0; a<4; a++){
    pthread_join(t[a], NULL);
  }
```
bagian di atas pada fungsi main adalah thread yang dibuat menggunakan loop untuk melakukan fungsi multiplymatrices untuk mengalikan matrks
kemudian melakukan print 
```
printf("\nHasil : \n");
for(int b=0; b<i; b++){
  for(int c=0; c<j ; c++){
    printf("%d\t", hasil[b][c]);
  }
  printf("\n");
}
```
bagian di bawah ini adalah shared memory yang digunakan karena hasil dari soal ini akan digunakan kembali di soal b
```
key_t key = 1234;
int shmid = shmget(key, sizeof(int)*i*j, IPC_CREAT | 0666);
matriks =  shmat(shmid, NULL, 0);
```
hasil perkalian dalam screenshot :
![2a](https://user-images.githubusercontent.com/81466736/119261849-7479df80-bc03-11eb-8a29-6dea7a58a15f.JPG)


## 2b
di soal 2b ini kami diminta untuk melakukan suatu operasi antara hasil matriks di soal sebelumnya dengan input matriks baru 
dengan ketentuan operasi sebagai berikut
![image](https://user-images.githubusercontent.com/81466736/119262120-4d6fdd80-bc04-11eb-9088-4cef020dcdb9.png)

```
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
```
fungsi diatas adalah untuk melakukan input pada matriks yang baru

```
unsigned long long factorial(int n) 
{ 
	if(n==0)return 1;
	else
		return n*factorial(n-1);
}
```
fungsi diatas adalah untuk melakukan perhitungan faktorial

diawal program saya membuat stuct untuk menyimpan dan untuk mengambil data dari hasil operasi matriks
```
typedef struct data {
	int matriksA;
    int matriksB;
	int x,y;
}data;
```

```
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
```
fungsi diatas adalah untuk melakukan operasi dengan ketentua di soal

```
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
```
pada bagian loop diatas mengambil data-data dari struct yang telah dibuat sebelumnya kemudian membuat thread untuk melakukan fungsi operasi_soal lalu melakukan join thread
dengan shared memory digunakan untuk mengambil hasil dari soal 2a 

hasil operasi di screenshot :
![2b](https://user-images.githubusercontent.com/81466736/119262674-3d58fd80-bc06-11eb-87b0-bd31c0d4a4e5.JPG)


## soal 2C
disoal ini kami diminta untuk membuat program agar menjalakan command "“ps aux | sort -nrk 3,3 | head -5”" untuk melihat 5 proses teratas apa saja yang memakan resource komputernya 
```
void exec1() {
  dup2(pipe1[1], 1);
  close(pipe1[0]);
  close(pipe1[1]);
  execlp("ps", "ps", "aux", NULL);
  perror("bad exec ps");
  _exit(1);
}

void exec2() {
  dup2(pipe1[0], 0);
  dup2(pipe2[1], 1);
  close(pipe1[0]);
  close(pipe1[1]);
  close(pipe2[0]);
  close(pipe2[1]);
  execlp("sort", "sort", "-nrk", "3.3", NULL);
  perror("bad exec grep root");
  _exit(1);
}

void exec3() {
  dup2(pipe2[0], 0);
  close(pipe2[0]);
  close(pipe2[1]);
  execlp("head", "head", "-5", NULL);
  perror("bad exec grep sbin");
  _exit(1);
}
```
membuat 3 fungsi exec1, exec2, exec3 yang berisikan fungsi dup() untuk pipe dan fungsi execlp yang berisikan pada masing masing fungsi "ps"dan "aux" untuk exec_1, "sort", "-nrk",dan "3.3" untuk fungsi exec_2, dan "head", "-5" untuk exec_5.

pada fungsi main akan dibuat pipe yang menjalankan 3 fungsi untuk membuat command "ps aux | sort -nrk 3,3 | head -5" diatas dan melakukan fork
```
void main() {

  if (pipe(pipe1) == -1) {
    perror("bad pipe1");
    exit(1);
  }

  if ((pid = fork()) == -1) {
    perror("bad fork1");
    exit(1);
  } else if (pid == 0) {
    exec1();
  }
  if (pipe(pipe2) == -1) {
    perror("bad pipe2");
    exit(1);
  }

  if ((pid = fork()) == -1) {
    perror("bad fork2");
    exit(1);
  } else if (pid == 0) {
    exec2();
  }
  close(pipe1[0]);
  close(pipe1[1]);
  if ((pid = fork()) == -1) {
    perror("bad fork3");
    exit(1);
  } else if (pid == 0) {
    exec3();
  }
  
}
```
output di terminal :

![2c](https://user-images.githubusercontent.com/81466736/119263098-df2d1a00-bc07-11eb-94ee-10a2fbe8ea3d.JPG)

## kendala saat mengerjakan soal 2

masih kurang memahami materi pipe sehingga kesulitan saat mengerjakan dan memahami soal 2c

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
Soal ini meminta untuk melakukan sama seperti pada soal 3B, tetapi perbedaannya disini hanya akan melakukan pengkategorian seluruh file yang berada pada working directory program C. Sesuai permintaan soal, program akan menjalankan operasi seperti ini ketika menerima perintah atau argumen ``*``. Cara penyelesaian soal ini hampir sama dengan yang ada pada soal 3B. Langkah pertama yang dilakukan adalah membuat program menerima argumen tersebut seperti berikut
```
 else if (strcmp(argv[1], "*") == 0){
        listFiles(".");
        if (errCheck == 0){
            printf("Direktori sukses disimpan!\n");
        }
        else{
            printf("Yah, gagal disimpan:(\n");
        }
    }
```
Lalu, karena diminta untuk melakukan pemeriksaan dengan cara rekursif, maka akan digunakan lagi funsgi *listFiles* seperti pada soal 3B.
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
Lalu, seperti pada soal 3B, dilakukan kembali fungsi *moveFile* untuk memindahkan file nya. Hasil dari program adalah sebagai berikut

![image](https://user-images.githubusercontent.com/55140514/119263829-d427b900-bc0a-11eb-8d93-e4219b714ab9.png)
![image](https://user-images.githubusercontent.com/55140514/119263834-dee24e00-bc0a-11eb-9d5f-ddaf71845de9.png)

## 3D
Pada soal ini diminta agar semua file harus berada di dalam folder. Lalu, karena ada kemungkinan file yang tidak mempunyai ekstensi, maka file tersebut akan masuk kedalam folder bernama "Unknown". Setelah itu ada kemungkinan terdapat juga file yang hidden, maka jika ada file tersebut akan pindah ke folder bernama "Hidden". Untuk itu, digunakan fungsi *moveFile*
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
Lalu, untuk soal ini digunakan case berikut
```
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
```
Dicase tersebut kita akan melakukan pengecekan pada file apakah file tersebut termasuk file hidden, unknown, atau file yang mempunyai ekstensi. Untuk file hidden pada string awal akan terdapat "." dan jika extension NULL maka masuk kedalam unknown. hal tersebut kami gunakan pertama untuk membuat folder kategorinya. Lalu seperti pada file yang memiliki extension, file-file tersebut akan dipindahkan ke folder kategorinya masing-masing menggunakan fungsi *newFilePath* ``newFilePath(fileOriginal, directDest);`` yang fungsi nya sebagai berikut
```
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
```
Fungsi ini digunakan untuk memindahkan semua file ke foldernya masing-masing agar mengertahui file harus kemana. Hasil sebagai berikut

![image](https://user-images.githubusercontent.com/55140514/119264515-c0318680-bc0d-11eb-92fb-7512fba0d78d.png)

## 3E
Pada soal ini diminta agar setiap file yang dikategorikan dioperasikan oleh 1 thread agar jalan secara paralel. Program sudah menerapkan 1 Thread untuk tiap pengkategorian file karena file dipindahkan secara satu per satu.
