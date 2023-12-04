#include "../include/Image.h"
#include "../include/Filter.h"
#include "../include/SCM.h"
#include "../include/Directory.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
  if (argc != 3){
    fprintf(stderr, "\n\t\t Formato: %s <N1-quantizaçao> <N2-quantizaçao>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  clock_t begin, end;
  
  begin = clock();

  int values[2] = {atoi(argv[1]), atoi(argv[2])};
  int matrixFactor[3] = {3, 5, 7};
  
  for (int i = 0; i < 3; i++){
    readDataset("./datasets", matrixFactor[i], values);
  } 

  end = clock();
  
  printf("\t\tTempo de Execução: %lf\n", (double) (end - begin) / CLOCKS_PER_SEC);
  return 0;
}
