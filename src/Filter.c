#include "../include/Filter.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

unsigned char **createMatrix(unsigned char** matrix, int factor){
  if(!(matrix = (unsigned char**) malloc(sizeof(unsigned char*) * factor))){
    puts("Memória insuficiente!");
    exit(1);
  }

  for(unsigned i = 0; i < factor; i++)
    if (!(*(matrix + i) = (unsigned char*) malloc(sizeof(unsigned char) * factor))){ 
      puts("Memória insuficiente!");
      exit(i + 2);
    }

  return matrix;
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

struct Image filterAverage(struct Image* image, int factor) {
  if(!(factor % 2)){
    puts("É necessário que a matriz tenha tamanho ímpar.");
    exit(1);
  }
   struct Image filtered_image = *image;
   int sum_index, sum_data;
   int coeficient = factor / 2;
   unsigned char** matrix = NULL;
   matrix = createMatrix(matrix, factor);

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

   freeMatrix(matrix, factor);
   return filtered_image;
}

void freeMatrix(unsigned char** matrix, int factor){
  for(unsigned i = 0; i < factor; i++)
    free(*(matrix + i));
  free(matrix);
}
