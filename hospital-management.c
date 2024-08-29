#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
//  #include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>
#include "common.h"
#include "pasien.h"
#include "riwayat.h"
#include "informasi.h"

GtkWidget *window;
GtkWidget *windowFixed;
GtkWidget *menuBar;
//File
GtkWidget *importMenuItem;
GtkWidget *saveMenuItem;
GtkWidget *quit;
//Pasien
GtkWidget *tambahPasienMenuItem;
GtkWidget *ubahPasienMenuItem;
GtkWidget *hapusPasienMenuItem;
GtkWidget *cariPasienMenuItem;
//Riwayat
GtkWidget *tambahRiwayatMenuItem;
GtkWidget *ubahRiwayatMenuItem;
GtkWidget *hapusRiwayatMenuItem;
GtkWidget *cariRiwayatMenuItem;
//Informasi
GtkWidget *informasiPasienMenuItem;
GtkWidget *informasiPendapatanMenuItem;
GtkWidget *informasiJumlahPasienMenuItem;
GtkWidget *informasiJumlahPenyakitMenuItem;
GtkWidget *informasiKontrolMenuItem;
//Stack Main
GtkWidget *stackMain;
//Stack Menu
GtkWidget *stackMenu;
GtkWidget *namaMenu;
GtkWidget *warnaNamaMenu;
//Stack Menu Besar
GtkWidget *stackMenuBesar;
GtkWidget *textMenuBesar;
//Stack Menu Kecil
GtkWidget *stackMenuKecil;
GtkWidget *textMenuKecil;
//Menu Tambah Pasien
GtkWidget *entryTambahNamaPasien;
GtkWidget *entryTambahAlamatPasien;
GtkWidget *entryTambahKotaPasien;
GtkWidget *entryTambahTempatLahirPasien;
GtkWidget *entryTambahTanggalLahirPasien;
GtkWidget *entryTambahUsiaPasien;
GtkWidget *entryTambahNoBPJSPasien;
GtkWidget *entryTambahIDPasien;
GtkWidget *tombolTambahPasien;
//Menu Ubah Pasien
GtkWidget *entryUbahNamaPasien;
GtkWidget *entryUbahAlamatPasien;
GtkWidget *entryUbahKotaPasien;
GtkWidget *entryUbahTempatLahirPasien;
GtkWidget *entryUbahTanggalLahirPasien;
GtkWidget *entryUbahUsiaPasien;
GtkWidget *entryUbahNoBPJSPasien;
GtkWidget *entryUbahIDPasien;
GtkWidget *tombolCariUbahPasien;
GtkWidget *tombolUbahPasien;
//Menu Tambah Riwayat
GtkWidget *entryTambahTanggalRiwayat;
GtkWidget *entryTambahIDRiwayat;
GtkWidget *entryTambahDiagnosisRiwayat;
GtkWidget *entryTambahTindakanRiwayat;
GtkWidget *entryTambahKontrolRiwayat;
//GtkWidget *entryTambahBiayaRiwayat;
GtkWidget *tombolTambahRiwayat;
//Menu Ubah Riwayat
GtkWidget *entryUbahTanggalRiwayat;
GtkWidget *entryUbahIDRiwayat;
GtkWidget *entryUbahDiagnosisRiwayat;
GtkWidget *entryUbahTindakanRiwayat;
GtkWidget *entryUbahKontrolRiwayat;
//GtkWidget *entryUbahBiayaRiwayat;
GtkWidget *tombolCariUbahRiwayat;
GtkWidget *tombolUbahRiwayat;
//Menu Import File
GtkWidget *entryFilePasien;
GtkWidget *entryFileRiwayat;
GtkWidget *entryFileBiaya;
GtkWidget *tombolMuatFilePasien;
GtkWidget *tombolMuatFileRiwayat;
GtkWidget *tombolMuatFileBiaya;
//Menu Informasi Jumlah Pasien
GtkWidget *tampilkanPasienPertahunButton;
GtkWidget *tampilkanPasienPerbulanButton;
GtkWidget *tampilkanPasienKeduanyaButton;
GtkWidget *urutkanPasienPertahunButton;
GtkWidget *urutkanPasienPerbulanButton;
GtkWidget *entryTahunPasienPerbulan;
GtkWidget *hasilkanInformasiJumlahPasienButton;
//Menu Informasi Jumlah Penyakit
GtkWidget *tampilkanPenyakitPertahunButton;
GtkWidget *tampilkanPenyakitPerbulanButton;
GtkWidget *tampilkanPenyakitKeduanyaButton;
GtkWidget *urutkanPenyakitPertahunButton;
GtkWidget *urutkanPenyakitPerbulanButton;
GtkWidget *entryTahunPenyakitPerbulan;
GtkWidget *hasilkanInformasiJumlahPenyakitButton;
//Menu Cari Riwayat
GtkWidget *entryCariIDRiwayat;
GtkWidget *entryCariTanggalRiwayat;
GtkWidget *cariRiwayatButton;
//Menu Hapus Riwayat
GtkWidget *entryHapusIDRiwayat;
GtkWidget *entryHapusTanggalRiwayat;
GtkWidget *hapusRiwayatButton;
//Menu Cari Pasien
GtkWidget *entryCariNoBPJSPasien;
GtkWidget *cariPasienButton;
//Menu Hapus Pasien
GtkWidget *entryHapusNoBPJSPasien;
GtkWidget *hapusPasienButton;
//Menu Informasi Pasien
GtkWidget *entryInformasiIDPasien;
GtkWidget *hasilkanInformasiRiwayatPasienButton;
//Menu Informasi Pendapatan
GtkWidget *tampilkanPendapatanPertahunButton;
GtkWidget *tampilkanPendapatanPerbulanButton;
GtkWidget *tampilkanPendapatanKeduanyaButton;
GtkWidget *tampilkanPendapatanRatarataButton;
GtkWidget *entryTahunPendapatanPerbulan;
GtkWidget *hasilkanInformasiPendapatanButton;
//Menu Informasi Kontrol
GtkWidget *hasilkanInformasiKontrolButton;

int tahunAktif = 2022;
int banyakPasien = 0;
int banyakRiwayat = 0;
int banyakBiaya = 0;
int banyakPenyakit = 0;
Penyakit *listPenyakit = NULL;
NodePasien *headListPasien = NULL;
NodeRiwayat *headListRiwayat = NULL;
NodeBiaya *headListBiaya = NULL;
NodeBiaya *tailListBiaya = NULL;
SearchResultPasien resultPasien = {NULL, NULL};
SearchResultRiwayat resultRiwayat = {NULL, NULL};
char namaFilePasien[256] = "datapasien.csv";
char namaFileRiwayat[256] = "riwayat.csv";
char namaFileBiaya[256] = "biaya.csv";

GtkTextBuffer *textBuffer;

GtkBuilder *builder;


//=========================IMPORT MENU============================//

void on_importMenuItem_activate(GtkMenuItem *m){
    gtk_stack_set_visible_child_name(GTK_STACK(stackMain), "menus");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenu), "menuKecil");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenuKecil), "menuImport");
    gtk_label_set_text(GTK_LABEL(namaMenu), "IMPORT FILE");
    gtk_text_buffer_set_text(textBuffer, "Tempatkan file csv di folder yang sama dengan aplikasi\nMasukkan nama file csv\n", -1);
}

