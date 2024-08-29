#ifndef INFORMASI_H
#define INFORMASI_H

#include "common.h"

//STRUKTUR DATA
//-------------------JUMLAH PASIEN DAN PENYAKIT------------------//
typedef struct{
    char bulan[10];
    int jumlahPasien;
} SummaryPasienPerBulan;

typedef struct{
    int tahun;
    int jumlahPasien;
    SummaryPasienPerBulan *summaryPasienPerBulan;
} SummaryPasienPerTahun;

typedef struct{
    char bulan[10];
    JumlahPerPenyakit *jumlahPerPenyakit;
} SummaryPenyakitPerBulan;

typedef struct{
    int tahun;
    JumlahPerPenyakit *jumlahPerPenyakit;
    SummaryPenyakitPerBulan *summaryPenyakitPerBulan;
} SummaryPenyakitPerTahun;

//-------------------PENDAPATAN------------------//
typedef struct{
    char monthYear[20];
    int income;
} MonthlyIncome;

typedef struct{
    int year;
    int income;
    MonthlyIncome *monthlyIncome;
} YearlyIncome;

//FUNGSI
//-------------------JUMLAH PASIEN DAN PENYAKIT------------------//
void laporanJumlahPasien(int startingYear, int currentYear, NodeRiwayat *headListRiwayat, int tampilkanTahun,
                                 int tampilkanBulan, int tahunYangDitampilkan, int urutkanTahun, int urutkanBulan, char **text);
void laporanJumlahPasienPerBulan(SummaryPasienPerBulan **summary, int pilihanTahun, NodeRiwayat *headListRiwayat, int *totalPasien, int urutkan);
void laporanJumlahPenyakit(int startingYear, int currentYear, int banyakPenyakit, NodeRiwayat *headListRiwayat,
                                    Penyakit *listPenyakit, int tampilkanTahun, int tampilkanBulan, int tahunYangDitampilkan,
                                    int urutkanTahun, int urutkanBulan, char **text);
void laporanJumlahPenyakitPerBulan(SummaryPenyakitPerBulan **summary, int pilihanTahun, NodeRiwayat *headListRiwayat,
                                   Penyakit *listPenyakit, int banyakPenyakit, JumlahPerPenyakit *totalPenyakit, int urutkan);

//-------------------PENDAPATAN------------------//
void calcMonthlyIncome(MonthlyIncome **monthlyIncome, int year, NodeRiwayat *headIncome, int *totalIncome);
void calcYearlyIncome(int startingYear, int currentYear, NodeRiwayat *headListRiwayat, int tampilkanRataRata, int tampilkanTahun,
                      int tampilkanBulan, int tahunYangDitampilkan, char **text);

//---------------------RIWAYAT PASIEN------------------------//
void informasiPasien(NodePasien *headListPasien, NodeRiwayat *headListRiwayat, char *id_pasien, char **text);

//---------------------PASIEN PERLU KONTROL------------------------//
void pasienPerluKontrol(char *currentDate, NodeRiwayat *headListRiwayat, NodePasien *headListPasien, char **text);

#endif