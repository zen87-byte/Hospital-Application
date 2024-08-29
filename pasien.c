#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pasien.h"

#define MAX_SIZE 1024

/*
void menuPasien(NodePasien **headListPasien){
    readPasien(headListPasien);
    while (1){
        int pasienChoice;
        printf("Menu aplikasi daftar Pasien pasien:\n1. Menambah daftar Pasien pasien\n2. Mengubah daftar Pasien pasien\n3. Mencari daftar Pasien pasien\n4. Menghapus daftar Pasien pasien\n5. Membaca daftar Pasien\n6. Keluar dari aplikasi Pasien\nMasukkan pilihan: ");
        scanf("%d", &pasienChoice);
        if(pasienChoice == 1){
            addPasien(headListPasien);
            savePasien(headListPasien);
        }else if(pasienChoice == 2){
            changePasien(headListPasien);
        }else if(pasienChoice == 3){
            searchPasien(headListPasien);
        }else if(pasienChoice == 4){
            deletePasien(headListPasien);
            savePasien(headListPasien);
        }else if(pasienChoice == 5){
            outputPasien(headListPasien);
        }else if(pasienChoice == 6){
            savePasien(headListPasien);
            freeAllPasien(headListPasien);
            break;
        }else{
            printf("Pilihan tidak ada! Masukkan input yang valid");
        }
    }
    
}
*/


void freeNodePasien(NodePasien *node) {
    if (node) {
        if (node->pasien) {
            free(node->pasien->nama);
            free(node->pasien->alamat);
            free(node->pasien->kota);
            free(node->pasien->tempatLahir);
            free(node->pasien->tanggalLahir);
            free(node->pasien);
        }
        free(node);
    }
}

void freeAllPasien(NodePasien **head) {
    NodePasien *current = *head;
    NodePasien *next;

    while (current != NULL) {
        next = current->next;
        freeNodePasien(current);
        current = next;
    }
    *head = NULL;
}

SearchResultPasien searchNodePasien(NodePasien **headListPasien, char *inputBPJS, char **text) {
    SearchResultPasien result = {NULL, NULL};
    char buffer[256];
    // Membaca id yang akan dihapus
    /*
    char inputBPJS[20];
    printf("Masukkan nomor BPJS: ");
    scanf(" %[^\n]s", inputBPJS);
    */
    if (headListPasien == NULL || *headListPasien == NULL) {
        //printf("Daftar Pasien kosong!\n");
        appendString(text, "Daftar Pasien kosong!\n");
        return result;
    }

    NodePasien *current = *headListPasien;
    NodePasien *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->pasien->noBPJS, inputBPJS) == 0) {
            result.current = current;
            result.previous = previous;
            sprintf(buffer, "Pasien dengan No. BPJS %s ditemukan!\n", inputBPJS);
            appendString(text, buffer);
            return result;
        }
        previous = current;
        current = current->next;
    }

    //printf("Nomor BPJS %s tidak ditemukan!\n", inputBPJS);
    sprintf(buffer, "Pasien dengan No. BPJS %s tidak ditemukan!\n", inputBPJS);
    appendString(text, buffer);

    return result;
}

