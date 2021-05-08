#include <stdio.h>
int i=0;
int j=0;
int k=0;
int temp;

// fungsi untuk input elemen dari matriks 4x3
void input_matrix_4x3(int matrix[10][10], int baris, int kolom) {

   printf("input elemen matriks 4x3: \n"); //biar ga bingung :v

   for (i = 0; i < baris; i++) 
   {
      for (j = 0; j < kolom; j++) 
	  {
         //printf("input a%d%d: ", i + 1, j + 1);
         scanf("%d", &matrix[i][j]);
      }
   }
}

// fungsi untuk input elemen dari matriks 3x6
void input_matrix_3x6(int matrix[10][10], int baris, int kolom) {

   printf("input elemen matriks 3x6 : \n"); //biar ga bingung :v

   for (i = 0; i < baris; i++) 
   {
      for (j = 0; j < kolom; j++) 
	  {
         //printf("input b%d%d: ", i + 1, j + 1);
         scanf("%d", &matrix[i][j]);
      }
   }
   printf("hasil :\n");
}


// fungsi untuk perkaliannya
void perkalian_matrix(int matriks4x3[10][10],
                      int matriks3x6[10][10],
                      int hasil[10][10],
                      int baris4x3, int kolom4x3, 
					  int baris3x6, int kolom3x6) 
{
     for (i = 0; i < baris4x3; i++) 
	 {
      for (j = 0; j < kolom3x6; j++) 
	  {
         hasil[i][j] = 0;
      }
     }
   
   for (i = 0; i < baris4x3; i++) 
   {
   for (j = 0; j < kolom3x6; j++) 
   	{
   	 for (k = 0; k < kolom4x3; k++) 
   		{
            temp =  matriks4x3[i][k] * matriks3x6[k][j];
            hasil[i][j] += temp;
        }
    }
   }
}

// fungsi untuk menampilkan hasil
void tampilkan_hasil(int hasil[10][10], int baris, int kolom) {
   for (i = 0; i < baris; i++) {
      for (j = 0; j < kolom; j++) {
         /*hasil*/ printf("%d  ", hasil[i][j]);
         if (j == kolom - 1)
            printf("\n");
      }
   }
}

int main() {
   int matriks4x3[10][10]; 
   int matriks3x6[10][10]; 
   int hasil[10][10]; 
   int baris4x3 = 4;
   int kolom4x3 = 3;
   int baris3x6 = 3;
   int kolom3x6 = 6;

   input_matrix_4x3(matriks4x3, baris4x3, kolom4x3);
   input_matrix_3x6(matriks3x6, baris3x6, kolom3x6);
   perkalian_matrix(matriks4x3, matriks3x6, hasil, baris4x3, kolom4x3, baris3x6, kolom3x6);
   tampilkan_hasil(hasil, baris4x3, kolom3x6);

   return 0;
}
