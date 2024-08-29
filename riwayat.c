#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "riwayat.h"

#define MAX_SIZE 256
// format biaya
/*
void menuRiwayat(NodeRiwayat **headListRiwayat, Penyakit **listPenyakit, int *banyakPenyakit){
    readDataRiwayat(headListRiwayat, listPenyakit, banyakPenyakit);
    while(1){
        int riwayatChoice;
        printf("Menu aplikasi daftar riwayat pasien:\n1. Menambah daftar riwayat pasien\n2. Mengubah daftar riwayat pasien\n3. Mencari daftar riwayat pasien\n4. Menghapus daftar riwayat pasien\n5. Membaca daftar riwayat\n6. Keluar dari aplikasi riwayat\nMasukkan pilihan: ");
        scanf("%d", &riwayatChoice);
        if(riwayatChoice == 1){
            addRiwayat(headListRiwayat);
            saveDataRiwayat(headListRiwayat);
        }else if(riwayatChoice == 2){
            changeRiwayat(headListRiwayat);
        }else if(riwayatChoice == 3){
            searchRiwayat(headListRiwayat);
        }else if(riwayatChoice == 4){
            deleteRiwayat(headListRiwayat);
            saveDataRiwayat(headListRiwayat);
        }else if(riwayatChoice == 5){
            outputRiwayat(headListRiwayat);
        }else if(riwayatChoice == 6){
            saveDataRiwayat(headListRiwayat);
            freeAllRiwayat(headListRiwayat);
            break;
        }else{
            printf("Pilihan tidak ada! Masukkan input yang valid");
        }
    }
    
}
*/

void freeNodeRiwayat(NodeRiwayat *node) {
    if (node) {
        if (node->riwayat) {
            free(node->riwayat->tanggal);
            free(node->riwayat->diagnosis);
            free(node->riwayat->tindakan);
            free(node->riwayat->kontrol);
            free(node->riwayat);
        }
        free(node);
    }
}

void freeAllRiwayat(NodeRiwayat **head) {
    NodeRiwayat *current = *head;
    NodeRiwayat *next;

    while (current != NULL) {
        next = current->next;
        freeNodeRiwayat(current);
        current = next;
    }
    *head = NULL;
}

SearchResultRiwayat searchNodeRiwayat(NodeRiwayat **headListRiwayat, char *inputId, char *inputTanggal, char **text) {
    SearchResultRiwayat result = {NULL, NULL};
    char buffer[256];
    // Membaca id yang akan dihapus
    /*
    char inputId[20];
    char inputTanggal[20];
    printf("Masukkan id: ");
    scanf(" %[^\n]s", inputId);
    printf("Masukkan tanggal kedatangan pasien: ");
    scanf(" %[^\n]s", inputTanggal);
    */
    if (headListRiwayat == NULL || *headListRiwayat == NULL) {
        appendString(text, "Daftar Riwayat kosong!\n");
        //printf("Daftar riwayat kosong!\n");
        return result;
    }

    NodeRiwayat *current = *headListRiwayat;
    NodeRiwayat *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->riwayat->id, inputId) == 0 && strcmp(current->riwayat->tanggal, inputTanggal) == 0) {
            result.current = current;
            result.previous = previous;
            sprintf(buffer, "Riwayat pasien dengan ID %s di tanggal %s ditemukan!\n", inputId, inputTanggal);
            appendString(text, buffer);
            return result;
        }
        previous = current;
        current = current->next;
    }

    //printf("Id %s dengan tanggal %s tidak ditemukan!\n", inputId, inputTanggal);
    sprintf(buffer, "Riwayat pasien dengan ID %s di tanggal %s tidak ditemukan!\n", inputId, inputTanggal);
    appendString(text, buffer);
    return result;
}

