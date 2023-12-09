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
  int coeficient = factor / 2; // Coeficiente que representa quantos pixels cada pixel tem de um lado


  for (unsigned i = image.w * coeficient; i < (image.size - (image.w * coeficient)); i++) { // Ignora pixels que fugiriam dos limites da imagem em cima e embaixo
    if((((i + coeficient) % image.w) - (coeficient + coeficient)) >= 0 ){ // Ignora pixels que fugiriam dos limites da imagem na esquerda e na direita
      sum_data = 0;
      int posX = -coeficient; // O "X" da matriz varia de -coeficiente até coeficiente
      for (int x = 0; x < factor; x++) {
         int posY = (-image.w) * coeficient; // O "Y" também varia de -coeficiente até coeficiente porém para pular/voltar linha você utiliza o tamanho da linha (image.w)
         for (int y = 0; y < factor; y++) {
            sum_index = i + posY + posX; // Atualiza o índice de acordo com a posição na matriz de filtro 
            sum_data += image.data[sum_index]; //Soma cada item da matriz de filtro
            posY += image.w;
         }
         posX++;
      }
      filtered_image.data[i] = sum_data/squared_factor; // Faz a média e substitui no pixel da imagem filtrada
    }
  }

   return filtered_image; // retorna a imagem filtrada
}

