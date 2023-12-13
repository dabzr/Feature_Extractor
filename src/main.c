#include "../include/Image.h"
#include "../include/Filter.h"
#include "../include/SCM.h"
#include "../include/Directory.h"
#include <stdlib.h>
#include <time.h>

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
  int matrixFactor[3] = {3, 5, 7};
  
  for (int i = 0; i < 3; i++){
    readDataset(argv[1], matrixFactor[i], values, qtd);
  } 

  end = clock();
  
  printf("\t\tTempo de Execução: %lf\n", (double) (end - begin) / CLOCKS_PER_SEC);
  return 0;
}
