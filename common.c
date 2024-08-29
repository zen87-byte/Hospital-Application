//PREPROCESSOR DAN MACRO
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include <time.h>
#define MAX_SIZE 256

//DEFINISI FUNGSI
void getCurrentDate(char *buffer, size_t bufferSize) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    const char *bulanIndonesia[] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni",
                                      "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

    snprintf(buffer, bufferSize, "%02d %s %d", tm->tm_mday, bulanIndonesia[tm->tm_mon], tm->tm_year + 1900);
}

void appendString(char **dest, const char *src) {
    if (src == NULL) return;

    size_t panjangDest;

    if (*dest) {
        panjangDest = strlen(*dest);
    } else {
        panjangDest = 0;
    }
    size_t panjangSrc = strlen(src);
    size_t panjangDestBaru = panjangDest + panjangSrc + 1;

    char *destBaru = realloc(*dest, panjangDestBaru);

    /*
    if (new_str == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    */

    strcpy(destBaru + panjangDest, src);
    *dest = destBaru;
}

void ubahFormatTanggal(char *tanggal, char *tanggalTerformat){
    //Mengubah format tanggal "DD-MM-YY" jadi "DD BULAN YYYY"
    char hyphen1[2];
    char hyphen2[2];
    strncpy(hyphen1, tanggal+2, 1);
    hyphen1[1] = '\0';
    strncpy(hyphen2, tanggal+1, 1);
    hyphen2[1] = '\0';

    //Cek apakah perlu diubah
    if(strcmp(hyphen1, "-") == 0 ||strcmp(hyphen2, "-") == 0){ //Perlu diubah
        char hari[3];
        char bulan[4];
        char tahun[3];
        char bulanTerformat[10];

        // Parsing hari
        if(strcmp(hyphen1, "-") == 0 ){
            strncpy(hari, tanggal, 2);
            hari[2] = '\0';
        }
        else{
            strncpy(hari, tanggal, 1);
            hari[1] = '\0';
        }

        //Parsing bulan
        strncpy(bulan, tanggal + 3, 3);
        bulan[3] = '\0';

        //Parsing tahun
        strncpy(tahun, tanggal + 7, 2);
        tahun[2] = '\0';

        // Ubah hari dan tanggal ke integer
        int hariInt = atoi(hari);
        int tahunInt = atoi(tahun);

        //Penyesuaian tahun sesuai akhirannya
        if(tahunInt > 24){
            tahunInt += 1900;
        }
        else{
            tahunInt += 2000;
        }

        char bulanBulanAbv[12][4] = {
            "Jan", "Feb", "Mar", "Apr", "May", "June", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
        };
        char bulanBulan[12][10] = {
            "Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"
        };
        
        int i;
        //Mengubah singkatan menjadi nama bulan seluruhnya
        for( i = 0; i < 12; i++){
            if(strcmp(bulan, bulanBulanAbv[i]) == 0){
                strcpy(bulanTerformat, bulanBulan[i]);
                break;
            }
        }
        //Kalau ada singkatan yang aneh
        if(i == 12){
            strcpy(bulanTerformat, "XX");
        }
        // Memformatkan tanggal
        sprintf(tanggalTerformat, "%d %s %d", hariInt, bulanTerformat, tahunInt);
        //printf("%s\n", tanggalTerformat);
    }
    else{//Kalau tidak perlu diubah
        strcpy(tanggalTerformat, tanggal);
    }
}