void on_tombolMuatFilePasien_clicked(GtkButton *b){
    char newNamaFile[256];
    char *buffer = NULL;
    FILE *file = NULL;

    sprintf(newNamaFile, "%s", gtk_entry_get_text(GTK_ENTRY(entryFilePasien)));
    file = fopen(newNamaFile, "r");

    if(file){
        fclose(file);
        strcpy(namaFilePasien, newNamaFile);
        freeAllPasien(&headListPasien);
        readPasien(&headListPasien, namaFilePasien);
        outputPasien(&headListPasien, &buffer);
        gtk_text_buffer_set_text(textBuffer, buffer, -1);
    }
    else{
        char error[256];
        sprintf(error, "Tidak ada file bernama %s\n", newNamaFile);
        gtk_text_buffer_set_text(textBuffer, error, -1); 
    }
    free(buffer);
}

void on_tombolMuatFileRiwayat_clicked(GtkButton *b){
    char newNamaFile[256];
    char *buffer = NULL;
    FILE *file = NULL;

    sprintf(newNamaFile, "%s", gtk_entry_get_text(GTK_ENTRY(entryFileRiwayat)));
    file = fopen(newNamaFile, "r");

    if(file){
        fclose(file);
        strcpy(namaFileRiwayat, newNamaFile);
        freeAllRiwayat(&headListRiwayat);
        readDataRiwayat(&headListRiwayat, &listPenyakit, &banyakPenyakit, namaFileRiwayat);
        outputRiwayat(&headListRiwayat, &buffer);
        gtk_text_buffer_set_text(textBuffer, buffer, -1);
    }
    else{
        char error[256];
        sprintf(error, "Tidak ada file bernama %s\n", newNamaFile);
        gtk_text_buffer_set_text(textBuffer, error, -1);
    }
    free(buffer);
}

void on_tombolMuatFileBiaya_clicked(GtkButton *b){
    char newNamaFile[256];
    char *buffer = NULL;
    FILE *file = NULL;

    sprintf(newNamaFile, "%s", gtk_entry_get_text(GTK_ENTRY(entryFileBiaya)));
    file = fopen(newNamaFile, "r");
    
    if(file){
        fclose(file);
        strcpy(namaFileBiaya, newNamaFile);
        bersihkanListBiaya(&headListBiaya);
        readBiaya(&headListBiaya, &tailListBiaya, namaFileBiaya);
        printBiaya(headListBiaya, &buffer);
        gtk_text_buffer_set_text(textBuffer, buffer, -1);
    }
    else{
        char error[256];
        sprintf(error, "Tidak ada file bernama %s\n", newNamaFile);
        gtk_text_buffer_set_text(textBuffer, error, -1);
    }
    free(buffer);
}

//======================MENU SAVE=========================//
void on_saveMenuItem_activate(GtkMenuItem *m){
    savePasien(&headListPasien);
    saveDataRiwayat(&headListRiwayat);
}

//======================MENU QUIT=======================//
void on_quit_activate(GtkMenuItem *m){
    freeAllPasien(&headListPasien);
    freeAllRiwayat(&headListRiwayat);
    bersihkanListBiaya(&headListBiaya);
    gtk_main_quit();
}

//=======================MENU TAMBAH PASIEN======================//
void on_tambahPasienMenuItem_activate(GtkMenuItem *m){
    gtk_stack_set_visible_child_name(GTK_STACK(stackMain), "menus");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenu), "menuBesar");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenuBesar), "menuTambahPasien");
    gtk_label_set_text(GTK_LABEL(namaMenu), "TAMBAH PASIEN");
    gtk_text_buffer_set_text(textBuffer, "Lengkapi data pasien yang ingin ditambahkan\n", -1);
}

void on_tombolTambahPasien_clicked(GtkButton *b){
    char nama[20], alamat[20], kota[20], tempatLahir[20], tanggalLahir[20], usia[20], noBPJS[20], id[20];
    char *buffer = NULL;
    sprintf(nama, "%s", gtk_entry_get_text(GTK_ENTRY(entryTambahNamaPasien)));
    sprintf(alamat, "%s", gtk_entry_get_text(GTK_ENTRY(entryTambahAlamatPasien)));
    sprintf(kota, "%s", gtk_entry_get_text(GTK_ENTRY(entryTambahKotaPasien)));
    sprintf(tempatLahir, "%s", gtk_entry_get_text(GTK_ENTRY(entryTambahTempatLahirPasien)));
    sprintf(tanggalLahir, "%s", gtk_entry_get_text(GTK_ENTRY(entryTambahTanggalLahirPasien)));
    sprintf(usia, "%s", gtk_entry_get_text(GTK_ENTRY(entryTambahUsiaPasien)));
    sprintf(noBPJS, "%s", gtk_entry_get_text(GTK_ENTRY(entryTambahNoBPJSPasien)));
    sprintf(id, "%s", gtk_entry_get_text(GTK_ENTRY(entryTambahIDPasien)));
    addPasien(&headListPasien, nama, alamat, kota, tempatLahir, tanggalLahir, usia, noBPJS, id, &buffer);
    savePasien(&headListPasien);
    gtk_text_buffer_set_text(textBuffer, buffer, -1);
    free(buffer);
}

//======================MENU UBAH PASIEN=======================//
void on_ubahPasienMenuItem_activate(GtkMenuItem *m){
    gtk_stack_set_visible_child_name(GTK_STACK(stackMain), "menus");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenu), "menuBesar");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenuBesar), "menuUbahPasien");
    gtk_label_set_text(GTK_LABEL(namaMenu), "UBAH PASIEN");
    gtk_text_buffer_set_text(textBuffer, "Masukkan no. BPJS dari pasien yang ingin diubah\n", -1);

    gtk_widget_set_sensitive(entryUbahNamaPasien, FALSE);
    gtk_widget_set_sensitive(entryUbahAlamatPasien, FALSE);
    gtk_widget_set_sensitive(entryUbahKotaPasien, FALSE);
    gtk_widget_set_sensitive(entryUbahTempatLahirPasien, FALSE);
    gtk_widget_set_sensitive(entryUbahTanggalLahirPasien, FALSE);
    gtk_widget_set_sensitive(entryUbahUsiaPasien, FALSE);
    gtk_widget_set_sensitive(entryUbahIDPasien, FALSE);
    gtk_widget_set_sensitive(tombolUbahPasien, FALSE);
}

