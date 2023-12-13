#include <dirent.h>
#include "Image.h"

void writeSCMtoCSV(FILE* csv, unsigned char** matrix, int matrixFactor, char * imageName); // Função que escreve a SCM em um arquivo CSV
void readDataset(const char* path, int FilterFactor, int *values, int qtd); // Função que lê o dataset e aplica filtro
