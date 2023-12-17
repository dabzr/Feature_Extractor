#include "Image.h"

void writeSCMtoCSV(FILE* csv, unsigned char** matrix, int matrixFactor, char * imageName); // Função que escreve a SCM em um arquivo CSV
unsigned char **CreateSCM(struct pgm img, struct pgm filtered_img, unsigned char level);
void freeMatrix(unsigned char**);
void SCMHandling(struct pgm imagem, struct pgm filtrada, int * values, int qtd, char* fileName, FILE **csvs);
