#include "../include/Image.h"
#include "../include/Filter.h"
#include "../include/SCM.h"
#include "../include/Directory.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define SAVE_FILTERED_IMAGE 1 
#define MAX_BUFFER_SIZE 300

void readDataset(const char *path, int filterFactor, int* values, int qtd, int qtd_imagens){

  FILE* csvs[qtd];
  for (int i = 0; i < qtd; i++){
    csvs[i] = fileHandling(CSV, filterFactor, values[i]);
    startCSV(csvs[i], values[i]);
  }
  int count = 0;
  DIR *d;
  struct dirent *dir;
  d = opendir(path);
  if(!d){
    perror("ERRO");
    exit(errno);
  }
  while ((dir = readdir(d)) != NULL) {
    if (dir->d_type != DT_REG) continue;
    struct pgm imagem, filtrada;
    if(!imageFiltering(&imagem, &filtrada, path, dir->d_name, filterFactor)) continue;
    SCMHandling(imagem, filtrada, values, qtd, dir->d_name, csvs);
    free(imagem.data);
    free(filtrada.data); 
    print_progress(++count, qtd_imagens);
  }
  closedir(d); 
  for (int i = 0; i < qtd; i++)
    fclose(csvs[i]);
}
void startCSV(FILE *csv, int matrixFactor){
  for(int j = 0; j < (matrixFactor * matrixFactor); j++){
    fprintf(csv, "%d,", j);
  }
  fprintf(csv, "%d",(matrixFactor * matrixFactor));
  fprintf(csv, "\n");
}
FILE *fileHandling(enum FileType type, int filterFactor, int value){
  char fileName[MAX_BUFFER_SIZE];
  FILE *file;
  switch (type){
    case TXT:
      file = fopen("./csv/Imagens.txt", "w");
      fileErrorHandling(file);
      break;
    case CSV:
      sprintf(fileName, "./csv/Image_%dx%d_%d.csv", filterFactor, filterFactor, value); 
      file = fopen(fileName, "w");
      fileErrorHandling(file);
      break;
  }
  return file;
}


void fileErrorHandling(FILE*fp){
  if(!fp){
    perror("ERRO");
    exit(errno);
  }
}

int imageFiltering(struct pgm* originalImage, struct pgm* filteredImage, const char* path, const char* fileName, int filterFactor){
  char imagePath[MAX_BUFFER_SIZE];
  sprintf(imagePath, "%s/%s", path, fileName);
  if(!readPGMImage(originalImage, imagePath)) return 0;
  *(filteredImage) = filterAverage(*originalImage, filterFactor);
  #if SAVE_FILTERED_IMAGE != 0 
    sprintf(imagePath, "./filtered/%dx%d/%s", filterFactor, filterFactor, fileName); 
    writePGMImage(filteredImage, imagePath); 
  #endif
  return 1;
} 

void startDataset(const char *path, int*max){ 
  FILE* txt = fileHandling(TXT, 0, 0);
  DIR* d;
  struct dirent *dir;
  d = opendir(path);
  *max = 0;
  while ((dir = readdir(d)) != NULL) {  
    if (dir->d_type != DT_REG) continue;
    fprintf(txt, "%s\n", dir->d_name);
    (*max)++;
  }
  fclose(txt);
}



void print_progress(size_t count, size_t max) {
  const int bar_width = 50;
  float progress = (float) count / max;
  int bar_length = progress * bar_width;
  printf("\rProgresso: [");
  for (int i = 0; i < bar_length; ++i) {
      printf("#");
  }
  for (int i = bar_length; i < bar_width; ++i) {
      printf(".");
  }
  printf("] %.2f%%", progress * 100);
  fflush(stdout);
}
