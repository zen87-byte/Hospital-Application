#ifndef COMMON_H
#define COMMON_H

//DEFINISI STRUKTUR DATA
typedef struct{
    char *nama;
    char *alamat;
    char *kota;
    char *tempatLahir;
    char *tanggalLahir;
    int usia;
    char noBPJS[20];
    char id[20];
} Pasien;

typedef struct{
    char *tanggal;
    char id[20];
    char *diagnosis;
    char *tindakan;
    char *kontrol;
    int biaya;
} Riwayat;

typedef struct{
    char *tindakan;
    int biaya;
} Biaya;

typedef struct NodePasien{
    Pasien *pasien;
    struct NodePasien* next;
    struct NodePasien* prev;
} NodePasien;

typedef struct NodeRiwayat{
    Riwayat *riwayat;
    struct NodeRiwayat* next;
    struct NodeRiwayat* prev;
} NodeRiwayat;

typedef struct NodeBiaya{
    Biaya *biaya;
    struct NodeBiaya* next;
    struct NodeBiaya* prev;
} NodeBiaya;

typedef struct{
    char *nama;
} Penyakit;

typedef struct{
    char *nama;
    int jumlah;
} JumlahPerPenyakit;

//DEKLARASI FUNGSI
//FUNGSI UMUM

//Mendapatkan tanggal sekarang dalam format DD Month YYYY
void getCurrentDate(char *buffer, size_t bufferSize);

//Menambahkan string src ke dest
void appendString(char **dest, const char *src);

//Mengubah format "DD-MM-YY" menjadi "Hari Bulan Tahun"
void ubahFormatTanggal(char *tanggal, char *tanggalTerformat);

//Mengonversi nama bulan menjadi angka
int konversiBulan(char *bulan);

//Memparsing tanggal dengan format "Hari Bulan Tahun"
void parsingTanggal(char *tanggal, int *hari, char* bulan, int *tahun);

//Mengecek apakah tanggal 1 sesudah tanggal 2
int bandingkanTanggal(char *tanggal1, char *tanggal2);

//Mengubah format "XXX.XXX" menjadi "XXXXXX"
int ubahFormatBiaya(char *biayaStr);

//List biaya
void insertNodeBiaya(NodeBiaya **headListBiaya, NodeBiaya **tailListBiaya, char *tindakan, int biaya);
//void deleteNodeBiaya(NodeBiaya *biaya, NodeBiaya **headListBiaya, NodeBiaya **tailListBiaya);
void readBiaya(NodeBiaya **headListBiaya, NodeBiaya **tailListBiaya, char *namaFile);
void printBiaya(NodeBiaya *headListBiaya, char **text);
void bersihkanListBiaya(NodeBiaya **headListBiaya);
//void saveBiaya(NodeBiaya *headListBiaya);

//Pencarian
NodeBiaya* cariBiaya(NodeBiaya *startingBiaya, char *tindakan);
NodePasien* cariPasien(NodePasien* startingPasien, char *id_pasien); //Mencari pasien berdasarkan ID dimulai dari startingPasien

void tambahPenyakit(char *namaPenyakit, int *banyakPenyakit, Penyakit **listPenyakit);

#endif
