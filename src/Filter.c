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
  int sum_index, sum_data, border_verifier_1, border_verifier_2;
  int coeficient = factor / 2;


  for (unsigned i = image.w * coeficient; i < (image.size - (image.w * coeficient)); i++) {
    if((((i + coeficient) % image.w) - (coeficient + coeficient)) >= 0 ){
      sum_data = 0;
      int posX = -coeficient;
      for (int x = 0; x < factor; x++) {
         int posY = (-image.w) * coeficient;
         for (int y = 0; y < factor; y++) {
            sum_index = i + posY + posX;
                sum_data += image.data[sum_index];
            posY += image.w;
         }
         posX++;
      }
      filtered_image.data[i] = sum_data/squared_factor;
    }
   }

   return filtered_image;
}

void freeMatrix(unsigned char **matrix) {
    free(matrix[0]);
    free(matrix);
}
