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

int readDataset(const char* path, int matrixFactor){
    FILE *txt, *csv8, *csv16;
    char fileName8[30], fileName16[30], imagePath[30];
    struct pgm imagem;
    sprintf(fileName8, "./csv/Image_%dx%d_%d.csv", matrixFactor, matrixFactor, 8);
    sprintf(fileName16, "./csv/Image_%dx%d_%d.csv", matrixFactor, matrixFactor, 16);
    csv8 = fopen(fileName8, "w");
    csv16 = fopen(fileName16, "w");
    txt = fopen("./csv/Imagens.txt", "w");
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (!txt || !d || !csv8 || !csv16) {
      perror("ERRO");
      if(txt) fclose(txt);
      if(d) closedir(d);
      if(csv8) fclose(csv8);
      if(csv16) fclose(csv16);
      exit(EXIT_FAILURE);
    };

    for (int i = 0; i < 8 * 8; i++){
      fprintf(csv8, "%d,", i);
    }
    fprintf(csv8, "%d", 8 * 8);
    fprintf(csv8, "\n");

    for (int i = 0; i < 16 * 16; i++){
      fprintf(csv16, "%d,", i);
    }
    fprintf(csv16, "%d", 16 * 16);
    fprintf(csv16, "\n");

    while ((dir = readdir(d)) != NULL) {
      if (dir->d_name[0] == '.') continue;
      fprintf(txt, "%s\n", dir->d_name);
      sprintf(imagePath, "%s/%s", path, dir->d_name);
      readPGMImage(&imagem, imagePath);
      struct pgm filtrada = filterAverage(imagem, matrixFactor);
      sprintf(imagePath, "./filtered/%dx%d_%s", matrixFactor, matrixFactor, dir->d_name);
      writePGMImage(&filtrada, imagePath);
      unsigned char** matriz8 = CreateSCM(imagem, filtrada, 8);
      writeSCMtoCSV(csv8, matriz8, 8, dir->d_name);
      unsigned char** matriz16 = CreateSCM(imagem, filtrada, 16); 
      writeSCMtoCSV(csv16, matriz16, 16, dir->d_name);
      
      freeMatrix(matriz8);
      freeMatrix(matriz16);
      free(imagem.data);
    }
    closedir(d);
    fclose(txt);
    fclose(csv8);
    fclose(csv16);
    return EXIT_SUCCESS;
}
