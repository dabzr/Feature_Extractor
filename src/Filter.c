#include "../include/Filter.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Image filterAverage(struct Image* image, int factor) {
  if(!(factor % 2)){
    puts("É necessário que a matriz tenha tamanho ímpar.");
    exit(1);
  }
  struct Image filtered_image = *image;
  int sum_index, sum_data;
  int coeficient = factor / 2;
  unsigned char** matrix = NULL;
  matrix = createMatrix(factor);

  for (unsigned i = 0; i < image->size; i++) {
      int posX = -1 * coeficient;
      for (int x = 0; x < factor; x++) {
         int posY = (-image->w) * coeficient;
         for (int y = 0; y < factor; y++) {
            sum_index = i + posY + posX;
            if (!((sum_index) % image->w) || !((sum_index + 1) % image->w) || sum_index < 0 || sum_index > image->size) sum_data = 0;
            else sum_data = image->data[sum_index];
            matrix[y][x] = sum_data;
            posY += image->w;
         }
         posX++;
      }
      filtered_image.data[i] = matrixAverage(matrix, factor);
   }

   freeMatrix(matrix, matrix[0]);
   return filtered_image;
}


unsigned char matrixAverage(unsigned char** matrix, int factor) {
   int sum = 0;
   for (int i = 0; i < factor; i++) {
      for (int j = 0; j < factor; j++) {
         sum += matrix[i][j];
      }
   }
   return sum / (factor * factor);
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

void freeMatrix(unsigned char **matrix, unsigned char *data) {
    free(data);
    free(matrix);    
}