void on_tombolCariUbahPasien_clicked(GtkButton *b){
    char noBPJS[20];
    char *buffer = NULL;
    resultPasien.current = NULL;
    resultPasien.previous = NULL;
	sprintf(noBPJS, "%s", gtk_entry_get_text(GTK_ENTRY(entryUbahNoBPJSPasien)));
    resultPasien = searchNodePasien(&headListPasien, noBPJS, &buffer);
    if(resultPasien.current){
        gtk_widget_set_sensitive(entryUbahNamaPasien, TRUE);
        gtk_widget_set_sensitive(entryUbahAlamatPasien, TRUE);
        gtk_widget_set_sensitive(entryUbahKotaPasien, TRUE);
        gtk_widget_set_sensitive(entryUbahTempatLahirPasien, TRUE);
        gtk_widget_set_sensitive(entryUbahTanggalLahirPasien, TRUE);
        gtk_widget_set_sensitive(entryUbahUsiaPasien, TRUE);
        gtk_widget_set_sensitive(entryUbahIDPasien, TRUE);
        gtk_widget_set_sensitive(tombolUbahPasien, TRUE);
    }
    else{
        gtk_widget_set_sensitive(entryUbahNamaPasien, FALSE);
        gtk_widget_set_sensitive(entryUbahAlamatPasien, FALSE);
        gtk_widget_set_sensitive(entryUbahKotaPasien, FALSE);
        gtk_widget_set_sensitive(entryUbahTempatLahirPasien, FALSE);
        gtk_widget_set_sensitive(entryUbahTanggalLahirPasien, FALSE);
        gtk_widget_set_sensitive(entryUbahUsiaPasien, FALSE);
        gtk_widget_set_sensitive(entryUbahIDPasien, FALSE);
        gtk_widget_set_sensitive(tombolUbahPasien, FALSE);
    }
    gtk_text_buffer_set_text(textBuffer, buffer, -1);
    free(buffer);
}

void on_tombolUbahPasien_clicked(GtkButton *b){
    char nama[20], alamat[20], kota[20], tempatLahir[20], tanggalLahir[20], usia[20], noBPJS[20], id[20];
    char *buffer = NULL;
    sprintf(nama, "%s", gtk_entry_get_text(GTK_ENTRY(entryUbahNamaPasien)));
    sprintf(alamat, "%s", gtk_entry_get_text(GTK_ENTRY(entryUbahAlamatPasien)));
    sprintf(kota, "%s", gtk_entry_get_text(GTK_ENTRY(entryUbahKotaPasien)));
    sprintf(tempatLahir, "%s", gtk_entry_get_text(GTK_ENTRY(entryUbahTempatLahirPasien)));
    sprintf(tanggalLahir, "%s", gtk_entry_get_text(GTK_ENTRY(entryUbahTanggalLahirPasien)));
    sprintf(usia, "%s", gtk_entry_get_text(GTK_ENTRY(entryUbahUsiaPasien)));
    sprintf(noBPJS, "%s", gtk_entry_get_text(GTK_ENTRY(entryUbahNoBPJSPasien)));
    sprintf(id, "%s", gtk_entry_get_text(GTK_ENTRY(entryUbahIDPasien)));

    if(resultPasien.current){
        changePasien(resultPasien, nama, alamat, kota, tempatLahir, tanggalLahir, usia, noBPJS, id, &buffer);
        gtk_text_buffer_set_text(textBuffer, buffer, -1);
        free(buffer);
        gtk_widget_set_sensitive(entryUbahNamaPasien, FALSE);
        gtk_widget_set_sensitive(entryUbahAlamatPasien, FALSE);
        gtk_widget_set_sensitive(entryUbahKotaPasien, FALSE);
        gtk_widget_set_sensitive(entryUbahTempatLahirPasien, FALSE);
        gtk_widget_set_sensitive(entryUbahTanggalLahirPasien, FALSE);
        gtk_widget_set_sensitive(entryUbahUsiaPasien, FALSE);
        gtk_widget_set_sensitive(entryUbahIDPasien, FALSE);
        gtk_widget_set_sensitive(tombolUbahPasien, FALSE);
        savePasien(&headListPasien);
        GtkTextIter iter;
        gtk_text_buffer_get_end_iter(textBuffer, &iter);
        gtk_text_buffer_insert(textBuffer, &iter, "\nMasukkan lagi no. BPJS dari pasien yang ingin diubah\n", -1);
    }
}

//======================MENU HAPUS PASIEN=======================//
void on_hapusPasienMenuItem_activate(GtkMenuItem *m){
    gtk_stack_set_visible_child_name(GTK_STACK(stackMain), "menus");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenu), "menuKecil");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenuKecil), "menuHapusPasien");
    gtk_label_set_text(GTK_LABEL(namaMenu), "HAPUS PASIEN");
    gtk_text_buffer_set_text(textBuffer, "Masukkan no. BPJS dari pasien yang ingin dihapus\n", -1);
}

void on_hapusPasienButton_clicked(GtkButton *b){
    char noBPJS[20];
    char *buffer = NULL;
    
	sprintf(noBPJS, "%s", gtk_entry_get_text(GTK_ENTRY(entryHapusNoBPJSPasien)));
    deletePasien(&headListPasien, noBPJS, &buffer);
    savePasien(&headListPasien);
    gtk_text_buffer_set_text(textBuffer, buffer, -1);
    free(buffer);
}

//======================MENU CARI PASIEN======================//
void on_cariPasienMenuItem_activate(GtkMenuItem *m){
    gtk_stack_set_visible_child_name(GTK_STACK(stackMain), "menus");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenu), "menuKecil");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenuKecil), "menuCariPasien");
    gtk_label_set_text(GTK_LABEL(namaMenu), "CARI PASIEN");
    gtk_text_buffer_set_text(textBuffer, "Masukkan no. BPJS dari pasien yang ingin dicari\n", -1);
}

void on_cariPasienButton_clicked(GtkButton *b){
    char noBPJS[20];
    char *buffer = NULL;
    
	sprintf(noBPJS, "%s", gtk_entry_get_text(GTK_ENTRY(entryCariNoBPJSPasien)));
    searchPasien(&headListPasien, noBPJS, &buffer);

    gtk_text_buffer_set_text(textBuffer, buffer, -1);
    free(buffer);
}

//====================MENU TAMBAH RIWAYAT=======================//
void on_tambahRiwayatMenuItem_activate(GtkMenuItem *m){
    gtk_stack_set_visible_child_name(GTK_STACK(stackMain), "menus");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenu), "menuBesar");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenuBesar), "menuTambahRiwayat");
    gtk_label_set_text(GTK_LABEL(namaMenu), "TAMBAH RIWAYAT");
    gtk_text_buffer_set_text(textBuffer, "Lengkapi data riwayat yang ingin ditambahkan\n", -1);
}

void on_tombolTambahRiwayat_clicked(GtkButton *b){
    char tanggal[20], id[20], diagnosis[20], tindakan[20], kontrol[20], biaya[20];
    char *buffer = NULL;
    sprintf(tanggal, "%s", gtk_entry_get_text(GTK_ENTRY(entryTambahTanggalRiwayat)));
    sprintf(id, "%s", gtk_entry_get_text(GTK_ENTRY(entryTambahIDRiwayat)));
    sprintf(diagnosis, "%s", gtk_entry_get_text(GTK_ENTRY(entryTambahDiagnosisRiwayat)));
    sprintf(tindakan, "%s", gtk_entry_get_text(GTK_ENTRY(entryTambahTindakanRiwayat)));
    sprintf(kontrol, "%s", gtk_entry_get_text(GTK_ENTRY(entryTambahKontrolRiwayat)));

    NodeBiaya *currentNode = cariBiaya(headListBiaya, tindakan);
    if(currentNode){
        sprintf(biaya, "%d", currentNode->biaya->biaya);
        addRiwayat(&headListRiwayat, tanggal, id, diagnosis, tindakan, kontrol, biaya, &buffer);
        saveDataRiwayat(&headListRiwayat);
        gtk_text_buffer_set_text(textBuffer, buffer, -1);
        free(buffer);
    }
    else{
        gtk_text_buffer_set_text(textBuffer, "Tindakan tidak terdaftar\nCek lagi nama tindakan atau tambahkan tindakan di file biaya\n", -1);
    }
}

