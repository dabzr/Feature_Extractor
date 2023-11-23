#include "../include/Filter.h"
#include <string.h>

unsigned char matrix_average(unsigned char matrix[3][3]) {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sum += matrix[i][j];
        }
    }
    return sum / 9; 
}

struct Image filter3x3_average(struct Image *image) {
  struct Image filtered_image = *image;
  for (unsigned i = image->w; i < (image->h - 1) * image->w; i++){
    if (i % image->w != 0 && (i + 1) % image->w != 0) {
      unsigned char matrix[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
      int posX = -1;
      for (int x = 0; x < 3; x++){
        int posY = -image->w;
        for (int y = 0; y < 3; y++){
          matrix[y][x] = image->data[i + posY + posX];
          posY += image->w;
        }
        posX++;
      }
      filtered_image.data[i] = matrix_average(matrix);
    }
  }
  return filtered_image;
}
