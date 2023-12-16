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
  
  print_progress(0, 3);
  printf("\t %d/%d", 0, 3);
  for (int i = 0; i < 3; i++){
    readDataset(argv[1], matrixFactor[i], values, qtd);
    printf("\t %d/%d", i+1, 3);
  } 

  end = clock();
  
  printf("\n\t\tTempo de Execução: %lf\n", (double) (end - begin) / CLOCKS_PER_SEC);
  return 0;
}

void print_progress(size_t count, size_t max) {
    const int bar_width = 50;

    float progress = (float) count / max;
    int bar_length = progress * bar_width;

    printf("\rProgresso: [");
    for (int i = 0; i < bar_length; ++i) {
        printf("#");
    }
    for (int i = bar_length; i < bar_width; ++i) {
        printf(".");
    }
    printf("] %.2f%%", progress * 100);

    fflush(stdout);
}
