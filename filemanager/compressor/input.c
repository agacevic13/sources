#include <stdio.h>
#include "miniz.h"
#include <stdlib.h>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint;

void Load(char* filename, uint8* pOutBuff,uLong uncomp_len)
{
    
 uLong cmp_len = compressBound(uncomp_len);

     fseek(filename, 0, SEEK_END);
   long  file_size = ftell(filename);  // Dobij veličinu fajla u bajtovima
    rewind(filename);             // Vrati pokazivač na početak fajla

    // Alociraj memoriju za sadržaj fajla
     uint8 file_buffer = (uint8 *)malloc(file_size);
    if (!file_buffer) {
        printf("Failed to allocate memory for file!\n");
        fclose(filename);
        return 1;
    }

    // Učitaj sadržaj fajla u memoriju
    fread(file_buffer, 1, file_size, filename);
    fclose(filename);  // Zatvori fajl nakon čitanja
    

 int cmp_status = uncompress(pOutBuff, &uncomp_len, file_buffer, cmp_len);

    if (cmp_status != Z_OK) {
        printf("Decompression failed!\n");
    }
    // procitati fajl

    // dekompresovati u pOutBuff direktno, pretpostaviti da je pOutBuff dovoljno veliki
}

void Save(char* filename, const uint8* pDataToSave)
{
     long file_size;
     uint8 *file_buffer;
    FILE * file = fopen(filename, "wb"); 
    if (!file) {
        printf("Failed to open file!\n");
        return;
    }
      // Pomeri pokazivač na kraj fajla kako bi dobio njegovu veličinu
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);  // Dobij veličinu fajla u bajtovima
    rewind(file);             // Vrati pokazivač na početak fajla

    // Alociraj memoriju za sadržaj fajla
    file_buffer = (uint8 *)malloc(file_size);
    if (!file_buffer) {
        printf("Failed to allocate memory for file!\n");
        fclose(file);
        return 1;
    }
     uLong src_len = (uLong)file_size;
     uLong cmp_len = compressBound(pDataToSave);
     uint8 *pCmp = (uint8 *)malloc(cmp_len); 
      fread(file_buffer, 1, file_size, file);
     fclose(file);  // Zatvori fajl nakon čitanja
    // ubaciti kompresiju i prilagoditi fwrite
   
    int cmp_status = compress(pCmp, &cmp_len, file_buffer, src_len);
    if (cmp_status != Z_OK) {
        printf("Compression failed!\n");
        free(file_buffer);
        free(pCmp);
       
    }
    

    fwrite(pCmp, 1, cmp_len, file);
    fclose(file);
}

void Compress(const uint8* const pDataToCompress, uint8* pOutBuff);
void Decompress(const uint8* const pDataToDecompress, uint8* pOutBuff);

void compress_and_save(char* filename, char* outFilename){
    // Priprema za kompresiju
    long file_size;
    uint8 *file_buffer;
    FILE * json = fopen(filename, "rb"); 
    if (!json) {
        printf("Failed to open file!\n");
    }

    // Pomeri pokazivač na kraj fajla kako bi dobio njegovu veličinu
    fseek(json, 0, SEEK_END);
    file_size = ftell(json);  // Dobij veličinu fajla u bajtovima
    rewind(json);  

    file_buffer = (uint8 *)malloc(file_size);
    if (!file_buffer) {
        printf("Failed to allocate memory for file!\n");
        fclose(json);
    }
    fread(file_buffer, 1, file_size, json);
    fclose(json);  // Zatvori fajl nakon čitanja

    uLong src_len = (uLong)file_size;
    uLong cmp_len = compressBound(src_len); // Maksimalna moguća veličina kompresovanih podataka
    uLong uncomp_len = src_len;  // Očekivana dužina dekompresovanih podataka
    uint8 *pCmp = (uint8 *)malloc(cmp_len); // Alociraj memoriju za kompresovane podatke
    
    // Kompresuj podatke
    int cmp_status = compress(pCmp, &cmp_len, file_buffer, src_len);
    if (cmp_status != Z_OK) {
        printf("Compression failed!\n");
        free(file_buffer);
        free(pCmp);
       
    }

    printf("Compressed from %lu to %lu bytes\n", src_len, cmp_len);

    FILE *compressed_file = fopen(outFilename, "wb");
    if (!compressed_file) {
        printf("Failed to open compressed data file!\n");
        free(file_buffer);
        free(pCmp);
      
    }

    fwrite(pCmp, 1, cmp_len, compressed_file);
    fclose(compressed_file);

    free(file_buffer);
    free(pCmp);
}



