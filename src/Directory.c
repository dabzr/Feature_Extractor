#include "../include/Image.h"
#include "../include/Filter.h"
#include "../include/SCM.h"
#include "../include/Directory.h"
#include <stdio.h>
#include <stdlib.h>

int writeSCMtoCSV(FILE* csv, unsigned char** matrix, int matrixFactor, char * imageName){
  for (int i = 0; i < matrixFactor; i++){
    for(int j = 0; j < matrixFactor; j++){
      fprintf(csv, "%d,", matrix[i][j]);
    }
  }
  char *type = (imageName[strlen(imageName)-5] == '1')?"stroma":"epithelium";
  fprintf(csv, "%s\n", type);
  return EXIT_SUCCESS;
}

int readDataset(const char* path, int matrixFactor, int quantizedValue){
    FILE *txt, *csv;
    char fileName[30];
    sprintf(fileName, "./csv/Image_%dx%d_%d", matrixFactor, matrixFactor, quantizedValue);
    csv = fopen(fileName, "w");
    txt = fopen("./csv/Imagens.txt", "w");
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (!txt || !d || !csv) return EXIT_FAILURE;

    for (int i = 0; i < matrixFactor * matrixFactor - 1; i++){
      fprintf(csv, "%d,", i);
    }
    fprintf(csv, "%d", matrixFactor * matrixFactor - 1);
    fprintf(csv, "\n");

    while ((dir = readdir(d)) != NULL) {
      if (dir->d_name[0] == '.') continue;
      fprintf(txt, "%s\n", dir->d_name);
      struct pgm imagem;
      readPGMImage(&imagem, "./dataset/lena.pgm");
      struct pgm filtrada = filterAverage(&imagem, matrixFactor);
      writePGMImage(&filtrada, "./filtered/lena_filtered.pgm");
      unsigned char** matriz = CreateSCM(imagem, filtrada, quantizedValue);
      printMatrix(matriz, quantizedValue);
      writeSCMtoCSV(csv, matriz, quantizedValue, dir->d_name);
    }
    closedir(d);
    fclose(txt);
    fclose(csv);
    return EXIT_SUCCESS;
}
