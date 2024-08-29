#ifndef PASIEN_H
#define PASIEN_H

#include "common.h"

typedef struct SearchResultPasien {
    NodePasien *current;
    NodePasien *previous;
} SearchResultPasien;

// Pasien application common function
void menuPasien(NodePasien **headListPasien);
void freeNodePasien(NodePasien *node);
void freeAllPasien(NodePasien **head);
void addNodePasien(NodePasien **head, Pasien *data);
SearchResultPasien searchNodePasien(NodePasien **headListPasien, char *inputBPJS, char **text);
void readPasien(NodePasien **headReadPasien, char *namaFile);
void savePasien(NodePasien **headDataPasien);
void outputPasien(NodePasien **headoutputPasien, char **text);

// Main funtion in Pasien application
void addPasien(NodePasien **headAddPasien, char *nama, char *alamat, char *kota, char *tempatLahir,
               char *tanggalLahir, char *usia, char *noBPJS, char *id, char **text);
void changePasien(SearchResultPasien result, char *nama, char *alamat, char *kota, char *tempatLahir,
                  char *tanggalLahir, char *usia, char *noBPJS, char *id, char **text);
void searchPasien(NodePasien **headSearchPasien, char *noBPJS, char **text);
void deletePasien(NodePasien **headdeletePasien, char *noBPJS, char **text);

#endif