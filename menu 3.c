
#include <stdio.h>
#include <string.h>

#define MAX_BUKU     100
#define FILE_BUKU    "databuku.txt"


typedef struct {
    char kode[10];
    char nama[100];
    char jenis[50];
    double harga;
} Buku;


Buku daftarBuku[MAX_BUKU];
int  jumlahBuku = 0;


void bacaDataBuku(void) {
    FILE *fp = fopen(FILE_BUKU, "r");
    jumlahBuku = 0;

    if (fp == NULL) {
        printf("Info: %s belum ditemukan, memulai dengan data buku kosong.\n", FILE_BUKU);
        return;
    }

    while (jumlahBuku < MAX_BUKU &&
           fscanf(fp, "%9[^|]|%99[^|]|%49[^|]|%lf\n",
                  daftarBuku[jumlahBuku].kode,
                  daftarBuku[jumlahBuku].nama,
                  daftarBuku[jumlahBuku].jenis,
                  &daftarBuku[jumlahBuku].harga) == 4) {
        jumlahBuku++;
    }

    fclose(fp);
}

void viewDataBuku(void) {
    printf("\n=== DAFTAR SELURUH DATA BUKU ===\n");

    if (jumlahBuku == 0) {
        printf("Belum ada data buku yang tersedia.\n");
        return;
    }

    printf("%-4s %-10s %-30s %-15s %s\n", "No", "Kode", "Nama Buku", "Jenis", "Harga");
    printf("--------------------------------------------------------------------\n");

    for (int i = 0; i < jumlahBuku; i++) {
        printf("%-4d %-10s %-30s %-15s Rp%.2lf\n",
               i + 1,
               daftarBuku[i].kode,
               daftarBuku[i].nama,
               daftarBuku[i].jenis,
               daftarBuku[i].harga);
    }
}



