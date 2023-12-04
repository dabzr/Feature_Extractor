#include <dirent.h>
#include "Image.h"

void writeSCMtoCSV(FILE* csv, unsigned char** matrix, int matrixFactor, char * imageName);
void readDataset(const char* path, int matrixFactor, int values[2]);
