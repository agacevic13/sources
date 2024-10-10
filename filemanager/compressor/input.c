#include <stdio.h>
#include "miniz.h"
#include <stdlib.h>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint;

void Load(char* filename, uint8* pOutBuff,uLong uncomp_len)   //arg: 
{
     
      FILE* file = fopen(filename, "rb");
      if(file==NULL){
        printf("Unable to open the file.");
        return;
      }
     fseek(file, 0, SEEK_END);
   long  file_size = ftell(file);  // Dobij veličinu fajla u bajtovima
    rewind(file);             // Vrati pokazivač na početak fajla

    // Alociraj memoriju za sadržaj fajla
     uint8 *file_buffer = (uint8 *)malloc(file_size);
    if (!file_buffer) {
        printf("Failed to allocate memory for file!\n");
        fclose(file);
    }
     fread(file_buffer, 1, file_size, file);
    fclose(file); 
   
      
 int cmp_status = uncompress(pOutBuff, &uncomp_len, file_buffer, file_size);

    if (cmp_status != Z_OK) {
        printf("Decompression failed!\n");
        free(file_buffer);
    }
    free(file_buffer);
  printf("Decompressed from %lu to %lu bytes\n", file_size, uncomp_len);
     // Učitaj sadržaj fajla u memoriju
    // Zatvori fajl nakon čitanja
    
    // procitati fajl

    // dekompresovati u pOutBuff direktno, pretpostaviti da je pOutBuff dovoljno veliki
}

void Save(char* filename, const uint8* pDataToSave)   //arg:filename with data to compress 
{

    
    FILE * file = fopen(filename, "wb"); 
    if (!file) {
        printf("Failed to open file!\n");
        return;
    }
      // Pomeri pokazivač na kraj fajla kako bi dobio njegovu veličinu
     
     uLong src_len = (uLong)strlen(pDataToSave);
     uLong cmp_len = compressBound(src_len);
     uint8 *pCmp = (uint8 *)malloc(cmp_len);
    int cmp_status = compress(pCmp, &cmp_len, pDataToSave, src_len);
    if (cmp_status != Z_OK) {
        printf("Compression failed!\n");
       free(pCmp);
    }

    fwrite(pCmp, 1, cmp_len, file);
    fclose(file);
    printf("Compressed from %lu to %lu bytes\n", src_len, cmp_len);
}

int main() {

   char* filename = "test.json";
   
   static const char *s_pStr = "Good morning Dr. Chandra. This is Hal. I am ready for my first lesson."
                            "Good morning Dr. Chandra. This is Hal. I am ready for my first lesson."
                            "Good morning Dr. Chandra. This is Hal. I am ready for my first lesson."
                            "Good morning Dr. Chandra. This is Hal. I am ready for my first lesson."
                            "Good morning Dr. Chandra. This is Hal. I am ready for my first lesson."
                            "Good morning Dr. Chandra. This is Hal. I am ready for my first lesson."
                            "Good morning Dr. Chandra. This is Hal. I am ready for my first lesson.";

    uLong src_len = (uLong)strlen(s_pStr);
    uint8 *pUncomp = (uint8 *)malloc(src_len); //memorija za dekompresovane podatke 
    Save(filename, s_pStr);
    Load(filename, pUncomp, src_len * 10);
    printf("Decompressed data:\n%s\n", pUncomp);

 
}
