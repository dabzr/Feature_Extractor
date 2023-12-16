#include "../include/Image.h"
#include "../include/Filter.h"
#include "../include/SCM.h"
#include "../include/Directory.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

#define SAVE_FILTERED_IMAGE 1 
void writeSCMtoCSV(FILE* csv, unsigned char** matrix, int matrixFactor, char * imageName){
  for (int i = 0; i < matrixFactor; i++){
    for(int j = 0; j < matrixFactor; j++){
      fprintf(csv, "%d,", matrix[i][j]);
    }
  }
  char *type = (imageName[0] == '0')?"epithelium":"stroma";
  fprintf(csv, "%s\n", type);
}

void readDataset(const char* path, int filterFactor, int *values, int qtd){
    FILE *txt;
    FILE *csvs[qtd];
    char fileName[qtd][300], imagePath[300];
    struct pgm imagem;
    for (int i = 0; i < qtd; i++){
      sprintf(fileName[i], "./csv/Image_%dx%d_%d.csv", filterFactor, filterFactor, values[i]); 
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
      for (int i = 0; i < qtd; i++)
        if(csvs[i]) fclose(csvs[i]);
      exit(1);
    };

    for(int i = 0; i < qtd; i++){
      for(int j = 0; j < (values[i] * values[i]); j++){
        fprintf(csvs[i], "%d,", j);
      }
      fprintf(csvs[i], "%d",(values[i] * values[i]));
      fprintf(csvs[i], "\n");
    }

    int max = 0;
    struct dirent *count_dir;
    DIR *count_directory = opendir(path);
    if(!count_directory) exit(1);
    while((count_dir = readdir(count_directory)) != NULL) {
      if(count_dir->d_type != DT_DIR) max++;
    }
    closedir(count_directory);
    int count = 0;

    while ((dir = readdir(d)) != NULL) {
      if (dir->d_type != DT_REG) continue;
      fprintf(txt, "%s\n", dir->d_name);
      sprintf(imagePath, "%s/%s", path, dir->d_name);
      if(!readPGMImage(&imagem, imagePath)) continue;
      struct pgm filtrada = filterAverage(imagem, filterFactor);
      #if SAVE_FILTERED_IMAGE != 0 
        sprintf(imagePath, "./filtered/%dx%d/%s", filterFactor, filterFactor, dir->d_name); 
        writePGMImage(&filtrada, imagePath); 
      #endif
      count++;
      print_progress(count, max);
      for(int i = 0; i < qtd; i++){
        unsigned char** matriz = CreateSCM(imagem, filtrada, values[i]); 
        writeSCMtoCSV(csvs[i], matriz, values[i], dir->d_name); 
        freeMatrix(matriz);
      }
      free(imagem.data);
      free(filtrada.data); 
    }
    closedir(d); 
    fclose(txt);
    for (int i = 0; i < qtd; i++)
      fclose(csvs[i]);
}
