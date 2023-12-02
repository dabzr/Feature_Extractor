#include <dirent.h>
#include "Image.h"


void readDataset_multithread(const char* path, int matrixFactor, int quantizedValue);
int readDataset(const char* path, int matrixFactor, int quantizedValue);
