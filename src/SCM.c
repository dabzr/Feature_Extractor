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
    DataOGImg[i] = (unsigned char) ((img.data[i] / 256.0) * level);
    DataFilteredImg[i] = (unsigned char) ((filtered_img.data[i] / 256.0) * level);
  }
  for (unsigned long i = 0; i < img.size; i++){
    matrix[DataOGImg[i]][DataFilteredImg[i]]++; 
  }
  free(DataOGImg);
  free(DataFilteredImg);
  return matrix;
}

void freeMatrix(unsigned char **matrix) {
    free(matrix[0]); 
    free(matrix);
}
