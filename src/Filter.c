#include "../include/Filter.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct pgm filterAverage(struct pgm image, int factor) {
  if(!(factor % 2)){
    puts("É necessário que a matriz tenha tamanho ímpar.");
    exit(1);
  }
  int squared_factor = factor * factor;
  struct pgm filtered_image = image;
  int sum_index, sum_data;
  int coeficient = factor / 2;
  unsigned char** matrix = NULL;
  matrix = createMatrix(factor);

  for (unsigned i = 0; i < image.size; i++) {
      int posX = -coeficient;
      for (int x = 0; x < factor; x++) {
         int posY = (-image.w) * coeficient;
         for (int y = 0; y < factor; y++) {
            sum_index = i + posY + posX;
            if (!((sum_index) % image.w) || !((sum_index + 1) % image.w) || sum_index < 0 || sum_index > image.size) sum_data = 0;
            else sum_data = image.data[sum_index];
            matrix[y][x] = sum_data;
            posY += image.w;
         }
         posX++;
      }
      filtered_image.data[i] = matrixAverage(matrix, factor, squared_factor);
   }

   freeMatrix(matrix);
   return filtered_image;
}


unsigned char matrixAverage(unsigned char** matrix, int factor, int squared_factor) {
   int sum = 0;
   for (int i = 0; i < factor; i++) {
      for (int j = 0; j < factor; j++) {
         sum += matrix[i][j];
      }
   }
   return sum / squared_factor;
}

unsigned char **createMatrix(int factor) {
    unsigned char **matrix = (unsigned char **)malloc(sizeof(unsigned char *) * factor); 
    unsigned char *data = (unsigned char *)malloc(sizeof(unsigned char) * factor * factor);
    if (!matrix || !data) {
        puts("Memória insuficiente!");
        exit(1);
    }
    for (int i = 0; i < factor; i++) {
        matrix[i] = &data[i * factor];
    }

    return matrix;
}

void freeMatrix(unsigned char **matrix) {
    free(matrix[0]);
    free(matrix);    
}