void addNodePasien(NodePasien **head, Pasien *data) {
    NodePasien *newNode = (NodePasien *)malloc(sizeof(NodePasien));
    if (newNode == NULL) {
        perror("Gagal mengalokasikan memori untuk node Pasien");
        exit(EXIT_FAILURE);
    }

    newNode->pasien = (Pasien *)malloc(sizeof(Pasien));
    if (newNode->pasien == NULL) {
        perror("Gagal mengalokasikan memori untuk pasien");
        free(newNode);
        exit(EXIT_FAILURE);
    }
    // Masukkan data tiap baris ke linked list
    newNode->pasien->nama = strdup(data->nama);
    newNode->pasien->alamat = strdup(data->alamat);
    newNode->pasien->kota = strdup(data->kota);
    newNode->pasien->tempatLahir = strdup(data->tempatLahir);
    newNode->pasien->tanggalLahir = strdup(data->tanggalLahir);
    newNode->pasien->usia = data->usia;
    strcpy(newNode->pasien->noBPJS, data->noBPJS);
    strcpy(newNode->pasien->id, data->id);

    newNode->next = NULL;
    
    if (*head == NULL) {
        *head = newNode;
    } else {
        NodePasien *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void readPasien(NodePasien **headReadPasien, char *namaFile) {
    char buffer[MAX_SIZE];
    char *token;
    FILE *filePasien = fopen(namaFile, "r");
    if (filePasien == NULL) {
        perror("File tidak ditemukan");
        //sprintf(buffer, "Tidak ada file bernama %s\n", namaFile);
        //appendString(text, buffer);
        return;
    }

    fgets(buffer, MAX_SIZE, filePasien);  // Skip header line

    while (fgets(buffer, MAX_SIZE, filePasien) != NULL) {
        char tanggalTerformat[20] = "";
        Pasien *data = (Pasien *)malloc(sizeof(Pasien));

        if (data == NULL) {
            perror("Gagal mengalokasikan memori untuk pasien");
            fclose(filePasien);
            return;
        }

        data->nama = NULL;
        data->alamat = NULL;
        data->kota = NULL;
        data->tempatLahir = NULL;
        data->tanggalLahir = NULL;

        token = strtok(buffer, ",");

        token = strtok(NULL, ",");
        if (token) {
            data->nama = strdup(token);
        }
        token = strtok(NULL, ",");
        if (token) {
            data->alamat = strdup(token);
        }
        token = strtok(NULL, ",");
        if (token) {
            data->kota = strdup(token);
        }
        token = strtok(NULL, ",");
        if (token) {
            data->tempatLahir = strdup(token);
        }
        token = strtok(NULL, ",");
        if (token) {
            ubahFormatTanggal(token, tanggalTerformat);
            data->tanggalLahir = strdup(tanggalTerformat);
        }
        token = strtok(NULL, ",");
        if (token) {
            data->usia = atoi(token);
        }
        token = strtok(NULL, ",");
        if (token) {
            strcpy(data->noBPJS, token);
        }
        token = strtok(NULL, "\n");
        if (token) {
            strcpy(data->id, token);
        }
    
        addNodePasien(headReadPasien, data);

        free(data->nama);
        free(data->alamat);
        free(data->kota);
        free(data->tempatLahir);
        free(data->tanggalLahir);
        free(data);
    }
    fclose(filePasien);
    return;
}


void savePasien(NodePasien **headDataPasien) {
    int count = 1;
    FILE *filePasien = NULL;
    filePasien =  fopen("datapasien.csv", "w");
    if (filePasien) {
        fprintf(filePasien, "No,Nama,Alamat,Kota,Tempat Lahir,Tanggal Lahir,Usia,noBPJS,id\n");
        NodePasien *currentNode = *headDataPasien;
        while (currentNode != NULL) {
            fprintf(filePasien, "%d,%s,%s,%s,%s,%s,%d,%s,%s\n",
                    count,
                    currentNode->pasien->nama,
                    currentNode->pasien->alamat,
                    currentNode->pasien->kota,
                    currentNode->pasien->tempatLahir,
                    currentNode->pasien->tanggalLahir,
                    currentNode->pasien->usia,
                    currentNode->pasien->noBPJS,
                    currentNode->pasien->id);
            currentNode = currentNode->next;
            count++;
        }
        fclose(filePasien);
    }
}

void outputPasien(NodePasien **headoutputPasien, char **text) {
    int count = 1;
    NodePasien *current = *headoutputPasien;
    NodePasien *next;
    char buffer[256];
    appendString(text, "===========================================================\n");
    while (current != NULL) {
        /*
        printf("%d %s %s %s %s %s %d %s %s\n", count,
               current->pasien->nama, 
               current->pasien->alamat, 
               current->pasien->kota, 
               current->pasien->tempatLahir, 
               current->pasien->tanggalLahir, 
               current->pasien->usia, 
               current->pasien->noBPJS, 
               current->pasien->id);
        */
        sprintf(buffer, "%d, %s, %s, %s, %s, %s, %d, %s, %s\n", count,
               current->pasien->nama, 
               current->pasien->alamat, 
               current->pasien->kota, 
               current->pasien->tempatLahir, 
               current->pasien->tanggalLahir, 
               current->pasien->usia, 
               current->pasien->noBPJS, 
               current->pasien->id);
        appendString(text, buffer);
        next = current->next;
        current = next;
        count ++;
    }
    appendString(text, "===========================================================\n");
    //printf("===========================================================================================\n");
}


void addPasien(NodePasien **headAddPasien, char *nama, char *alamat, char *kota, char *tempatLahir,
               char *tanggalLahir, char *usia, char *noBPJS, char *id, char **text){
        Pasien *data = (Pasien *)malloc(sizeof(Pasien));
        
        if (data == NULL) {
            perror("Gagal mengalokasikan memori untuk Pasien");
            return;
        }

        char pasien[20];
        char tanggalTerformat[20] = "";

        data->nama = NULL;
        data->alamat = NULL;
        data->kota = NULL;
        data->tempatLahir = NULL;
        data->tanggalLahir = NULL;

        //printf("=============== Tambahkan daftar Pasien penyakit pasien ===============\n");
        //printf("Masukkan nama pasien: ");
        //scanf(" %[^\n]s", pasien);

        data->nama = strdup(nama);

        //printf("Masukkan alamat pasien: ");
        //scanf(" %[^\n]s", pasien);

        data->alamat = strdup(alamat);

        //printf("Masukkan kota pasien: ");
        //scanf(" %[^\n]s", pasien);

        data->kota = strdup(kota);

        //printf("Masukkan tempat lahir pasien: ");
        //scanf(" %[^\n]s", pasien);

        data->tempatLahir = strdup(tempatLahir);

        //printf("Masukkan tanggal lahir  pasien: ");
        //scanf(" %[^\n]s", pasien);

        ubahFormatTanggal(tanggalLahir, tanggalTerformat);
        data->tanggalLahir = strdup(tanggalTerformat);

        //printf("Masukkan usia pasien: ");
        //scanf(" %[^\n]s", pasien);

        data->usia = atoi(usia);

        //printf("Masukkan nomor BPJS pasien: ");
        //scanf(" %[^\n]s", pasien);

        strcpy(data->noBPJS, noBPJS);

        //printf("Masukkan id pasien: ");
        //scanf(" %[^\n]s", pasien);

        strcpy(data->id, id);

    addNodePasien(headAddPasien, data);
    appendString(text, "Berhasil menambahkan pasien\n");
}

void changePasien(SearchResultPasien result, char *nama, char *alamat, char *kota, char *tempatLahir,
                  char *tanggalLahir, char *usia, char *noBPJS, char *id, char **text){
    /*
    SearchResultPasien result = searchNodePasien(headChangePasien);
    if(result.current == NULL){
        return;
    }
    */
    char buffer[256];
    NodePasien *nodeToChange = result.current;

    char change[20];
    char tanggalTerformat[20] = "";
    //printf("=============== Ubah Pasien penyakit pasien ===============\n");
    //appendString(text, "=============== Ubah Pasien penyakit pasien ===============\n")

    //printf("Masukkan nama pasien: ");
    //scanf(" %[^\n]s", change);
    strcpy(nodeToChange->pasien->nama, nama);

    //printf("Masukkan alamat pasien: ");
    //scanf(" %[^\n]s", change);
    strcpy(nodeToChange->pasien->alamat, alamat);

    //printf("Masukkan kota pasien: ");
    //scanf(" %[^\n]s", change);
    strcpy(nodeToChange->pasien->kota, kota);

    //printf("Masukkan tempat lahir pasien: ");
    //scanf(" %[^\n]s", change);
    strcpy(nodeToChange->pasien->tempatLahir, tempatLahir);

    //printf("Masukkan tanggal lahir pasien: ");
    //scanf(" %[^\n]s", change);
    ubahFormatTanggal(tanggalLahir, tanggalTerformat);
    nodeToChange->pasien->tanggalLahir = strdup(tanggalTerformat);

    //printf("Masukkan usia pasien: ");
    //scanf(" %[^\n]s", change);
    nodeToChange->pasien->usia = atoi(usia);

    //printf("Masukkan nomor BPJS pasien: ");
    //scanf(" %[^\n]s", change);
    strcpy(nodeToChange->pasien->noBPJS, noBPJS);

    //printf("Masukkan id pasien: ");
    //scanf(" %[^\n]s", change);
    strcpy(nodeToChange->pasien->id, id);

    appendString(text, "Data Pasien berhasil diubah!\n");
    //printf("Data Pasien berhasil diubah!\n");
}

void searchPasien(NodePasien **headSearchPasien, char *noBPJS, char **text){
    char buffer[256];
    //printf("===================== Cari Pasien ====================");
    SearchResultPasien result = searchNodePasien(headSearchPasien, noBPJS, text);
    if(result.current == NULL){
        return;
    }
    NodePasien *foundPasien = result.current;

    //printf("%s %s %s %s %s %d %s %s\n", foundPasien->pasien->nama, foundPasien->pasien->alamat, foundPasien->pasien->kota, foundPasien->pasien->tempatLahir, foundPasien->pasien->tanggalLahir, foundPasien->pasien->usia, foundPasien->pasien->noBPJS, foundPasien->pasien->id);
    appendString(text, "\n");
    appendString(text, "Nama, Alamat, Kota, Tempat Lahir, Tanggal Lahir, Usia (tahun), No BPJS, ID\n");
    sprintf(buffer, "%s, %s, %s, %s, %s, %d, %s, %s,\n", foundPasien->pasien->nama, foundPasien->pasien->alamat, foundPasien->pasien->kota, foundPasien->pasien->tempatLahir, foundPasien->pasien->tanggalLahir, foundPasien->pasien->usia, foundPasien->pasien->noBPJS, foundPasien->pasien->id);
    appendString(text, buffer);
}

void deletePasien(NodePasien **headdeletePasien, char *noBPJS, char **text) {
    //printf("===================== Hapus Pasien Pasien ====================\n");
    if (headdeletePasien == NULL || *headdeletePasien == NULL) {
        //printf("Daftar Pasien kosong!\n");
        appendString(text, "Daftar Pasien kosong!\n");
        return;
    }

    SearchResultPasien result = searchNodePasien(headdeletePasien, noBPJS, text);
    if(result.current == NULL){
        return;
    }
    NodePasien *nodeToDelete = result.current;
    NodePasien *previousNode = result.previous;

    if (previousNode == NULL) {
        *headdeletePasien = nodeToDelete->next;
    } else {
        previousNode->next = nodeToDelete->next;
    }

    freeNodePasien(nodeToDelete);

    //printf("Id berhasil dihapus dari daftar Pasien\n");
    char buffer[256];
    sprintf(buffer, "Pasien dengan No. BPJS %s berhasil dihapus dari daftar pasien\n", noBPJS);
    appendString(text, buffer);
}
