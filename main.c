/** EL2208 Praktikum Pemecahan Masalah dengan C 2022/2023
 *   Modul               : 4 - Struct and Dynamic Array
 *   Hari dan Tanggal    : Rabu, 1 Maret 2023
 *   Nama (NIM)          : Dimas Ridhwana Shalsareza (13221076)
 *   Nama File           : main.c
 *   Deskripsi           : Program menerima sebuah input nama file lalu membaca baris pertama sebagai mode 
 *                         Dan menjalankan baris selanjutnya dengan validasi terlebih dahulu sesuai spek yang dibutuhkan
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_LEN 100

int count, count_row;
char in_row[MAX_LEN];

int mode;
char *token;
char nama_file[1000];
int i = 0;

char search;
char temp_check[1000000];

typedef struct Pokemon {
   char id[MAX_LEN];
   char name[MAX_LEN];
   char type[MAX_LEN];
} Pokemon;

//Fungsi Menghitung Jumlah Baris pada file
int countrow(){
    FILE *file;
    scanf("%s", &nama_file);
    file = fopen(nama_file, "r");
    while (!feof(file)){
        fgets(in_row, MAX_LEN,file);
        count++;
    }
    int temp_count = count;
    count = 0;
    fclose(file);
    return temp_count;
}

//Fungsi mengecek substring
bool is_substring(char *check, char *string)
{
   int slen = strlen(string);
   int clen = strlen(check);
   int end = slen - clen + 1;
   
   for (int i = 0; i < end; i++)
   {
      bool check_found = true;
      for (int j = 0; j < clen; j++){
         if ((check[j]>=65 && check[j]<=90)){
               temp_check[j] = (char)((int)check[j] + 32);
               if ((temp_check[j] != string[i + j]))
               {
                  check_found = false;
                  break;
               }
         } else{
               if ((check[j] != string[i + j]))
               {
                  check_found = false;
                  break;
               }
         }     
      }
      if (check_found) return true;
   }
}

// //Fungsi untuk melakukan print sesuai input structure
void printPokemon(Pokemon *p, int n) {
   printf("\nID: %s\nNama: %s\nType: %s\n", p[n].id, p[n].name, p[n].type);
}

// //Fungsi untuk melakukan pencarian ID pada array structure
void searchID(Pokemon *p, int n, char *ID) {
    bool status = is_substring(p[n].id, ID);
    if (status == true){
        // printPokemon(p, n);
        printf("asdad");
    } else{
        printf("\nPokemon yang memiliki ID %s belum ditangkap!",ID);
    }
}

//Fungsi untuk melakukan pencarian name pada array structure
void searchName(Pokemon *p, int n, char *NAMA) {
    bool status = is_substring(p[n].name, NAMA);
    if (status == true){
        // printPokemon(p, n);
    } else{
        printf("\nPokemon dengan nama %s belum ditangkap!", NAMA);
    }
}

//Fungsi untuk melakukan pencarian type pada array structure
void searchType(Pokemon *p, int n, char *type) {
    bool status = is_substring(p[n].type, type);
    if (status == true){
        // printPokemon(p, n);
    } else{
        printf("\nPokemon dengan type %s belum ditangkap!", type);
    }   
}

int main(){
    //Open File
    FILE *file;
    count_row = countrow();
    // printf("Rows : %d\n", count_row);
    file = fopen("pokedex1.txt", "r");
    
    //Dynamic Array Using Struct
    Pokemon *data = malloc(count_row*sizeof(Pokemon));

    // Mengambil Mode dari baris pertama file
    mode = atoi((char*)fgets(in_row, MAX_LEN,file));
    // printf("Mode : %d\n", mode);

    while(!feof(file) && count<count_row){
      //   printf("Looping Baris ke %d\n", count+1);               //----DEBUG
        fgets(in_row, MAX_LEN, file);

        // Returns first token
        token = strtok(in_row, ";");
        strcpy(data[count].id, token);
      //   printf("\tID      : %s\n", data[count].id);             //----DEBUG

        token = strtok(NULL, ";");
        strcpy(data[count].name, token);
      //   printf("\tName    : %s\n", data[count].name);           //----DEBUG

        token = strtok(NULL, ";");
        strcpy(data[count].type, token);
      //   printf("\tType    : %s\n", data[count].type);           //----DEBUG
        token = strtok(NULL, " ");
        
        count++;
    }

    char sub_ID[MAX_LEN];
    char sub_Nama[MAX_LEN];
    char sub_Type[MAX_LEN];
   //  printf("-------------------------------------------------\n");
   
    bool status;

    if (mode == 1){
        printf("Program mencari ID pokemon: ");
        scanf("%s", &sub_ID);        
        searchID(data, count, sub_ID);
    } else if(mode == 2){
        printf("Program mencari Nama pokemon: ");
        scanf("%s", &sub_Nama);   
        searchName(data, count, sub_Nama);
    } else if(mode == 3){
        printf("Program mencari Type pokemon: ");
        scanf("%s", &sub_Type);
        searchType(data, count, sub_Type);
    }else{
        return 0;
    }
    free(data);
    fclose(file);
    return 0;
}