//=======================MENU UBAH RIWAYAT======================//
void on_ubahRiwayatMenuItem_activate(GtkMenuItem *m){
    gtk_stack_set_visible_child_name(GTK_STACK(stackMain), "menus");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenu), "menuBesar");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenuBesar), "menuUbahRiwayat");
    gtk_label_set_text(GTK_LABEL(namaMenu), "UBAH RIWAYAT");
    gtk_text_buffer_set_text(textBuffer, "Masukkan ID pasien dan tanggal kedatangan dari riwayat yang ingin diubah\n", -1);
    gtk_widget_set_sensitive(entryUbahDiagnosisRiwayat, FALSE);
    gtk_widget_set_sensitive(entryUbahTindakanRiwayat, FALSE);
    gtk_widget_set_sensitive(entryUbahKontrolRiwayat, FALSE);
    //gtk_widget_set_sensitive(entryUbahBiayaRiwayat, FALSE);
    gtk_widget_set_sensitive(tombolUbahRiwayat, FALSE);
}

void on_tombolCariUbahRiwayat_clicked(GtkButton *b){
    char tanggal[20], id[20];
    char *buffer = NULL;
    resultRiwayat.current = NULL;
    resultRiwayat.previous = NULL;
	sprintf(tanggal, "%s", gtk_entry_get_text(GTK_ENTRY(entryUbahTanggalRiwayat)));
    sprintf(id, "%s", gtk_entry_get_text(GTK_ENTRY(entryUbahIDRiwayat)));
    resultRiwayat = searchNodeRiwayat(&headListRiwayat, id, tanggal, &buffer);
    if(resultRiwayat.current){
        gtk_widget_set_sensitive(entryUbahDiagnosisRiwayat, TRUE);
        gtk_widget_set_sensitive(entryUbahTindakanRiwayat, TRUE);
        gtk_widget_set_sensitive(entryUbahKontrolRiwayat, TRUE);
        //gtk_widget_set_sensitive(entryUbahBiayaRiwayat, TRUE);
        gtk_widget_set_sensitive(tombolUbahRiwayat, TRUE);
    }
    else{
        gtk_widget_set_sensitive(entryUbahDiagnosisRiwayat, FALSE);
        gtk_widget_set_sensitive(entryUbahTindakanRiwayat, FALSE);
        gtk_widget_set_sensitive(entryUbahKontrolRiwayat, FALSE);
        //gtk_widget_set_sensitive(entryUbahBiayaRiwayat, FALSE);
        gtk_widget_set_sensitive(tombolUbahRiwayat, FALSE);
    }
    gtk_text_buffer_set_text(textBuffer, buffer, -1);
    free(buffer);
}

void on_tombolUbahRiwayat_clicked(GtkButton *b){
    char tanggal[20], id[20], diagnosis[20], tindakan[20], kontrol[20], biaya[20];
    char *buffer = NULL;
    sprintf(tanggal, "%s", gtk_entry_get_text(GTK_ENTRY(entryUbahTanggalRiwayat)));
    sprintf(id, "%s", gtk_entry_get_text(GTK_ENTRY(entryUbahIDRiwayat)));
    sprintf(diagnosis, "%s", gtk_entry_get_text(GTK_ENTRY(entryUbahDiagnosisRiwayat)));
    sprintf(tindakan, "%s", gtk_entry_get_text(GTK_ENTRY(entryUbahTindakanRiwayat)));
    sprintf(kontrol, "%s", gtk_entry_get_text(GTK_ENTRY(entryUbahKontrolRiwayat)));
    //sprintf(biaya, "%s", gtk_entry_get_text(GTK_ENTRY(entryUbahBiayaRiwayat)));
    NodeBiaya *currentNode = cariBiaya(headListBiaya, tindakan);

    if(currentNode){
        sprintf(biaya, "%d", currentNode->biaya->biaya);
        if(resultRiwayat.current){
            changeRiwayat(resultRiwayat, tanggal, id, diagnosis, tindakan, kontrol, biaya, &buffer);
            gtk_text_buffer_set_text(textBuffer, buffer, -1);
            free(buffer);
            gtk_widget_set_sensitive(entryUbahDiagnosisRiwayat, FALSE);
            gtk_widget_set_sensitive(entryUbahTindakanRiwayat, FALSE);
            gtk_widget_set_sensitive(entryUbahKontrolRiwayat, FALSE);
            //gtk_widget_set_sensitive(entryUbahBiayaRiwayat, FALSE);
            gtk_widget_set_sensitive(tombolUbahRiwayat, FALSE);
            saveDataRiwayat(&headListRiwayat);
            GtkTextIter iter;
            gtk_text_buffer_get_end_iter(textBuffer, &iter);
            gtk_text_buffer_insert(textBuffer, &iter, "Masukkan lagi ID pasien dan tanggal kedatangannya dari riwayat yang ingin dihapus\n", -1);
        }
    }
    else{
        gtk_text_buffer_set_text(textBuffer, "Tindakan tidak terdaftar\nCek lagi nama tindakan atau tambahkan tindakan di file biaya\n", -1);
    }
}

//==================MENU HAPUS RIWAYAT=====================//
void on_hapusRiwayatMenuItem_activate(GtkMenuItem *m){
    gtk_stack_set_visible_child_name(GTK_STACK(stackMain), "menus");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenu), "menuKecil");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenuKecil), "menuHapusRiwayat");
    gtk_label_set_text(GTK_LABEL(namaMenu), "HAPUS RIWAYAT");
    gtk_text_buffer_set_text(textBuffer, "Masukkan ID dan tanggal kedatangan pasien yang ingin dihapus riwayatnya\n", -1);
}

void on_hapusRiwayatButton_clicked(GtkButton *b){
    char id[20];
    char tanggal[20];
    char *buffer = NULL;
	sprintf(id, "%s", gtk_entry_get_text(GTK_ENTRY(entryHapusIDRiwayat)));
    sprintf(tanggal, "%s", gtk_entry_get_text(GTK_ENTRY(entryHapusTanggalRiwayat)));
    deleteRiwayat(&headListRiwayat, tanggal, id, &buffer);
    saveDataRiwayat(&headListRiwayat);
    gtk_text_buffer_set_text(textBuffer, buffer, -1);
    free(buffer);
}

