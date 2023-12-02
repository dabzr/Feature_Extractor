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
  char *type = (imageName[0] == '0')?"epithelium":"stroma";
  fprintf(csv, "%s\n", type);
  return EXIT_SUCCESS;
}

int readDataset(const char* path, int matrixFactor, int quantizedValue){
    FILE *txt, *csv;
    char fileName[30], imagePath[30];
    struct pgm imagem;
    sprintf(fileName, "./csv/Image_%dx%d_%d.csv", matrixFactor, matrixFactor, quantizedValue);
    csv = fopen(fileName, "w");
    txt = fopen("./csv/Imagens.txt", "w");
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (!txt || !d || !csv) return EXIT_FAILURE;

    for (int i = 0; i < quantizedValue * quantizedValue; i++){
      fprintf(csv, "%d,", i);
    }
    fprintf(csv, "%d", quantizedValue * quantizedValue);
    fprintf(csv, "\n");

    while ((dir = readdir(d)) != NULL) {
      if (dir->d_name[0] == '.') continue;
      fprintf(txt, "%s\n", dir->d_name);
      sprintf(imagePath, "%s/%s", path, dir->d_name);
      readPGMImage(&imagem, imagePath);
      struct pgm filtrada = filterAverage(imagem, matrixFactor);
      // sprintf(imagePath, "./filtered/%dx%d_%d_%s", matrixFactor, matrixFactor, quantizedValue, dir->d_name);
      // writePGMImage(&filtrada, imagePath);
      unsigned char** matriz = CreateSCM(imagem, filtrada, quantizedValue);
      writeSCMtoCSV(csv, matriz, quantizedValue, dir->d_name);
      freeMatrix(matriz);
      free(imagem.data);
    }
    closedir(d);
    fclose(txt);
    fclose(csv);
    return EXIT_SUCCESS;
}
