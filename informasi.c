#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "informasi.h"

//-------------------JUMLAH PASIEN DAN PENYAKIT------------------//

int compareByJumlahPasienPerTahun(const void *a, const void *b) {
    int jumlahPasienA = ((SummaryPasienPerTahun*)a)->jumlahPasien;
    int jumlahPasienB = ((SummaryPasienPerTahun*)b)->jumlahPasien;
    return (jumlahPasienB - jumlahPasienA);
}

int compareByJumlahPasienPerBulan(const void *a, const void *b) {
    int jumlahPasienA = ((SummaryPasienPerBulan*)a)->jumlahPasien;
    int jumlahPasienB = ((SummaryPasienPerBulan*)b)->jumlahPasien;
    return (jumlahPasienB - jumlahPasienA);
}

int compareByJumlahPenyakit(const void *a, const void *b) {
    int jumlahPenyakitA = ((JumlahPerPenyakit*)a)->jumlah;
    int jumlahPenyakitB = ((JumlahPerPenyakit*)b)->jumlah;
    return (jumlahPenyakitB - jumlahPenyakitA);
}

void laporanJumlahPasienPerBulan(SummaryPasienPerBulan **summary, int pilihanTahun,
                                 NodeRiwayat *headListRiwayat, int *totalPasien,
                                 int urutkan){
    //Inisialisasi
    char bulanBulan[12][20] = {"Januari", "Februari", "Maret", "April", "Mei",
    "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

    *summary = (SummaryPasienPerBulan*)malloc(12*sizeof(SummaryPasienPerBulan));

    for(int i = 0; i < 12; i++){
        strcpy((*summary)[i].bulan, bulanBulan[i]);
        (*summary)[i].jumlahPasien = 0;
    }
    // Perhitungan
    NodeRiwayat *currentRiwayat = headListRiwayat;
    int hariRiwayat;
    char bulanRiwayat[10];
    int tahunRiwayat;
    int angkaBulan;

    while(currentRiwayat != NULL){
        parsingTanggal(currentRiwayat->riwayat->tanggal, &hariRiwayat, bulanRiwayat,
                       &tahunRiwayat);
        if(tahunRiwayat == pilihanTahun){
            angkaBulan = konversiBulan(bulanRiwayat);
            (*summary)[angkaBulan-1].jumlahPasien += 1;
            *totalPasien += 1;
        }
        currentRiwayat = currentRiwayat->next;
    }

    //Pengurutan
    if(urutkan){
        qsort((*summary), 12, sizeof(SummaryPasienPerBulan),
              compareByJumlahPasienPerBulan);
    }
}

void laporanJumlahPasien(int startingYear, int currentYear, NodeRiwayat *headListRiwayat,
                         int tampilkanTahun, int tampilkanBulan, int tahunYangDitampilkan,
                         int urutkanTahun, int urutkanBulan, char **text){
    //Inisialisasi
    char buffer[256];
    int rangeTahun = currentYear - startingYear;
    SummaryPasienPerTahun *summary = NULL;

    if(tampilkanBulan){
        if(tahunYangDitampilkan > currentYear){
            sprintf(buffer, "Tahun %d belum terlalui\n", tahunYangDitampilkan);
            appendString(text, buffer);
            return;
        }
        else if(tahunYangDitampilkan < startingYear){
            sprintf(buffer, "Tahun kurang dari tahun berdirinya klinik\n", tahunYangDitampilkan);
            appendString(text, buffer);
            return;
        }
    }

    //Inisialisasi
    summary = (SummaryPasienPerTahun*)malloc((rangeTahun+1)*sizeof(SummaryPasienPerTahun));
    for(int i = 0; i <= rangeTahun; i++){
        summary[i].tahun = currentYear - i;
        summary[i].jumlahPasien = 0;
    }

    //Perhitungan
    for(int i = 0; i <= rangeTahun; i++){
        laporanJumlahPasienPerBulan(&(summary[i].summaryPasienPerBulan), summary[i].tahun,
                                    headListRiwayat, &(summary[i].jumlahPasien), urutkanBulan);
    }

    //Pengurutan Tahun
    if(urutkanTahun){
        qsort(summary, (rangeTahun+1), sizeof(SummaryPasienPerTahun), compareByJumlahPasienPerTahun);
    }

    //Penampilan laporan
    if(tampilkanTahun){
        for(int i = 0; i <= rangeTahun; i++){
            appendString(text, "--------------INFORMASI JUMLAH PASIEN---------------\n");
            sprintf(buffer, "Tahun %d: %d pasien\n\n", summary[i].tahun, summary[i].jumlahPasien);
            appendString(text, buffer);
            if(tampilkanBulan){
                for(int j = 0; j < 12; j++){
                    sprintf(buffer, "%s: %d pasien\n", summary[i].summaryPasienPerBulan[j].bulan,
                            summary[i].summaryPasienPerBulan[j].jumlahPasien);
                    appendString(text, buffer);
                }
            }
            appendString(text, "\n");
        }
    }
    else{
        if(tampilkanBulan){
            int yearDifference = currentYear-tahunYangDitampilkan;
            appendString(text, "--------------INFORMASI JUMLAH PASIEN---------------\n");
            sprintf(buffer, "Tahun %d: %d pasien\n\n", tahunYangDitampilkan,
                    summary[yearDifference].jumlahPasien);
            appendString(text, buffer);

            for(int i = 0; i < 12; i++){
                sprintf(buffer, "%s: %d pasien\n", summary[yearDifference].summaryPasienPerBulan[i].bulan,
                        summary[yearDifference].summaryPasienPerBulan[i].jumlahPasien);
                appendString(text, buffer);
            }
        }
    }

    //Pembebasan Memori
    for(int i = 0; i <= rangeTahun; i++){
        free(summary[i].summaryPasienPerBulan);
    }
    free(summary);
}

void laporanJumlahPenyakitPerBulan(SummaryPenyakitPerBulan **summary, int pilihanTahun,
                                   NodeRiwayat *headListRiwayat, Penyakit *listPenyakit,
                                   int banyakPenyakit, JumlahPerPenyakit *totalPenyakit,
                                   int urutkan){

    //Inisialisasi
    char bulanBulan[12][20] = {"Januari", "Februari", "Maret", "April", "Mei",
    "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

    *summary = (SummaryPenyakitPerBulan*)malloc(12*sizeof(SummaryPenyakitPerBulan));

    for(int i = 0; i < 12; i++){
        strcpy((*summary)[i].bulan, bulanBulan[i]);
        (*summary)[i].jumlahPerPenyakit = (JumlahPerPenyakit *)malloc(banyakPenyakit*sizeof(JumlahPerPenyakit));
        for(int j = 0; j < banyakPenyakit; j++){
            (*summary)[i].jumlahPerPenyakit[j].nama = malloc(strlen(listPenyakit[j].nama)+1);
            strcpy((*summary)[i].jumlahPerPenyakit[j].nama, listPenyakit[j].nama);
            (*summary)[i].jumlahPerPenyakit[j].jumlah = 0;
        }
    }

    // Perhitungan
    NodeRiwayat *currentRiwayat = headListRiwayat;
    int hariRiwayat;
    char bulanRiwayat[10];
    int tahunRiwayat;
    int indeksPenyakit;
    int angkaBulan;

    while(currentRiwayat != NULL){
        parsingTanggal(currentRiwayat->riwayat->tanggal, &hariRiwayat, bulanRiwayat, &tahunRiwayat);
        if(tahunRiwayat == pilihanTahun){
            for(indeksPenyakit = 0; indeksPenyakit < banyakPenyakit; indeksPenyakit++){
                if(strcmp(listPenyakit[indeksPenyakit].nama, currentRiwayat->riwayat->diagnosis) == 0){
                    angkaBulan = konversiBulan(bulanRiwayat);
                    (*summary)[angkaBulan-1].jumlahPerPenyakit[indeksPenyakit].jumlah += 1;
                    totalPenyakit[indeksPenyakit].jumlah += 1;
                    break;
                }
            } 
        }
        currentRiwayat = currentRiwayat->next;
    }

    //Pengurutan
    if(urutkan){
        for(int i = 0; i < 12; i++){
            qsort((*summary)[i].jumlahPerPenyakit, banyakPenyakit, sizeof(JumlahPerPenyakit), compareByJumlahPenyakit);
        }
    }
}

void laporanJumlahPenyakit(int startingYear, int currentYear, int banyakPenyakit,
                           NodeRiwayat *headListRiwayat, Penyakit *listPenyakit,
                           int tampilkanTahun, int tampilkanBulan,
                           int tahunYangDitampilkan, int urutkanTahun, int urutkanBulan,
                           char **text){
    //Inisialisasi
    char buffer[256];
    int rangeTahun = currentYear - startingYear;
    SummaryPenyakitPerTahun *summary = NULL;

    if(tampilkanBulan){
        if(tahunYangDitampilkan > currentYear){
            sprintf(buffer, "Tahun %d belum terlalui\n", tahunYangDitampilkan);
            appendString(text, buffer);
            return;
        }
        else if(tahunYangDitampilkan < startingYear){
            sprintf(buffer, "Tahun kurang dari tahun berdirinya klinik\n", tahunYangDitampilkan);
            appendString(text, buffer);
            return;
        }
    } 

    summary = (SummaryPenyakitPerTahun*)malloc((rangeTahun+1)*sizeof(SummaryPenyakitPerTahun));

    for(int i = 0; i <= rangeTahun; i++){
        summary[i].tahun = currentYear - i;
        summary[i].jumlahPerPenyakit = (JumlahPerPenyakit *)malloc(banyakPenyakit*sizeof(JumlahPerPenyakit));
        for(int j = 0; j < banyakPenyakit; j++){
            summary[i].jumlahPerPenyakit[j].nama = malloc(strlen(listPenyakit[j].nama)+1);
            strcpy(summary[i].jumlahPerPenyakit[j].nama, listPenyakit[j].nama);
            summary[i].jumlahPerPenyakit[j].jumlah = 0;
        }
    }
    // Perhitungan
    for(int i = 0; i <= rangeTahun; i++){
        laporanJumlahPenyakitPerBulan(&(summary[i].summaryPenyakitPerBulan), summary[i].tahun,
                                      headListRiwayat, listPenyakit, banyakPenyakit,
                                      summary[i].jumlahPerPenyakit, urutkanBulan);
    }

    //Pengurutan
    if(urutkanTahun){
        for(int i = 0; i <= rangeTahun; i++){
            qsort(summary[i].jumlahPerPenyakit, banyakPenyakit, sizeof(JumlahPerPenyakit),
                  compareByJumlahPenyakit);
        }
    }
    
    //Penyusunan Laporan
    if(tampilkanTahun){
        for(int i = 0; i <= rangeTahun; i++){
            appendString(text, "--------------INFORMASI JUMLAH PENYAKIT---------------\n");
            sprintf(buffer, "Tahun %d\n", summary[i].tahun);
            appendString(text, buffer);

            for(int j = 0; j < banyakPenyakit; j++){
                sprintf(buffer, "\t%s: %d kasus\n", summary[i].jumlahPerPenyakit[j].nama,
                        summary[i].jumlahPerPenyakit[j].jumlah);
                appendString(text, buffer);
                free(summary[i].jumlahPerPenyakit[j].nama);
            }

            if(tampilkanBulan){
                    for(int k = 0; k < 12; k++){
                        sprintf(buffer, "%s\n", summary[i].summaryPenyakitPerBulan[k].bulan);
                        appendString(text, buffer);

                        for(int l = 0; l < banyakPenyakit; l++){
                            sprintf(buffer, "\t%s: %d kasus\n",
                                    summary[i].summaryPenyakitPerBulan[k].jumlahPerPenyakit[l].nama,
                                    summary[i].summaryPenyakitPerBulan[k].jumlahPerPenyakit[l].jumlah);
                            appendString(text, buffer);
                            free(summary[i].summaryPenyakitPerBulan[k].jumlahPerPenyakit[l].nama);
                        }
                        free(summary[i].summaryPenyakitPerBulan[k].jumlahPerPenyakit);
                    }
                    free(summary[i].summaryPenyakitPerBulan);
                }
            free(summary[i].jumlahPerPenyakit);
            appendString(text, "\n");
        }
    }
    if(!tampilkanTahun){
        if(tampilkanBulan){
            appendString(text, "--------------INFORMASI JUMLAH PENYAKIT---------------\n");
            sprintf(buffer, "Tahun %d\n", tahunYangDitampilkan);
            appendString(text, buffer);

            int yearDifference = currentYear - tahunYangDitampilkan;

            for(int j = 0; j < banyakPenyakit; j++){
                sprintf(buffer, "\t%s: %d kasus\n",
                        summary[yearDifference].jumlahPerPenyakit[j].nama,
                        summary[yearDifference].jumlahPerPenyakit[j].jumlah);
                appendString(text, buffer);
                free(summary[yearDifference].jumlahPerPenyakit[j].nama);
            }
            printf("\n");
            for(int k = 0; k < 12; k++){
                sprintf(buffer, "%s\n", summary[yearDifference].summaryPenyakitPerBulan[k].bulan);
                appendString(text, buffer);

                for(int l = 0; l < banyakPenyakit; l++){
                    sprintf(buffer, "\t%s: %d kasus\n",
                            summary[yearDifference].summaryPenyakitPerBulan[k].jumlahPerPenyakit[l].nama,
                            summary[yearDifference].summaryPenyakitPerBulan[k].jumlahPerPenyakit[l].jumlah);
                    appendString(text, buffer);
                    free(summary[yearDifference].summaryPenyakitPerBulan[k].jumlahPerPenyakit[l].nama);
                }
                free(summary[yearDifference].summaryPenyakitPerBulan[k].jumlahPerPenyakit);
            }
            free(summary[yearDifference].summaryPenyakitPerBulan);
        }
    }
    free(summary);
}

int compareByTanggal(const void *a, const void *b) {
    NodeRiwayat *nodeA = *(NodeRiwayat **)a;
    NodeRiwayat *nodeB = *(NodeRiwayat **)b;
    
    int hariA, hariB, tahunA, tahunB;
    char bulanA[20], bulanB[20];
    
    parsingTanggal(nodeA->riwayat->kontrol, &hariA, bulanA, &tahunA);
    parsingTanggal(nodeB->riwayat->kontrol, &hariB, bulanB, &tahunB);
    
    int bulanIntA = konversiBulan(bulanA);
    int bulanIntB = konversiBulan(bulanB);

    if (tahunA != tahunB) {
        return tahunA - tahunB;
    } else if (bulanIntA != bulanIntB) {
        return bulanIntA - bulanIntB;
    } else {
        return hariA - hariB;
    }
}

void pasienPerluKontrol(char *currentDate, NodeRiwayat *headListRiwayat, NodePasien *headListPasien, char **text){

    NodeRiwayat *currentRiwayat = headListRiwayat;
    NodeRiwayat **listPasienPerluKontrol = NULL;
    NodePasien *pasienPerluKontrol;

    char buffer[256];
    int banyakPasienPerluKontrol = 0;
    int perluKontrol = 0;

    //Pengumpulan riwayat-riwayat yang perlu melakukan kontrol
    while (currentRiwayat != NULL) {
        perluKontrol = bandingkanTanggal(currentRiwayat->riwayat->kontrol, currentDate);
        if (perluKontrol){
            banyakPasienPerluKontrol++;
            listPasienPerluKontrol = (NodeRiwayat **)realloc(listPasienPerluKontrol,
                                     (banyakPasienPerluKontrol) * sizeof(NodeRiwayat *));
            listPasienPerluKontrol[banyakPasienPerluKontrol-1] = currentRiwayat;
        }
        currentRiwayat = currentRiwayat->next;
    }

    //Pengecekan banyak pasien perlu kontrol
    if (banyakPasienPerluKontrol == 0) {
        appendString(text, "Tidak ada pasien yang perlu kontrol\n");
        return;
    }

    appendString(text, "---------------Pasien Perlu Kontrol---------------\n");
    appendString(text, "\nNo. Nama : Tanggal Kontrol\n\n");

    //Pengurutan berdasarkan Tanggal
    qsort(listPasienPerluKontrol, banyakPasienPerluKontrol, sizeof(NodeRiwayat *), compareByTanggal);

    //Penyusunan Laporan
    int count = 1;
    for (int i = 0; i < banyakPasienPerluKontrol; i++) {
        pasienPerluKontrol = cariPasien(headListPasien, listPasienPerluKontrol[i]->riwayat->id);
        if (pasienPerluKontrol) {
            sprintf(buffer, "%d. %s : %s\n", count, pasienPerluKontrol->pasien->nama,
                    listPasienPerluKontrol[i]->riwayat->kontrol);
            appendString(text, buffer);
            count += 1;
        }
    }

    //Pembebasan Memori
    free(listPasienPerluKontrol);
}

//-------------------PENDAPATAN------------------//


void calcMonthlyIncome(MonthlyIncome **monthlyIncome, int year, NodeRiwayat *headIncome, int *totalIncome) {

    char bulanBulan[12][20] = {"Januari", "Februari", "Maret", "April", "Mei",
    "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

    *monthlyIncome = (MonthlyIncome*)malloc(12*sizeof(MonthlyIncome));
    
    for(int i = 0; i < 12; i++){
        strcpy((*monthlyIncome)[i].monthYear, bulanBulan[i]);
        (*monthlyIncome)[i].income = 0;
    }

    NodeRiwayat *currentNodeMonth = headIncome;
    int hari;
    char bulan[10];
    int tahun;

    while (currentNodeMonth != NULL) {
        parsingTanggal(currentNodeMonth->riwayat->tanggal, &hari, bulan, &tahun);
        if(tahun == year){
            (*monthlyIncome)[konversiBulan(bulan)-1].income += currentNodeMonth->riwayat->biaya;  
            *totalIncome += currentNodeMonth->riwayat->biaya;
        }
        currentNodeMonth = currentNodeMonth->next;
    }
}

void calcYearlyIncome(int startingYear, int currentYear, NodeRiwayat *headListRiwayat, int tampilkanRataRata, int tampilkanTahun,
                      int tampilkanBulan, int tahunYangDitampilkan, char **text){
    char buffer[256];
    if(tampilkanBulan){
        if(tahunYangDitampilkan > currentYear){
            //printf("Tahun %d belum terlalui\n", tahunYangDitampilkan);
            sprintf(buffer, "Tahun %d belum terlalui\n", tahunYangDitampilkan);
            appendString(text, buffer);
            return;
        }
        else if(tahunYangDitampilkan < startingYear){
            sprintf(buffer, "Tahun kurang dari tahun berdirinya klinik\n", tahunYangDitampilkan);
            appendString(text, buffer);
            return;
        }
    }

    int rangeTahun = currentYear - startingYear;
    
    YearlyIncome *yearlyIncome = (YearlyIncome*)malloc((rangeTahun+1)*sizeof(YearlyIncome));

    for(int i = 0; i <= rangeTahun; i++){
        yearlyIncome[i].year = currentYear - i;
        yearlyIncome[i].income = 0;
    }

    // Perhitungan
    double totalPendapatan = 0.0;
    for(int i = 0; i <= rangeTahun; i++){
        calcMonthlyIncome(&(yearlyIncome[i].monthlyIncome), yearlyIncome[i].year, headListRiwayat, &(yearlyIncome[i].income));
        totalPendapatan += yearlyIncome[i].income;
    }

    if(tampilkanRataRata){
        appendString(text, "--------------INFORMASI PENDAPATAN RATA-RATA---------------\n");
        sprintf(buffer, "Rata-Rata Pendapatan Per Tahun: Rp %.2lf\n\n", totalPendapatan/(rangeTahun+1));
        appendString(text, buffer);
    }

    if(tampilkanTahun){
        for(int i = 0; i <= rangeTahun; i++){
            appendString(text, "--------------INFORMASI PENDAPATAN---------------\n");
            //printf("%d: %d\n\n", yearlyIncome[i].year, yearlyIncome[i].income);
            sprintf(buffer, "Tahun %d: Rp %d\n\n", yearlyIncome[i].year, yearlyIncome[i].income);
            appendString(text, buffer);
            if(tampilkanBulan){
                for(int j = 0; j < 12; j++){
                    sprintf(buffer, "%s: Rp %d\n", yearlyIncome[i].monthlyIncome[j].monthYear, yearlyIncome[i].monthlyIncome[j].income);
                    appendString(text, buffer);

                }
            }
            appendString(text, "\n");
        }

    }
    else{
        if(tampilkanBulan){
            int yearDifference = currentYear - tahunYangDitampilkan;
            appendString(text, "--------------INFORMASI JUMLAH PENYAKIT---------------\n");
            sprintf(buffer, "Tahun %d: Rp %d\n\n", tahunYangDitampilkan, yearlyIncome[yearDifference].income);
            appendString(text, buffer);
            for(int i = 0; i < 12; i++){
                sprintf(buffer, "%s: %d\n", yearlyIncome[yearDifference].monthlyIncome[i].monthYear, yearlyIncome[yearDifference].monthlyIncome[i].income);
                appendString(text, buffer);
            }
        }
    }
    
    
    for(int i = 0; i <= rangeTahun; i++){
        free(yearlyIncome[i].monthlyIncome);
    }
    free(yearlyIncome);
}

//---------------------INFORMASI RIWAYAT PASIEN------------------------//

void informasiPasien(NodePasien *headListPasien, NodeRiwayat *headListRiwayat, char *id_pasien, char **text) {
    NodeRiwayat *riwayat = headListRiwayat;
    NodeRiwayat **listRiwayatPasien = NULL;
    NodePasien *pasien = NULL;
    int banyakRiwayat = 0;
    char buffer[256];

    // Meminta ID pasien dari pengguna
    /*
    char id_pasien[11];
    printf("Masukkan ID pasien: ");
    fgets(id_pasien, 11, stdin);
    */

    // Mencari pasien berdasarkan ID
    pasien = cariPasien(headListPasien, id_pasien);
    if (pasien == NULL) {
        //printf("Pasien dengan ID %s tidak ditemukan.\n", id_pasien);
        sprintf(buffer, "Pasien dengan ID %s tidak ditemukan.\n", id_pasien);
        appendString(text, buffer);
        return;
    }

    // Menampilkan informasi pasien
    //printf("Informasi Pasien:\n");
    appendString(text, "--------------INFORMASI PASIEN---------------\n");
    //printf("Nama: %s\n", pasien->pasien->nama);
    sprintf(buffer, "Nama: %s\n", pasien->pasien->nama);
    appendString(text, buffer);
    //printf("Alamat: %s\n", pasien->pasien->alamat);
    sprintf(buffer, "Alamat: %s\n", pasien->pasien->alamat);
    appendString(text, buffer);
    //printf("Kota Asal: %s\n", pasien->pasien->kota);
    sprintf(buffer, "Kota Asal: %s\n", pasien->pasien->kota);
    appendString(text, buffer);
    //printf("Tempat Lahir: %s\n", pasien->pasien->tempatLahir);
    sprintf(buffer, "Tempat Lahir: %s\n", pasien->pasien->tempatLahir);
    appendString(text, buffer);
    //printf("Tanggal Lahir: %s\n", pasien->pasien->tanggalLahir);
    sprintf(buffer, "Tanggal Lahir: %s\n", pasien->pasien->tanggalLahir);
    appendString(text, buffer);
    //printf("Usia: %d\n", pasien->pasien->usia);
    sprintf(buffer, "Usia: %d\n", pasien->pasien->usia);
    appendString(text, buffer);
    //printf("No BPJS: %s\n", pasien->pasien->noBPJS);
    sprintf(buffer, "No BPJS: %s\n", pasien->pasien->noBPJS);
    appendString(text, buffer);
    //printf("ID: %s\n", pasien->pasien->id);
    sprintf(buffer, "ID: %s\n\n", pasien->pasien->id);
    appendString(text, buffer);

    // Mencari dan menampilkan riwayat medis pasien
    //printf("\nRiwayat Medis:\n");
    appendString(text, "--------------RIWAYAT MEDIS---------------\n");

    // Inisialisasi variabel untuk tanggal
    while (riwayat != NULL) {
        if(strcmp(riwayat->riwayat->id, id_pasien) == 0){
            listRiwayatPasien= (NodeRiwayat **)realloc(listRiwayatPasien, (banyakRiwayat + 1) * sizeof(NodeRiwayat *));
            listRiwayatPasien[banyakRiwayat] = riwayat;
            banyakRiwayat++;
        }
        riwayat = riwayat->next;
    }

    if(banyakRiwayat == 0){
        //printf("Tidak ada riwayat untuk pasien dengan ID %s", id_pasien);
        sprintf(buffer, "Tidak ada riwayat untuk pasien dengan ID %s", id_pasien);
        appendString(text, buffer);
        return;
    }

    qsort(listRiwayatPasien, banyakRiwayat, sizeof(NodeRiwayat*), compareByTanggal);

    for (int i = 0; i < banyakRiwayat; i++) {
        //printf("Tanggal: %s\n", listRiwayatPasien[i]->riwayat->tanggal);
        sprintf(buffer, "Tanggal: %s\n", listRiwayatPasien[i]->riwayat->tanggal);
        appendString(text, buffer);
        //printf("Diagnosis: %s\n", listRiwayatPasien[i]->riwayat->diagnosis);
        sprintf(buffer, "Diagnosis: %s\n", listRiwayatPasien[i]->riwayat->diagnosis);
        appendString(text, buffer);
        //printf("Tindakan: %s\n", listRiwayatPasien[i]->riwayat->tindakan);
        sprintf(buffer, "Tindakan: %s\n", listRiwayatPasien[i]->riwayat->tindakan);
        appendString(text, buffer);
        //printf("Kontrol: %s\n", listRiwayatPasien[i]->riwayat->kontrol);
        sprintf(buffer, "Kontrol: %s\n", listRiwayatPasien[i]->riwayat->kontrol);
        appendString(text, buffer);
        //printf("Biaya: %d\n", listRiwayatPasien[i]->riwayat->biaya);
        sprintf(buffer, "Biaya: %d\n", listRiwayatPasien[i]->riwayat->biaya);
        appendString(text, buffer);
        //printf("\n");
        appendString(text, "\n");
    }

    free(listRiwayatPasien);
}