//====================MENU CARI RIWAYAT===================
void on_cariRiwayatMenuItem_activate(GtkMenuItem *m){
    gtk_stack_set_visible_child_name(GTK_STACK(stackMain), "menus");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenu), "menuKecil");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenuKecil), "menuCariRiwayat");
    gtk_label_set_text(GTK_LABEL(namaMenu), "CARI RIWAYAT");
    gtk_text_buffer_set_text(textBuffer, "Masukkan ID dan tanggal kedatangan pasien yang ingin dicari riwayatnya\n", -1);
}

void on_cariRiwayatButton_clicked(GtkButton *b){
    char id[20];
    char tanggal[20];
    char *buffer = NULL;

	sprintf(id, "%s", gtk_entry_get_text(GTK_ENTRY(entryCariIDRiwayat)));
    sprintf(tanggal, "%s", gtk_entry_get_text(GTK_ENTRY(entryCariTanggalRiwayat)));

    searchRiwayat(&headListRiwayat, tanggal, id, &buffer);
    gtk_text_buffer_set_text(textBuffer, buffer, -1);
    free(buffer);
}

//==================MENU INFORMASI RIWAYAT PASIEN==================
void on_informasiPasienMenuItem_activate(GtkMenuItem *m){
    gtk_stack_set_visible_child_name(GTK_STACK(stackMain), "menus");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenu), "menuKecil");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenuKecil), "menuInformasiRiwayatPasien");
    gtk_label_set_text(GTK_LABEL(namaMenu), "INFORMASI RIWAYAT PASIEN");
    gtk_text_buffer_set_text(textBuffer, "Masukkan ID dari pasien yang ingin diketahui riwayatnya\n", -1);
}

void on_hasilkanInformasiRiwayatPasienButton_clicked(GtkButton *b){
    char id[20];
    char *buffer = NULL;
    gtk_text_buffer_set_text(textBuffer, "Masukkan ID pasien yang ingin diketahui riwayatnya\n", -1);
    sprintf(id, "%s", gtk_entry_get_text(GTK_ENTRY(entryInformasiIDPasien)));
    informasiPasien(headListPasien, headListRiwayat, id, &buffer);
    gtk_text_buffer_set_text(textBuffer, buffer, -1);
    free(buffer);
}

//===============MENU INFORMASI PENDAPATAN=================//
void on_informasiPendapatanMenuItem_activate(GtkMenuItem *m){
    gtk_stack_set_visible_child_name(GTK_STACK(stackMain), "menus");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenu), "menuKecil");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenuKecil), "menuInformasiPendapatan");
    gtk_label_set_text(GTK_LABEL(namaMenu), "INFORMASI PENDAPATAN");
    gtk_widget_set_sensitive(entryTahunPendapatanPerbulan, FALSE);
    gtk_text_buffer_set_text(textBuffer, "Tentukan opsi\n", -1);
}

void on_tampilkanPendapatanPerbulanButton_toggled(GtkToggleButton *t){
    int active = gtk_toggle_button_get_active(t);
    if (active) {
        gtk_widget_set_sensitive(entryTahunPendapatanPerbulan, TRUE);
    } else {
        gtk_widget_set_sensitive(entryTahunPendapatanPerbulan, FALSE);
    }
}

void on_hasilkanInformasiPendapatanButton_clicked(GtkButton *b){
    int tampilkanBulan = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tampilkanPendapatanPerbulanButton));
    int tampilkanTahun = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tampilkanPendapatanPertahunButton));
    int tampilkanKeduanya = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tampilkanPendapatanKeduanyaButton));
    int tampilkanRatarata = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tampilkanPendapatanRatarataButton));

    char tahunYangDitampilkan[20];
    char currentDate[25];
    getCurrentDate(currentDate, 25);
    int currentHari;
    char currentBulan[20];
    int currentTahun;

    parsingTanggal(currentDate, &currentHari, currentBulan, &currentTahun);

    sprintf(tahunYangDitampilkan, "%s", gtk_entry_get_text(GTK_ENTRY(entryTahunPendapatanPerbulan)));

    if(strcmp(tahunYangDitampilkan, "") == 0){
        if(tampilkanBulan){
            gtk_text_buffer_set_text(textBuffer, "Masukkan tahun yang ingin ditampilkan\n", -1);
            return;
        }
    }

    if(tampilkanKeduanya){
        tampilkanBulan = 1;
        tampilkanTahun = 1;
    }
    char *buffer = NULL;

    calcYearlyIncome(tahunAktif, currentTahun, headListRiwayat, tampilkanRatarata, tampilkanTahun,
                     tampilkanBulan, atoi(tahunYangDitampilkan), &buffer);
    gtk_text_buffer_set_text(textBuffer, buffer, -1);
    free(buffer);
}


//=================MENU INFORMASI JUMLAH PASIEN====================//
void on_informasiJumlahPasienMenuItem_activate(GtkMenuItem *m){
    gtk_stack_set_visible_child_name(GTK_STACK(stackMain), "menus");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenu), "menuKecil");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenuKecil), "menuInformasiJumlahPasien");
    gtk_label_set_text(GTK_LABEL(namaMenu), "INFORMASI JUMLAH PASIEN");
    gtk_widget_set_sensitive(entryTahunPasienPerbulan, FALSE);
    gtk_text_buffer_set_text(textBuffer, "Tentukan opsi\n", -1);
}

void on_tampilkanPasienPerbulanButton_toggled(GtkToggleButton *t){
    int active = gtk_toggle_button_get_active(t);
    if (active) {
        gtk_widget_set_sensitive(entryTahunPasienPerbulan, TRUE);
    } else {
        gtk_widget_set_sensitive(entryTahunPasienPerbulan, FALSE);
    }
}

void on_hasilkanInformasiJumlahPasienButton_clicked(GtkButton *b){

    int tampilkanBulan = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tampilkanPasienPerbulanButton));
    int tampilkanTahun = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tampilkanPasienPertahunButton));
    int tampilkanKeduanya = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tampilkanPasienKeduanyaButton));
    int urutkanTahun = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(urutkanPasienPertahunButton));
    int urutkanBulan = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(urutkanPasienPerbulanButton));

    char tahunYangDitampilkan[20];
    char currentDate[25];
    getCurrentDate(currentDate, 25);
    int currentHari;
    char currentBulan[20];
    int currentTahun;

    parsingTanggal(currentDate, &currentHari, currentBulan, &currentTahun);

    sprintf(tahunYangDitampilkan, "%s", gtk_entry_get_text(GTK_ENTRY(entryTahunPasienPerbulan)));

    if(strcmp(tahunYangDitampilkan, "") == 0){
        if(tampilkanBulan){
            gtk_text_buffer_set_text(textBuffer, "Masukkan tahun yang ingin ditampilkan\n", -1);
            return;
        }
    }

    if(tampilkanKeduanya){
        tampilkanBulan = 1;
        tampilkanTahun = 1;
    }
    char *buffer = NULL;

    laporanJumlahPasien(tahunAktif, currentTahun, headListRiwayat, tampilkanTahun, tampilkanBulan,
                                atoi(tahunYangDitampilkan), urutkanTahun, urutkanBulan, &buffer);

    gtk_text_buffer_set_text(textBuffer, buffer, -1);
    free(buffer);
}

