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


void simpanDataBuku(void) {
    FILE *fp = fopen(FILE_BUKU, "w");  /* mode "w" otomatis membuat file baru jika belum ada */
    if (fp == NULL) {
        printf("Error: Gagal membuka/membuat file %s untuk menyimpan data.\n", FILE_BUKU);
        return;
    }

    for (int i = 0; i < jumlahBuku; i++) {
        fprintf(fp, "%s|%s|%s|%.2lf\n",
                daftarBuku[i].kode,
                daftarBuku[i].nama,
                daftarBuku[i].jenis,
                daftarBuku[i].harga);
    }

    fclose(fp);
}


void generateKodeBuku(char *kodeOut) {
    sprintf(kodeOut, "BK%03d", jumlahBuku + 1);
}


void inputDataBuku(void) {
    if (jumlahBuku >= MAX_BUKU) {
        printf("\nMaaf, kapasitas data buku sudah penuh (maks %d data).\n", MAX_BUKU);
        return;
    }

    Buku bukuBaru;


    generateKodeBuku(bukuBaru.kode);

    printf("\n=== INPUT DATA BUKU BARU ===\n");
    printf("Kode Buku otomatis : %s\n", bukuBaru.kode);

    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    printf("Nama Buku  : ");
    fgets(bukuBaru.nama, sizeof(bukuBaru.nama), stdin);
    bukuBaru.nama[strcspn(bukuBaru.nama, "\n")] = '\0'; /* hapus newline di akhir */

    printf("Jenis Buku : ");
    fgets(bukuBaru.jenis, sizeof(bukuBaru.jenis), stdin);
    bukuBaru.jenis[strcspn(bukuBaru.jenis, "\n")] = '\0';

    printf("Harga Buku : ");
    while (scanf("%lf", &bukuBaru.harga) != 1 || bukuBaru.harga < 0) {
        printf("Input tidak valid. Masukkan harga berupa angka (>= 0): ");
        while ((c = getchar()) != '\n' && c != EOF) { } /* bersihkan buffer salah */
    }

    daftarBuku[jumlahBuku] = bukuBaru;
    jumlahBuku++;

    simpanDataBuku();

    printf("\nData buku '%s' dengan kode %s berhasil ditambahkan!\n",
           bukuBaru.nama, bukuBaru.kode);
}
