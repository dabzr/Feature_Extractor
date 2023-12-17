#include "../include/SCM.h"

unsigned char **CreateSCM(struct pgm img, struct pgm filtered_img, unsigned char level){
  unsigned char **matrix = (unsigned char **) malloc(sizeof(unsigned char *) * level); // Aloca a matriz
  unsigned char *matrix_vector = (unsigned char *)calloc(sizeof(unsigned char), level * level); 
  for (int i = 0; i < level; i++) {
    matrix[i] = &matrix_vector[i * level];
  }
  
  unsigned char * DataOGImg = malloc(sizeof(unsigned char) * img.size);
  unsigned char * DataFilteredImg = malloc(sizeof(unsigned char) * filtered_img.size);
  for (int i = 0; i < img.size; i++){
    DataOGImg[i] = (unsigned char) ((img.data[i] / ((float)img.maxValue + 1)) * level);
    DataFilteredImg[i] = (unsigned char) ((filtered_img.data[i] / ((float)filtered_img.maxValue + 1)) * level);
  }
  for (unsigned long i = 0; i < img.size; i++){
    matrix[DataOGImg[i]][DataFilteredImg[i]]++; 
  }
  free(DataOGImg);
  free(DataFilteredImg);
  return matrix;
}

void writeSCMtoCSV(FILE* csv, unsigned char** matrix, int matrixFactor, char * imageName){
  for (int i = 0; i < matrixFactor; i++){
    for(int j = 0; j < matrixFactor; j++){
      fprintf(csv, "%d,", matrix[i][j]);
    }
  }
  char *type = (imageName[0] == '0')?"epithelium":"stroma";
  fprintf(csv, "%s\n", type);
}

void SCMHandling(struct pgm imagem, struct pgm filtrada, int * values, int qtd, char* fileName, FILE **csvs){
    for(int i = 0; i < qtd; i++){
      unsigned char** matriz = CreateSCM(imagem, filtrada, values[i]); 
      writeSCMtoCSV(csvs[i], matriz, values[i], fileName); 
      freeMatrix(matriz);
    }
}

void freeMatrix(unsigned char **matrix) {
    free(matrix[0]); 
    free(matrix);
}