//=============MENU INFORMASI JUMLAH PENYAKIT================//
void on_informasiJumlahPenyakitMenuItem_activate(GtkMenuItem *m){
    gtk_stack_set_visible_child_name(GTK_STACK(stackMain), "menus");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenu), "menuKecil");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenuKecil), "menuInformasiJumlahPenyakit");
    gtk_label_set_text(GTK_LABEL(namaMenu), "INFORMASI JUMLAH PENYAKIT");
    gtk_widget_set_sensitive(entryTahunPenyakitPerbulan, FALSE);
    gtk_text_buffer_set_text(textBuffer, "Tentukan opsi\n", -1);
}

void on_tampilkanPenyakitPerbulanButton_toggled(GtkToggleButton *t){
    int active = gtk_toggle_button_get_active(t);
    if (active) {
        gtk_widget_set_sensitive(entryTahunPenyakitPerbulan, TRUE);
    } else {
        gtk_widget_set_sensitive(entryTahunPenyakitPerbulan, FALSE);
    }
}

void on_hasilkanInformasiJumlahPenyakitButton_clicked(GtkButton *b){
    int tampilkanBulan = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tampilkanPenyakitPerbulanButton));
    int tampilkanTahun = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tampilkanPenyakitPertahunButton));
    int tampilkanKeduanya = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(tampilkanPenyakitKeduanyaButton));
    int urutkanTahun = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(urutkanPenyakitPertahunButton));
    int urutkanBulan = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(urutkanPenyakitPerbulanButton));

    char tahunYangDitampilkan[20];
    char currentDate[25];
    getCurrentDate(currentDate, 25);
    int currentHari;
    char currentBulan[20];
    int currentTahun;

    parsingTanggal(currentDate, &currentHari, currentBulan, &currentTahun);

    sprintf(tahunYangDitampilkan, "%s", gtk_entry_get_text(GTK_ENTRY(entryTahunPenyakitPerbulan)));
    
    if(strcmp(tahunYangDitampilkan, "") == 0){
        if(tampilkanBulan){
            gtk_text_buffer_set_text(textBuffer, "Masukkan tahun yang ingin ditampilkan\n", -1);
            return;
        }
    }

    if(tampilkanKeduanya){
        tampilkanBulan = 1;
        tampilkanTahun = 1;
    }
    char *buffer = NULL;
    laporanJumlahPenyakit(tahunAktif, currentTahun, banyakPenyakit, headListRiwayat, listPenyakit, tampilkanTahun,
                                  tampilkanBulan, atoi(tahunYangDitampilkan), urutkanTahun, urutkanBulan, &buffer);

    gtk_text_buffer_set_text(textBuffer, buffer, -1);
    free(buffer);
}

//==========MENU INFORMASI PASIEN PERLU KONTROL==================///
void on_informasiKontrolMenuItem_activate(GtkMenuItem *m){
    gtk_stack_set_visible_child_name(GTK_STACK(stackMain), "menus");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenu), "menuKecil");
    gtk_stack_set_visible_child_name(GTK_STACK(stackMenuKecil), "menuInformasiKontrol");
    gtk_label_set_text(GTK_LABEL(namaMenu), "INFORMASI KONTROL PASIEN");
    gtk_text_buffer_set_text(textBuffer, "Tekan Tombol Hasilkan\n", -1);
}

void on_hasilkanInformasiKontrolButton_clicked(GtkButton *b){
    char *buffer = NULL;
    char currentDate[20];
    getCurrentDate(currentDate, 20);
    pasienPerluKontrol(currentDate, headListRiwayat, headListPasien, &buffer);
    gtk_text_buffer_set_text(textBuffer, buffer, -1);
    free(buffer);
}

