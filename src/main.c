#include "../include/Image.h"
#include "../include/Filter.h"
#include "../include/SCM.h"

int main() {
   struct Image imagem = readPGM("lena.pgm");
   struct Image filtrada = filterAverage(&imagem, 5);
   savePGM("lena_filtered.pgm", &filtrada);
   unsigned char** matriz = CreateSCM(imagem, filtrada, 16);
   printMatrix(matriz, 16);
}