int main() {
    FILE *json;
    long file_size;
    uint8 *file_buffer;

    // Otvori fajl "data.json" u režimu za čitanje
    json = fopen("data.json", "rb"); // "rb" za binarno čitanje
    if (!json) {
        printf("Failed to open file!\n");
        return 1;
    }

    // Pomeri pokazivač na kraj fajla kako bi dobio njegovu veličinu
    fseek(json, 0, SEEK_END);
    file_size = ftell(json);  // Dobij veličinu fajla u bajtovima
    rewind(json);             // Vrati pokazivač na početak fajla

    // Alociraj memoriju za sadržaj fajla
    file_buffer = (uint8 *)malloc(file_size);
    if (!file_buffer) {
        printf("Failed to allocate memory for file!\n");
        fclose(json);
        return 1;
    }

    // Učitaj sadržaj fajla u memoriju
    fread(file_buffer, 1, file_size, json);
    fclose(json);  // Zatvori fajl nakon čitanja

    // Priprema za kompresiju
    uLong src_len = (uLong)file_size;
    uLong cmp_len = compressBound(src_len); // Maksimalna moguća veličina kompresovanih podataka
    uLong uncomp_len = src_len;  // Očekivana dužina dekompresovanih podataka
    uint8 *pCmp = (uint8 *)malloc(cmp_len); // Alociraj memoriju za kompresovane podatke
    uint8 *pUncomp = (uint8 *)malloc(); // Alociraj memoriju za dekompresovane podatke

    if (!pCmp || !pUncomp) {
        printf("Failed to allocate memory for compression!\n");
        free(file_buffer);
        return 1;
    }

    // Kompresuj podatke
    int cmp_status = compress(pCmp, &cmp_len, file_buffer, src_len);
    if (cmp_status != Z_OK) {
        printf("Compression failed!\n");
        free(file_buffer);
        free(pCmp);
        free(pUncomp);
        return 1;
    }

    printf("Compressed from %lu to %lu bytes\n", src_len, cmp_len);

 FILE *compressed_file = fopen("compressedData.bin", "wb");
    if (!compressed_file) {
        printf("Failed to open compressed data file!\n");
        free(file_buffer);
        free(pCmp);
        free(pUncomp);
        return 1;
    }
    fwrite(pCmp, 1, cmp_len, compressed_file);
    fclose(compressed_file);
    // Dekomprimuj podatke
    cmp_status = uncompress(pUncomp, &uncomp_len, pCmp, cmp_len);
    if (cmp_status != Z_OK) {
        printf("Decompression failed!\n");
        free(file_buffer);
        free(pCmp);
        free(pUncomp);
        return 1;
    }

    printf("Decompressed from %lu to %lu bytes\n", cmp_len, uncomp_len);
 // Zapiši dekompresovane podatke u fajl "decompressedData.json"
    FILE *decompressed_file = fopen("decompressedData.json", "wb");
    if (!decompressed_file) {
        printf("Failed to open decompressed data file!\n");
        free(file_buffer);
        free(pCmp);
        free(pUncomp);
        return 1;
    }
    fwrite(pUncomp, 1, uncomp_len, decompressed_file);
    fclose(decompressed_file);

    // Provera da li su originalni i dekompresovani podaci isti
    if (uncomp_len != src_len || memcmp(file_buffer, pUncomp, src_len) != 0) {
        printf("Decompressed data does not match original!\n");
    } else {
        printf("Decompression successful and data matches original!\n");
    }

    // Oslobodi memoriju
    free(file_buffer);
    free(pCmp);
    free(pUncomp);

    return 0;
}