//===============INISIALISASI OBJEK================//
void initialize(){
    builder = gtk_builder_new_from_file("gui.glade");
 
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title(GTK_WINDOW(window), "Manajemen Rumah Sakit");

    windowFixed = GTK_WIDGET(gtk_builder_get_object(builder, "windowFixed"));
    menuBar = GTK_WIDGET(gtk_builder_get_object(builder, "menuBar"));
    //---------------------MENU ITEM----------------------//
    importMenuItem = GTK_WIDGET(gtk_builder_get_object(builder, "importMenuItem"));
    g_signal_connect(importMenuItem, "activate", G_CALLBACK(on_importMenuItem_activate), NULL);
    
    saveMenuItem = GTK_WIDGET(gtk_builder_get_object(builder, "saveMenuItem"));
    g_signal_connect(saveMenuItem, "activate", G_CALLBACK(on_saveMenuItem_activate), NULL);

    quit = GTK_WIDGET(gtk_builder_get_object(builder, "quit"));
    g_signal_connect(quit, "activate", G_CALLBACK(on_quit_activate), NULL);

    tambahPasienMenuItem = GTK_WIDGET(gtk_builder_get_object(builder, "tambahPasienMenuItem"));
    g_signal_connect(tambahPasienMenuItem, "activate", G_CALLBACK(on_tambahPasienMenuItem_activate), NULL);

    ubahPasienMenuItem = GTK_WIDGET(gtk_builder_get_object(builder, "ubahPasienMenuItem"));
    g_signal_connect(ubahPasienMenuItem, "activate", G_CALLBACK(on_ubahPasienMenuItem_activate), NULL);

    hapusPasienMenuItem = GTK_WIDGET(gtk_builder_get_object(builder, "hapusPasienMenuItem"));
    g_signal_connect(hapusPasienMenuItem, "activate", G_CALLBACK(on_hapusPasienMenuItem_activate), NULL);

    cariPasienMenuItem = GTK_WIDGET(gtk_builder_get_object(builder, "cariPasienMenuItem"));
    g_signal_connect(cariPasienMenuItem, "activate", G_CALLBACK(on_cariPasienMenuItem_activate), NULL);

    tambahRiwayatMenuItem = GTK_WIDGET(gtk_builder_get_object(builder, "tambahRiwayatMenuItem"));
    g_signal_connect(tambahRiwayatMenuItem, "activate", G_CALLBACK(on_tambahRiwayatMenuItem_activate), NULL);

    ubahRiwayatMenuItem = GTK_WIDGET(gtk_builder_get_object(builder, "ubahRiwayatMenuItem"));
    g_signal_connect(ubahRiwayatMenuItem, "activate", G_CALLBACK(on_ubahRiwayatMenuItem_activate), NULL);

    hapusRiwayatMenuItem = GTK_WIDGET(gtk_builder_get_object(builder, "hapusRiwayatMenuItem"));
    g_signal_connect(hapusRiwayatMenuItem, "activate", G_CALLBACK(on_hapusRiwayatMenuItem_activate), NULL);

    cariRiwayatMenuItem = GTK_WIDGET(gtk_builder_get_object(builder, "cariRiwayatMenuItem"));
    g_signal_connect(cariRiwayatMenuItem, "activate", G_CALLBACK(on_cariRiwayatMenuItem_activate), NULL);

    informasiPasienMenuItem = GTK_WIDGET(gtk_builder_get_object(builder, "informasiPasienMenuItem"));
    g_signal_connect(informasiPasienMenuItem, "activate", G_CALLBACK(on_informasiPasienMenuItem_activate), NULL);

    informasiPendapatanMenuItem = GTK_WIDGET(gtk_builder_get_object(builder, "informasiPendapatanMenuItem"));
    g_signal_connect(informasiPendapatanMenuItem, "activate", G_CALLBACK(on_informasiPendapatanMenuItem_activate), NULL);

    informasiJumlahPasienMenuItem = GTK_WIDGET(gtk_builder_get_object(builder, "informasiJumlahPasienMenuItem"));
    g_signal_connect(informasiJumlahPasienMenuItem, "activate", G_CALLBACK(on_informasiJumlahPasienMenuItem_activate), NULL);

    informasiJumlahPenyakitMenuItem = GTK_WIDGET(gtk_builder_get_object(builder, "informasiJumlahPenyakitMenuItem"));
    g_signal_connect(informasiJumlahPenyakitMenuItem, "activate", G_CALLBACK(on_informasiJumlahPenyakitMenuItem_activate), NULL);

    informasiKontrolMenuItem = GTK_WIDGET(gtk_builder_get_object(builder, "informasiKontrolMenuItem"));
    g_signal_connect(informasiKontrolMenuItem, "activate", G_CALLBACK(on_informasiKontrolMenuItem_activate), NULL);

    stackMain = GTK_WIDGET(gtk_builder_get_object(builder, "stackMain"));

    stackMenu = GTK_WIDGET(gtk_builder_get_object(builder, "stackMenu"));
    namaMenu = GTK_WIDGET(gtk_builder_get_object(builder, "namaMenu"));

    stackMenuBesar = GTK_WIDGET(gtk_builder_get_object(builder, "stackMenuBesar"));
    textMenuBesar = GTK_WIDGET(gtk_builder_get_object(builder, "textMenuBesar"));

    stackMenuKecil = GTK_WIDGET(gtk_builder_get_object(builder, "stackMenuKecil"));
    textMenuKecil = GTK_WIDGET(gtk_builder_get_object(builder, "textMenuKecil"));

    textMenuKecil = GTK_WIDGET(gtk_builder_get_object(builder, "textMenuKecil"));

    entryTambahNamaPasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryTambahNamaPasien"));
    entryTambahAlamatPasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryTambahAlamatPasien"));
    entryTambahKotaPasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryTambahKotaPasien"));
    entryTambahTempatLahirPasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryTambahTempatLahirPasien"));
    entryTambahTanggalLahirPasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryTambahTanggalLahirPasien"));
    entryTambahUsiaPasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryTambahUsiaPasien"));
    entryTambahNoBPJSPasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryTambahNoBPJSPasien"));
    entryTambahIDPasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryTambahIDPasien"));
    tombolTambahPasien = GTK_WIDGET(gtk_builder_get_object(builder, "tombolTambahPasien"));
    g_signal_connect(tombolTambahPasien, "clicked", G_CALLBACK(on_tombolTambahPasien_clicked), NULL);

    entryUbahNamaPasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryUbahNamaPasien"));
    entryUbahAlamatPasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryUbahAlamatPasien"));
    entryUbahKotaPasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryUbahKotaPasien"));
    entryUbahTempatLahirPasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryUbahTempatLahirPasien"));
    entryUbahTanggalLahirPasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryUbahTanggalLahirPasien"));
    entryUbahUsiaPasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryUbahUsiaPasien"));
    entryUbahNoBPJSPasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryUbahNoBPJSPasien"));
    entryUbahIDPasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryUbahIDPasien"));
    tombolCariUbahPasien = GTK_WIDGET(gtk_builder_get_object(builder, "tombolCariUbahPasien"));
    g_signal_connect(tombolCariUbahPasien, "clicked", G_CALLBACK(on_tombolCariUbahPasien_clicked), NULL);
    tombolUbahPasien = GTK_WIDGET(gtk_builder_get_object(builder, "tombolUbahPasien"));
    g_signal_connect(tombolUbahPasien, "clicked", G_CALLBACK(on_tombolUbahPasien_clicked), NULL);

    entryTambahTanggalRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "entryTambahTanggalRiwayat"));
    entryTambahIDRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "entryTambahIDRiwayat"));
    entryTambahDiagnosisRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "entryTambahDiagnosisRiwayat"));
    entryTambahTindakanRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "entryTambahTindakanRiwayat"));
    entryTambahKontrolRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "entryTambahKontrolRiwayat"));
    //entryTambahBiayaRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "entryTambahBiayaRiwayat"));
    tombolTambahRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "tombolTambahRiwayat"));
    g_signal_connect(tombolTambahRiwayat, "clicked", G_CALLBACK(on_tombolTambahRiwayat_clicked), NULL);

    entryUbahTanggalRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "entryUbahTanggalRiwayat"));
    entryUbahIDRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "entryUbahIDRiwayat"));
    entryUbahDiagnosisRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "entryUbahDiagnosisRiwayat"));
    entryUbahTindakanRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "entryUbahTindakanRiwayat"));
    entryUbahKontrolRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "entryUbahKontrolRiwayat"));
    //entryUbahBiayaRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "entryUbahBiayaRiwayat"));
    tombolCariUbahRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "tombolCariUbahRiwayat"));
    g_signal_connect(tombolCariUbahRiwayat, "clicked", G_CALLBACK(on_tombolCariUbahRiwayat_clicked), NULL);
    tombolUbahRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "tombolUbahRiwayat"));
    g_signal_connect(tombolUbahRiwayat, "clicked", G_CALLBACK(on_tombolUbahRiwayat_clicked), NULL);

    entryFilePasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryFilePasien"));
    entryFileRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "entryFileRiwayat"));
    entryFileBiaya = GTK_WIDGET(gtk_builder_get_object(builder, "entryFileBiaya"));
    tombolMuatFilePasien = GTK_WIDGET(gtk_builder_get_object(builder, "tombolMuatFilePasien"));
    g_signal_connect(tombolMuatFilePasien, "clicked", G_CALLBACK(on_tombolMuatFilePasien_clicked), NULL);
    tombolMuatFileRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "tombolMuatFileRiwayat"));
    g_signal_connect(tombolMuatFileRiwayat, "clicked", G_CALLBACK(on_tombolMuatFileRiwayat_clicked), NULL);
    tombolMuatFileBiaya = GTK_WIDGET(gtk_builder_get_object(builder, "tombolMuatFileBiaya"));
    g_signal_connect(tombolMuatFileBiaya, "clicked", G_CALLBACK(on_tombolMuatFileBiaya_clicked), NULL);

    tampilkanPasienPertahunButton = GTK_WIDGET(gtk_builder_get_object(builder, "tampilkanPasienPertahunButton"));
    tampilkanPasienPerbulanButton = GTK_WIDGET(gtk_builder_get_object(builder, "tampilkanPasienPerbulanButton"));
    g_signal_connect(tampilkanPasienPerbulanButton, "toggled", G_CALLBACK(on_tampilkanPasienPerbulanButton_toggled), NULL);
    tampilkanPasienKeduanyaButton = GTK_WIDGET(gtk_builder_get_object(builder, "tampilkanPasienKeduanyaButton"));
    urutkanPasienPertahunButton = GTK_WIDGET(gtk_builder_get_object(builder, "urutkanPasienPertahunButton"));
    urutkanPasienPerbulanButton = GTK_WIDGET(gtk_builder_get_object(builder, "urutkanPasienPerbulanButton"));
    entryTahunPasienPerbulan = GTK_WIDGET(gtk_builder_get_object(builder, "entryTahunPasienPerbulan"));
    hasilkanInformasiJumlahPasienButton = GTK_WIDGET(gtk_builder_get_object(builder, "hasilkanInformasiJumlahPasienButton"));
    g_signal_connect(hasilkanInformasiJumlahPasienButton, "clicked", G_CALLBACK(on_hasilkanInformasiJumlahPasienButton_clicked), NULL);

    tampilkanPenyakitPertahunButton = GTK_WIDGET(gtk_builder_get_object(builder, "tampilkanPenyakitPertahunButton"));
    tampilkanPenyakitPerbulanButton = GTK_WIDGET(gtk_builder_get_object(builder, "tampilkanPenyakitPerbulanButton"));
    g_signal_connect(tampilkanPenyakitPerbulanButton, "toggled", G_CALLBACK(on_tampilkanPenyakitPerbulanButton_toggled), NULL);
    tampilkanPenyakitKeduanyaButton = GTK_WIDGET(gtk_builder_get_object(builder, "tampilkanPenyakitKeduanyaButton"));
    urutkanPenyakitPertahunButton = GTK_WIDGET(gtk_builder_get_object(builder, "urutkanPenyakitPertahunButton"));
    urutkanPenyakitPerbulanButton = GTK_WIDGET(gtk_builder_get_object(builder, "urutkanPenyakitPerbulanButton"));
    entryTahunPenyakitPerbulan = GTK_WIDGET(gtk_builder_get_object(builder, "entryTahunPenyakitPerbulan"));
    hasilkanInformasiJumlahPenyakitButton = GTK_WIDGET(gtk_builder_get_object(builder, "hasilkanInformasiJumlahPenyakitButton"));
    g_signal_connect(hasilkanInformasiJumlahPenyakitButton, "clicked", G_CALLBACK(on_hasilkanInformasiJumlahPenyakitButton_clicked), NULL);

    entryCariIDRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "entryCariIDRiwayat"));
    entryCariTanggalRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "entryCariTanggalRiwayat"));
    cariRiwayatButton = GTK_WIDGET(gtk_builder_get_object(builder, "cariRiwayatButton"));
    g_signal_connect(cariRiwayatButton, "clicked", G_CALLBACK(on_cariRiwayatButton_clicked), NULL);

    entryHapusIDRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "entryHapusIDRiwayat"));
    entryHapusTanggalRiwayat = GTK_WIDGET(gtk_builder_get_object(builder, "entryHapusTanggalRiwayat"));
    hapusRiwayatButton = GTK_WIDGET(gtk_builder_get_object(builder, "hapusRiwayatButton"));
    g_signal_connect(hapusRiwayatButton, "clicked", G_CALLBACK(on_hapusRiwayatButton_clicked), NULL);

    entryCariNoBPJSPasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryCariNoBPJSPasien"));
    cariPasienButton = GTK_WIDGET(gtk_builder_get_object(builder, "cariPasienButton"));
    g_signal_connect(cariPasienButton, "clicked", G_CALLBACK(on_cariPasienButton_clicked), NULL);

    entryHapusNoBPJSPasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryHapusNoBPJSPasien"));
    hapusPasienButton = GTK_WIDGET(gtk_builder_get_object(builder, "hapusPasienButton"));
    g_signal_connect(hapusPasienButton, "clicked", G_CALLBACK(on_hapusPasienButton_clicked), NULL);

    entryInformasiIDPasien = GTK_WIDGET(gtk_builder_get_object(builder, "entryInformasiIDPasien"));
    hasilkanInformasiRiwayatPasienButton = GTK_WIDGET(gtk_builder_get_object(builder, "hasilkanInformasiRiwayatPasienButton"));
    g_signal_connect(hasilkanInformasiRiwayatPasienButton, "clicked", G_CALLBACK(on_hasilkanInformasiRiwayatPasienButton_clicked), NULL);

    tampilkanPendapatanPertahunButton = GTK_WIDGET(gtk_builder_get_object(builder, "tampilkanPendapatanPertahunButton"));
    tampilkanPendapatanPerbulanButton = GTK_WIDGET(gtk_builder_get_object(builder, "tampilkanPendapatanPerbulanButton"));
    g_signal_connect(tampilkanPendapatanPerbulanButton, "toggled", G_CALLBACK(on_tampilkanPendapatanPerbulanButton_toggled), NULL);
    tampilkanPendapatanKeduanyaButton = GTK_WIDGET(gtk_builder_get_object(builder, "tampilkanPendapatanKeduanyaButton"));
    tampilkanPendapatanRatarataButton = GTK_WIDGET(gtk_builder_get_object(builder, "tampilkanPendapatanRatarataButton"));
    entryTahunPendapatanPerbulan = GTK_WIDGET(gtk_builder_get_object(builder, "entryTahunPendapatanPerbulan"));
    hasilkanInformasiPendapatanButton = GTK_WIDGET(gtk_builder_get_object(builder, "hasilkanInformasiPendapatanButton"));
    g_signal_connect(hasilkanInformasiPendapatanButton, "clicked", G_CALLBACK(on_hasilkanInformasiPendapatanButton_clicked), NULL);

    hasilkanInformasiKontrolButton = GTK_WIDGET(gtk_builder_get_object(builder, "hasilkanInformasiKontrolButton"));
    g_signal_connect(hasilkanInformasiKontrolButton, "clicked", G_CALLBACK(on_hasilkanInformasiKontrolButton_clicked), NULL);

    textBuffer = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "textBuffer"));
}

