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
    FILE *txt;
    FILE *csvs[2];
    char fileName[2][300], imagePath[300];
    int values[2] = {8, 16};
    struct pgm imagem;
    for (int i = 0; i < 2; i++){
      sprintf(fileName[i], "./csv/Image_%dx%d_%d.csv", matrixFactor, matrixFactor, values[i]);
      csvs[i] = fopen(fileName[i], "w");
    }
    txt = fopen("./csv/Imagens.txt", "w");
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (!txt || !d || !csvs[0] || !csvs[1]) {
      perror("ERRO");
      if(txt) fclose(txt);
      if(d) closedir(d);
      if(csvs[0]) fclose(csvs[0]);
      if(csvs[1]) fclose(csvs[1]);
      exit(EXIT_FAILURE);
    };

    for(int i = 0; i < 2; i++){
      for(int j = 0; j < (values[i] * values[i]); j++){
        fprintf(csvs[i], "%d,", j);
      }
      fprintf(csvs[i], "%d",(values[i] * values[i]));
      fprintf(csvs[i], "\n");
    }

    unsigned char** matriz = NULL;

    while ((dir = readdir(d)) != NULL) {
      if (dir->d_type != DT_REG) continue;  // DT_REG é um macro para verificar se é um arquivo regular, e no código utilizei-o para caso não seja ele pule para proxima iteração
      fprintf(txt, "%s\n", dir->d_name);
      sprintf(imagePath, "%s/%s", path, dir->d_name);
      readPGMImage(&imagem, imagePath);
      struct pgm filtrada = filterAverage(imagem, matrixFactor);
      sprintf(imagePath, "./filtered/%dx%d_%s", matrixFactor, matrixFactor, dir->d_name);
      writePGMImage(&filtrada, imagePath);
      for(int i = 0; i < 2; i++){
        matriz = CreateSCM(imagem, filtrada, values[i]);
        writeSCMtoCSV(csvs[i], matriz, values[i], dir->d_name);
      }

      freeMatrix(matriz);
      free(imagem.data);
    }
    closedir(d);
    fclose(txt);
    fclose(csvs[0]);
    fclose(csvs[1]);
    return EXIT_SUCCESS;
}
