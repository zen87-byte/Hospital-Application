#ifndef RIWAYAT_H
#define RIWAYAT_H

#include "common.h"

typedef struct{
    NodeRiwayat *current;
    NodeRiwayat *previous;
} SearchResultRiwayat;

// Riwayat application common function
void menuRiwayat(NodeRiwayat **headListRiwayat, Penyakit **listPenyakit, int *banyakPenyakit);
void freeNodeRiwayat(NodeRiwayat *node);
void freeAllRiwayat(NodeRiwayat **head);
void addNodeRiwayat(NodeRiwayat **head, Riwayat *data);
SearchResultRiwayat searchNodeRiwayat(NodeRiwayat **headListRiwayat, char *inputId, char *inputTanggal, char **text);
void readDataRiwayat(NodeRiwayat **headReadRiwayat, Penyakit **listPenyakit, int *banyakPenyakit, char *namaFile);
void saveDataRiwayat(NodeRiwayat **headDataRiwayat);
void outputRiwayat(NodeRiwayat **headOutputRiwayat, char **text);

// Main funtion in riwayat application
void addRiwayat(NodeRiwayat **headAddRiwayat, char *tanggal, char *id, char *diagnosis,
                char *tindakan, char *kontrol, char *biaya, char **text);
void changeRiwayat(SearchResultRiwayat result, char *tanggal, char *id, 
                   char *diagnosis, char *tindakan, char *kontrol, char *biaya, char **text);
void searchRiwayat(NodeRiwayat **headSearchRiwayat, char *tanggal, char *id, char **text);
void deleteRiwayat(NodeRiwayat **headDeleteRiwayat, char *tanggal, char *id, char **text);

#endif