void css_set(GtkCssProvider * cssProvider, GtkWidget *g_widget) {
    GtkStyleContext *context = gtk_widget_get_style_context(g_widget);
    gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(cssProvider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    }

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    initialize();

    readDataRiwayat(&headListRiwayat, &listPenyakit, &banyakPenyakit, namaFileRiwayat);
    readPasien(&headListPasien, namaFilePasien);
    readBiaya(&headListBiaya, &tailListBiaya, namaFileBiaya);
    
    gtk_stack_set_visible_child_name(GTK_STACK(stackMain), "home");

    GtkCssProvider  *cssProvider1;
    cssProvider1  = gtk_css_provider_new();

    gtk_css_provider_load_from_path(cssProvider1, "gtk.css", NULL);
    
    css_set(cssProvider1, window);
    css_set(cssProvider1, tombolCariUbahPasien);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(cssProvider1),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);

    GError *error = NULL;
    GtkIconTheme *icon_theme;

    icon_theme = gtk_icon_theme_new();

    char **path;
    gint ele;

    gtk_icon_theme_get_search_path (icon_theme, &path, &ele);

    gtk_icon_theme_set_custom_theme (icon_theme, "GNOME");
    gtk_icon_theme_set_screen (icon_theme, gdk_screen_get_default());

    // Show all widgets
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}