void addNodeRiwayat(NodeRiwayat **head, Riwayat *data) {
    NodeRiwayat *newNode = (NodeRiwayat *)malloc(sizeof(NodeRiwayat));
    if (newNode == NULL) {
        perror("Gagal mengalokasikan memori untuk node riwayat");
        exit(EXIT_FAILURE);
    }

    newNode->riwayat = (Riwayat *)malloc(sizeof(Riwayat));
    if (newNode->riwayat == NULL) {
        perror("Gagal mengalokasikan memori untuk riwayat");
        free(newNode);
        exit(EXIT_FAILURE);
    }
    // Masukkan data tiap baris ke linked list
    newNode->riwayat->tanggal = strdup(data->tanggal);
    strcpy(newNode->riwayat->id, data->id);
    newNode->riwayat->diagnosis = strdup(data->diagnosis);
    newNode->riwayat->tindakan = strdup(data->tindakan);
    newNode->riwayat->kontrol = strdup(data->kontrol);
    newNode->riwayat->biaya = data->biaya;

    newNode->next = NULL;
    
    if (*head == NULL) {
        *head = newNode;
    } else {
        NodeRiwayat *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void readDataRiwayat(NodeRiwayat **headReadRiwayat, Penyakit **listPenyakit, int *banyakPenyakit, char *namaFile) {
    char buffer[MAX_SIZE];
    char *token;
    FILE *fileRiwayat = fopen(namaFile, "r");

    if (fileRiwayat == NULL) {
        perror("File tidak ditemukan");
        //sprintf(buffer, "Tidak ada file bernama %s\n", namaFile);
        //appendString(text, buffer);
        return;
    }

    fgets(buffer, MAX_SIZE, fileRiwayat); // Skip header

    while (fgets(buffer, MAX_SIZE, fileRiwayat) != NULL) {
        char tanggalTerformat[20] = "";
        char tanggalKontrolTerformat[20] = "";
        Riwayat *data = (Riwayat *)malloc(sizeof(Riwayat));

        if (data == NULL) {
            perror("Gagal mengalokasikan memori untuk riwayat");
            fclose(fileRiwayat);
            return;
        }

        data->tanggal = NULL;
        data->diagnosis = NULL;
        data->tindakan = NULL;
        data->kontrol = NULL;

        // Skip nomor / kolom pertama
        token = strtok(buffer, ",");

        // Copy tanggal
        token = strtok(NULL, ",");
        if (token) {
            ubahFormatTanggal(token, tanggalTerformat);
            data->tanggal = strdup(tanggalTerformat);
        }

        // Copy id
        token = strtok(NULL, ",");
        if (token) {
            strcpy(data->id, token);
        }

        // Copy diagnosis
        token = strtok(NULL, ",");
        if (token) {
            data->diagnosis = strdup(token);
            tambahPenyakit(data->diagnosis, banyakPenyakit, listPenyakit);
        }

        // Copy tindakan
        token = strtok(NULL, ",");
        if (token) {
            data->tindakan = strdup(token);
        }

        // Copy tanggal kontrol
        token = strtok(NULL, ",");
        if (token) {
            ubahFormatTanggal(token, tanggalKontrolTerformat);
            data->kontrol = strdup(tanggalKontrolTerformat);
        }

        // Copy biaya
        token = strtok(NULL, "\n");
        if (token) {
            data->biaya = ubahFormatBiaya(token);
        }

        addNodeRiwayat(headReadRiwayat, data);

        free(data->tanggal);
        free(data->diagnosis);
        free(data->tindakan);
        free(data->kontrol);
        free(data);
    }
    fclose(fileRiwayat);
    return;
}

void saveDataRiwayat(NodeRiwayat **headDataRiwayat){
    int count = 1;
    FILE *fileRiwayat = NULL; 
    fileRiwayat = fopen("riwayat.csv", "w");
    if (fileRiwayat){
        fprintf(fileRiwayat, "No,Tanggal,ID Pasien,Diagnosis,Tindakan,Kontrol,Biaya (Rp)\n");
        NodeRiwayat *currentNode = *headDataRiwayat;
        count = 1;
        while (currentNode != NULL){
            fprintf(fileRiwayat, "%d,%s,%s,%s,%s,%s,%d\n",
                count, currentNode->riwayat->tanggal, currentNode->riwayat->id, 
                currentNode->riwayat->diagnosis, currentNode->riwayat->tindakan, 
                currentNode->riwayat->kontrol, currentNode->riwayat->biaya);
            currentNode = currentNode->next;
            count += 1;
        }
        fclose(fileRiwayat);
    }
}

void outputRiwayat(NodeRiwayat **headOutputRiwayat, char **text){
    int count = 1;
    NodeRiwayat *current = *headOutputRiwayat;
    NodeRiwayat *next;
    char buffer[256];
    appendString(text, "===========================================================\n");
    //printf("===========================================================\n");
    while(current != NULL){
        //printf("%s %s %s %s %s %d\n", current->riwayat->tanggal, current->riwayat->id, current->riwayat->diagnosis,
        //       current->riwayat->tindakan, current->riwayat->kontrol, current->riwayat->biaya);
        sprintf(buffer, "%d, %s, %s, %s, %s, %s, %d\n", count, current->riwayat->tanggal, current->riwayat->id, current->riwayat->diagnosis,
               current->riwayat->tindakan, current->riwayat->kontrol, current->riwayat->biaya);
        appendString(text, buffer);
        next = current->next;
        current = next;
        count++;
    }
    appendString(text, "===========================================================\n");
    //printf("=============================================================\n");
}

void addRiwayat(NodeRiwayat **headAddRiwayat, char *tanggal, char *id, char *diagnosis,
                char *tindakan, char *kontrol, char *biaya, char **text){
        Riwayat *data = (Riwayat *)malloc(sizeof(Riwayat));

        if (data == NULL) {
            perror("Gagal mengalokasikan memori untuk riwayat");
            return;
        }

        char tanggalTerformat[20] = "";
        data->tanggal = NULL;
        data->diagnosis = NULL;
        data->tindakan = NULL;
        data->kontrol = NULL;

        //printf("=============== Tambahkan daftar riwayat penyakit pasien ===============\n");
        //printf("Masukkan tanggal kedatangan ke klinik: ");
        //scanf(" %[^\n]s", riwayat);


        ubahFormatTanggal(tanggal, tanggalTerformat);
        data->tanggal = strdup(tanggalTerformat);

        //printf("Masukkan id pasien: ");
        //scanf(" %[^\n]s", riwayat);

        strcpy(data->id, id);

        //printf("Masukkan diagnosis penyakit: ");
        //scanf(" %[^\n]s", riwayat);

        data->diagnosis = strdup(diagnosis);

        //printf("Masukkan tindakan yang dilakukan: ");
        //scanf(" %[^\n]s", riwayat);

        data->tindakan = strdup(tindakan);

        //printf("Masukkan tanggal kontrol kembali: ");
        //scanf(" %[^\n]s", riwayat);

        data->kontrol = strdup(kontrol);

        //printf("Masukkan biaya: ");
        //scanf(" %[^\n]s", riwayat);

        data->biaya = ubahFormatBiaya(biaya);

    addNodeRiwayat(headAddRiwayat, data);
    appendString(text, "Berhasil menambahkan riwayat\n");
}

void changeRiwayat(SearchResultRiwayat result, char *tanggal, char *id, 
                   char *diagnosis, char *tindakan, char *kontrol, char *biaya, char **text){
    /*
    SearchResultRiwayat result = searchNodeRiwayat(headChangeRiwayat);
    if(result.current == NULL){
        return;
    }
    */
    NodeRiwayat *nodeToChange = result.current;

    char change[20];
    char tanggalTerformat[20] = "";
    //printf("=============== Ubah riwayat penyakit pasien ===============\n");
    //printf("Masukkan tanggal kedatangan ke klinik: ");
    //scanf(" %[^\n]s", change);
    ubahFormatTanggal(tanggal, tanggalTerformat);
    nodeToChange->riwayat->tanggal = strdup(tanggalTerformat);

    //printf("Masukkan id pasien: ");
    //scanf(" %[^\n]s", change);
    strcpy(nodeToChange->riwayat->id, id);

    //printf("Masukkan diagnosis penyakit: ");
    //scanf(" %[^\n]s", change);
    nodeToChange->riwayat->diagnosis = strdup(diagnosis);

    //printf("Masukkan tindakan yang dilakukan: ");
    //scanf(" %[^\n]s", change);
    nodeToChange->riwayat->tindakan = strdup(tindakan);

    //printf("Masukkan tanggal kontrol kembali: ");
    //scanf(" %[^\n]s", change);
    nodeToChange->riwayat->kontrol = strdup(kontrol);

    //printf("Masukkan biaya: ");
    //scanf(" %[^\n]s", change);
    nodeToChange->riwayat->biaya = ubahFormatBiaya(biaya);

    //printf("Data riwayat berhasil diubah!\n");
    appendString(text, "Data riwayat berhasil diubah!\n");
}

void searchRiwayat(NodeRiwayat **headSearchRiwayat, char *tanggal, char *id, char **text){
    char buffer[256];
    //printf("===================== Cari Riwayat Pasien ====================");
    SearchResultRiwayat result = searchNodeRiwayat(headSearchRiwayat, id, tanggal, text);
    if(result.current == NULL){
        return;
    }
    NodeRiwayat *foundRiwayat = result.current;

    //printf("Hasil: %s, %s %s %s %s %d\n", foundRiwayat->riwayat->tanggal, foundRiwayat->riwayat->id, foundRiwayat->riwayat->diagnosis, foundRiwayat->riwayat->tindakan, foundRiwayat->riwayat->kontrol, foundRiwayat->riwayat->biaya);
    //appendString(text, "Ditemukan\n");
    appendString(text, "Tanggal, ID, Diagnosis, Tindakan, Kontrol, Biaya (Rp)\n");
    sprintf(buffer, "%s, %s, %s, %s, %s, %d\n", foundRiwayat->riwayat->tanggal, foundRiwayat->riwayat->id, foundRiwayat->riwayat->diagnosis, foundRiwayat->riwayat->tindakan, foundRiwayat->riwayat->kontrol, foundRiwayat->riwayat->biaya);
    appendString(text, buffer);
}

void deleteRiwayat(NodeRiwayat **headDeleteRiwayat, char *tanggal, char *id, char **text) {
    //printf("===================== Hapus Riwayat Pasien ====================");
    if (headDeleteRiwayat == NULL || *headDeleteRiwayat == NULL) {
        //printf("Daftar riwayat kosong!\n");
        appendString(text, "Daftar riwayat kosong!\n");
        return;
    }

    SearchResultRiwayat result = searchNodeRiwayat(headDeleteRiwayat, id, tanggal, text);
    if(result.current == NULL){
        return;
    }
    NodeRiwayat *nodeToDelete = result.current;
    NodeRiwayat *previousNode = result.previous;

    if (previousNode == NULL) {
        *headDeleteRiwayat = nodeToDelete->next;
    } else {
        previousNode->next = nodeToDelete->next;
    }

    freeNodeRiwayat(nodeToDelete);
    //printf("Id berhasil dihapus dari daftar riwayat\n");
    char buffer[256];
    sprintf(buffer, "Riwayat pasien dengan ID %s di tanggal %s berhasil dihapus\n", id, tanggal);
    appendString(text, buffer);
}
