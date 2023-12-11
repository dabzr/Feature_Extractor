/*

  Equipe: Emannuel Levi, Henrique Fernandes, Levi Mena, Raimundo Rafael
  Avaliação 04: Trabalho Final
  04.505.23 - 2023.2 - Prof.Daniel Ferreira
  Compilador: gcc (GCC) 13.2.1 20230801.

*/

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
  int coeficient = factor / 2; // Coeficiente que representa quantos pixels cada pixel tem de um lado


  for (unsigned i = 0; i < image.size; i++) { // Ignora pixels que fugiriam dos limites da imagem em cima e embaixo
      sum_data = 0;
      // O "X" da matriz varia de -coeficiente até coeficiente
      for (int x = -coeficient; x <= coeficient; x++) {
         for (int y = -coeficient * (image.w); y <= coeficient * image.w; y+=image.w) {
          sum_index = i + y + x; // Atualiza o índice de acordo com a posição na matriz de filtro 
          if(((((i + coeficient) % image.w) - (coeficient + coeficient)) >= 0 ) && (sum_index >= 0)) // Ignora pixels que fugiriam dos limites da imagem na esquerda e na direita
            sum_data += image.data[sum_index];//Soma cada item da matriz de filtro
         }
      }
      filtered_image.data[i] = sum_data/squared_factor; // Faz a média e substitui no pixel da imagem filtrada
    }

   return filtered_image; // retorna a imagem filtrada
}

