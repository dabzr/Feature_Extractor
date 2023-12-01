#include "../include/SCM.h"

unsigned char **CreateSCM(struct pgm img, struct pgm filtered_img, unsigned char level){
  unsigned char **matrix = (unsigned char **) malloc(sizeof(unsigned char *) * level);
  for (unsigned char i = 0; i < level; i++){
    matrix[i] = (unsigned char *) calloc(sizeof(unsigned char), level);
  }
  for (unsigned long i = 0; i < img.size; i++){
    matrix[(img.data[i])%level][(filtered_img.data[i])%level]++;
  }
  return matrix;
}

void printMatrix(unsigned char **matrix, unsigned char factor){
  for (int i = 0; i < factor; i++){
    printf("\n\t\t");
    for (int j = 0; j < factor; j++){
      printf("%d ", matrix[i][j]);
    }
  }
  printf("\n");
}
