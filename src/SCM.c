#include "../include/SCM.h"

unsigned char **CreateSCM(struct pgm img, struct pgm filtered_img, unsigned char level){
  unsigned char **matrix = (unsigned char **) malloc(sizeof(unsigned char *) * level);
  unsigned char *data = (unsigned char *)calloc(sizeof(unsigned char), level * level);
  for (int i = 0; i < level; i++) {
    matrix[i] = &data[i * level];
  }

  for (unsigned long i = 0; i < img.size; i++){
    matrix[(img.data[i])%level][(filtered_img.data[i])%level]++;
  }
  return matrix;
}

void freeMatrix(unsigned char **matrix) {
    free(matrix[0]);
    free(matrix);
}
