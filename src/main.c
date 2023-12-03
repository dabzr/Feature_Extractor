#include "../include/Image.h"
#include "../include/Filter.h"
#include "../include/SCM.h"
#include "../include/Directory.h"
#include <time.h>


int main() {
  clock_t begin, end;

  begin = clock();

  int matrixFactor[3] = {3, 5, 7};
  
  for (int i = 0; i < 3; i++){
    readDataset("./datasets", matrixFactor[i]);
  } 

  end = clock();
  
  printf("\t\tTempo de Execução: %lf\n", (double) (end - begin) / CLOCKS_PER_SEC);
  return 0;
}
