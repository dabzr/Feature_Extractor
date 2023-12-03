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


  for (unsigned i = 0; i < image.size; i++) {
      sum_data = 0;
      int posX = -coeficient;
      for (int x = 0; x < factor; x++) {
         int posY = (-image.w) * coeficient;
         for (int y = 0; y < factor; y++) {
            sum_index = i + posY + posX; 
            if (((sum_index) % image.w) && ((sum_index + 1) % image.w) && sum_index >= 0 && sum_index <= image.size) 
              sum_data += image.data[sum_index];
            posY += image.w;
         }
         posX++;
      }
      filtered_image.data[i] = sum_data/squared_factor;
   }

   return filtered_image;
}

void freeMatrix(unsigned char **matrix) {
    free(matrix[0]);
    free(matrix);
}
