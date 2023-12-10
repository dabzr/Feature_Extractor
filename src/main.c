/*

  Equipe: Emannuel Levi, Henrique Fernandes, Levi Mena, Raimundo Rafael
  Avaliação 04: Trabalho Final
  04.505.23 - 2023.2 - Prof.Daniel Ferreira
  Compilador: gcc (GCC) 13.2.1 20230801.

*/



#include "../include/Image.h"
#include "../include/Filter.h"
#include "../include/SCM.h"
#include "../include/Directory.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
  if (argc != 4){
    fprintf(stderr, "\n\t\t Formato: %s <N1-quantizaçao> <N2-quantizaçao> <Diretório-Do-Dataset>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  clock_t begin, end;
  
  begin = clock();

  int values[2] = {atoi(argv[1]), atoi(argv[2])};
  int matrixFactor[3] = {3, 5, 7};
  
  for (int i = 0; i < 3; i++){
    readDataset(argv[3], matrixFactor[i], values);
  } 

  end = clock();
  
  printf("\t\tTempo de Execução: %lf\n", (double) (end - begin) / CLOCKS_PER_SEC);
  return 0;
}
