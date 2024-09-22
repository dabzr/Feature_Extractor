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
  filtered_image.data = malloc(sizeof(unsigned char) * image.size);
  int sum_index, sum_data;
  int coeficient = factor / 2; 


  for (unsigned i = 0; i < image.size; i++) {
      sum_data = 0;
      for (int x = -coeficient; x <= coeficient; x++) {
         for (int y = -coeficient * (image.w); y <= coeficient * image.w; y+=image.w) {
          sum_index = i + y + x; 
          if(((((i + coeficient) % image.w) - (coeficient + coeficient)) >= 0 ) && (sum_index >= 0))
            sum_data += image.data[sum_index];
         }
      }
      filtered_image.data[i] = sum_data/squared_factor;
    }

   return filtered_image;
}

