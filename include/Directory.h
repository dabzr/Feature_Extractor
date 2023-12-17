#include <dirent.h>
#include "Image.h"

enum FileType{
  TXT,
  CSV,
};

void startCSV(FILE *csv, int matrixFactor);
void startDataset(const char *path, int*max); 
int countItemsinDirectory(const char* path);
void fileErrorHandling(FILE*fp);
FILE *fileHandling(enum FileType type, int filterFactor, int value);
void print_progress(size_t count, size_t max);
void readDataset(const char* path, int FilterFactor, int *values, int qtd, int qtd_imagens); // Função que lê o dataset e aplica filtro
int imageFiltering(struct pgm* originalImage, struct pgm* filteredImage, const char* path, const char* fileName, int filterFactor);