int konversiBulan(char *bulan){
    //Mengonversi nama bulan menjadi angka urutan bulan tersebut
    char bulanBulan[12][20] = {"Januari", "Februari", "Maret", "April", "Mei",
    "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
    
    for(int i = 0; i < 12; i++){
        if(strcmp(bulan, bulanBulan[i]) == 0){
            return i+1;
        }
    }
    return -1;
}

void parsingTanggal(char *tanggal, int *hari, char *bulan, int *tahun){
    //Mendapatkan hari, bulan, dan tahun dari string tanggal
    char tanggalCpy[20];
    char *token;

    strcpy(tanggalCpy, tanggal);

    //Parse hari
    token = strtok(tanggalCpy, " ");
    *hari = atoi(token);

    //Parse bulan
    token = strtok(NULL, " ");
    strcpy(bulan, token);

    //Parse tahun
    token = strtok(NULL, "\0");
    *tahun = atoi(token);
}

int bandingkanTanggal(char *tanggal1, char *tanggal2){ //Cek apakah tanggal 1 sesudah tanggal 2
    //Return 1 kalau TRUE, return 0 kalau FALSE
    int hari1;
    int hari2;
    char bulan1[20];
    char bulan2[20];
    int tahun1;
    int tahun2;
    //Parsing kedua tanggal

    parsingTanggal(tanggal1, &hari1, bulan1, &tahun1);

    parsingTanggal(tanggal2, &hari2, bulan2, &tahun2);

    if(tahun1 > tahun2){
        return 1;
    }
    
    if(tahun1 == tahun2){
        int angkaBulan1, angkaBulan2;
        angkaBulan1 = konversiBulan(bulan1);
        angkaBulan2 = konversiBulan(bulan2);
        if(angkaBulan1 > angkaBulan2){
            return 1;
        }
        if(angkaBulan1 == angkaBulan2){
            if(hari1 >= hari2){
                return 1;
            }
        }
    }
    return 0;
}

int ubahFormatBiaya(char *biayaStr) {
    //Mengubah format biaya dari "XXX.XXX" menjadi "XXXXXX"
    char *biayaBelumTerformat = malloc(strlen(biayaStr) + 1);
    char *token;
    char biayaTerformat[20] = "";
    strcpy(biayaBelumTerformat, biayaStr);

    //Parsing string
    token = strtok(biayaBelumTerformat, ".");

    while (token) {
        strcat(biayaTerformat, token);
        token = strtok(NULL, ".");
    }
    
    int biayaTerformatInt = atoi(biayaTerformat);

    free(biayaBelumTerformat);
    return biayaTerformatInt;
}

void insertNodeBiaya(NodeBiaya **headListBiaya, NodeBiaya **tailListBiaya, char *tindakan, int biaya){
    //Menambahkan node biaya ke linked list biaya
    NodeBiaya *lk = (NodeBiaya*) malloc(sizeof(NodeBiaya));
    /*
    if(lk == NULL) {
        perror("Gagal mengalokasikan memori untuk biaya node");
        exit(EXIT_FAILURE);
    }
    */
    //Inisialisasi
    lk->biaya = NULL;
    lk->next = NULL;
    lk->prev = NULL;
    //Penglokasian memori
    lk->biaya = (Biaya*)malloc(sizeof(Biaya));
    /*
    if(lk->biaya == NULL) {
        perror("Gagal mengalokasikan memori untuk biaya");
        exit(EXIT_FAILURE);
    }
    */
    //Inisialisasi
    lk->biaya->tindakan = NULL;
    //Pengalokasian memori
    lk->biaya->tindakan = malloc(strlen(tindakan) + 1);
    //Pemasukan nilai
    strcpy(lk->biaya->tindakan, tindakan);
    lk->biaya->biaya = biaya;
    if(*headListBiaya == NULL){
        *headListBiaya = lk;
        *tailListBiaya = lk;
    } else {
        lk->prev = *tailListBiaya;
        (*tailListBiaya)->next = lk;
        *tailListBiaya = lk;
    }
}

/*
void deleteNodeBiaya(NodeBiaya *biaya, NodeBiaya **headListBiaya, NodeBiaya **tailListBiaya){
    //Menghapus node biaya dari linked list biaya
    if(*headListBiaya == biaya){
        if(*tailListBiaya != biaya){
            *headListBiaya = biaya->next;
        }
    }
    else if(*tailListBiaya == biaya){
        *tailListBiaya = biaya->prev;
    }
    else{
        biaya->prev->next = biaya->next;
        biaya->next->prev = biaya->prev;
    }
    if(biaya->biaya) {
        free(biaya->biaya->tindakan);
        free(biaya->biaya);
        }
    free(biaya);
}
*/

void tambahPenyakit(char *namaPenyakit, int *banyakPenyakit, Penyakit **listPenyakit){
    //Menambahkan penyakit ke list penyakit
    if(*banyakPenyakit == 0){
        (*listPenyakit) = (Penyakit *)malloc(sizeof(Penyakit));
    }
    else{
        int sudahAda = 0;
        //Cek apakah penyakit sudah terdaftar
        for(int i = 0; i < *banyakPenyakit; i++){
            if(strcmp((*listPenyakit)[i].nama, namaPenyakit) == 0){
                sudahAda = 1;
                break;
            }
        }
        //Kalau sudah ada, tidak perlu ditambahkan
        if(sudahAda){
            return;
        }
        else{
            (*listPenyakit) = (Penyakit *)realloc((*listPenyakit), (*banyakPenyakit+1) * sizeof(Penyakit));
        }
    }

    (*listPenyakit)[*banyakPenyakit].nama = malloc(strlen(namaPenyakit)+1);
    strcpy((*listPenyakit)[*banyakPenyakit].nama, namaPenyakit);

    *banyakPenyakit += 1;
}

void readBiaya(NodeBiaya **headListBiaya, NodeBiaya **tailListBiaya, char *namaFile){
    //Membaca isi file biaya.csv
    char buffer[MAX_SIZE];
    char *token;
    FILE *fileBiaya;
    //printf("Masukkan nama file: ");
    //scanf("%s", namaFile);
    fileBiaya = fopen(namaFile, "r+");
    if(fileBiaya == NULL){
        printf("Tidak ada file bernama %s\n", namaFile);
        //sprintf(buffer, "Tidak ada file bernama %s\n", namaFile);
        //appendString(text, buffer);
        return;
    }
    fgets(buffer, MAX_SIZE, fileBiaya); // Skip header
    //Pembacaan isi file
    char *tindakan;
    char *biayaStr;
    int biaya;
    while(fgets(buffer, MAX_SIZE, fileBiaya) != NULL){
        // Melewati kolom nomor
        strtok(buffer, ",");
        // Baca tindakan
        tindakan = strtok(NULL, ",");
        // Baca biaya
        biayaStr = strtok(NULL, "\n");
        biaya = ubahFormatBiaya(biayaStr);
        //Penambahan node
        insertNodeBiaya(headListBiaya, tailListBiaya, tindakan, biaya);
        /*
        printf("%s, %d\n", (*tailListBiaya)->biaya->tindakan, (*tailListBiaya)->biaya->biaya);
        */
    }
    fclose(fileBiaya);
}

void printBiaya(NodeBiaya *headListBiaya, char **text){
    //Print semua node biaya dari linked list biaya
    int count = 1;
    NodeBiaya *lk = headListBiaya;
    char buffer[256];
    appendString(text, "===========================================================\n");
    while(lk){
        //printf("%s, %d\n", lk->biaya->tindakan, lk->biaya->biaya);
        sprintf(buffer, "%d, %s, %d\n", count, lk->biaya->tindakan, lk->biaya->biaya);
        appendString(text, buffer);
        lk = lk->next;
        count++;
    }
    appendString(text, "===========================================================\n");
}

NodePasien* cariPasien(NodePasien* startingPasien, char * idPasien){
    //Mencari node pasien berdasarkan id pasien
    NodePasien* pasien = startingPasien;
    while(pasien != NULL){
        if(strcmp(pasien->pasien->id, idPasien) == 0){
            break;
        }
        pasien = pasien->next;
    }
    return pasien; //Kalau NULL, tidak ditemukan
}

NodeBiaya* cariBiaya(NodeBiaya *startingBiaya, char *tindakan){
    //Mencari node biaya berdasarkan tindakan
    NodeBiaya* nodeBiaya = startingBiaya;
    while(nodeBiaya != NULL){
        if(strcmp(nodeBiaya->biaya->tindakan, tindakan) == 0){
            break;
        }
        nodeBiaya = nodeBiaya->next;
    }
    return nodeBiaya; //Kalau NULL, tidak ditemukan
}

/*
NodeRiwayat* cariRiwayat(NodeRiwayat *startingRiwayat, char * id_pasien, char *tanggal, int isKontrol){
    //Mencari node riwayat berdasarkan 4 hal, id pasien saja atau id pasien dan tanggal riwayat atau tanggal riwayat saja atau tanggal kontrol saja
    //Inisialiasi variabel lokal
    NodeRiwayat* riwayat = startingRiwayat;
    char *token;
    int hariRiwayat;
    char bulanRiwayat[20];
    int tahunRiwayat;

    //Proses pencarian
    while(riwayat != NULL){
        if(id_pasien != NULL){ 
            if(tanggal != NULL){ //Mencari riwayat berdasarkan id_pasien dan tanggal riwayat
                if(strcmp(riwayat->riwayat->id, id_pasien) == 0 && strcmp(riwayat->riwayat->tanggal, tanggal) == 0){
                    return riwayat;
                }
            }
            if(strcmp(riwayat->riwayat->id, id_pasien) == 0){ //Mencari riwayat berdasarkan id_pasien saja
                return riwayat;
            }
        }
        else{
            if(isKontrol != 1){ //Mencari riwayat berdasarkan tanggal riwayat
                if(strcmp(riwayat->riwayat->tanggal, tanggal) == 0){
                    return riwayat;
                }
            }
            else{ //Mencari riwayat berdasarkan tanggal kontrol
                if(strcmp(riwayat->riwayat->kontrol, tanggal) == 0){
                    return riwayat;
                }
            }
        }
        riwayat = riwayat->next;
    }
    return riwayat; //Kalau NULL, tidak ditemukan lagi
}
*/

/*
void saveBiaya(NodeBiaya *headListBiaya){
    //Menyimpan isi linked list biaya ke file biaya.csv
    int count = 1;
    FILE *fileBiaya = NULL;
    fileBiaya = fopen("biaya.csv", "w");
    if (fileBiaya) {
        fprintf(fileBiaya, "No,Aktivitas,Biaya (Rp)\n");
        NodeBiaya *current = headListBiaya;
        count = 1;
        while (current != NULL) {
            fprintf(fileBiaya, "%d,%s,%d\n", count, current->biaya->tindakan, current->biaya->biaya);
            current = current->next;
            count += 1;
        }
    }
}
*/

void bersihkanListBiaya(NodeBiaya **headListBiaya){
    NodeBiaya *lkb1 = *headListBiaya;
    NodeBiaya *lkb2;
    while(lkb1 != NULL){
        lkb2 = lkb1->next;
        if(lkb1->biaya) {
            free(lkb1->biaya->tindakan);
            free(lkb1->biaya);
        }
        free(lkb1);
        lkb1 = lkb2;
    }
    *headListBiaya = NULL;
}
