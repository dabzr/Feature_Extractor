#include "../include/Image.h"
#include "../include/Filter.h"
#include "../include/SCM.h"
#include "../include/Directory.h"
#include <stdlib.h>
#include <time.h>

#define FILTER_FACTOR_QUANTITY 3

int main(int argc, char *argv[]){
  if (argc < 3){
    fprintf(stderr, "\n\t\t Formato: %s <Diretório-Do-Dataset> <N-de-Quantização> ... (podem ser quantos níveis de quantização você queira.)\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  clock_t begin, end;
  
  begin = clock();
  int qtd = argc - 2;
  
  int *values = malloc (sizeof(int) * qtd);
  if(!values) exit(EXIT_FAILURE);
  for (int i = 0; i < qtd; i++){
    values[i] = atoi(argv[i+2]);
  }
  int matrixFactor[FILTER_FACTOR_QUANTITY] = {3, 5, 7};
  print_progress(0, 1);
  printf("\t %d/%d", 0, FILTER_FACTOR_QUANTITY);
  int pgm_quantity;
  startDataset(argv[1], &pgm_quantity); 
  for (int i = 0; i < FILTER_FACTOR_QUANTITY; i++){
    readDataset(argv[1], matrixFactor[i], values, qtd, pgm_quantity);
    printf("\t %d/%d", i+1, FILTER_FACTOR_QUANTITY);
  } 

  end = clock();
  
  printf("\n\t\tTempo de Execução: %lf\n", (double) (end - begin) / CLOCKS_PER_SEC);
  return 0;
}
