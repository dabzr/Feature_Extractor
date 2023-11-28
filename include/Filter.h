#include "Image.h"
#include <stdio.h>
#include <stdlib.h>

struct Image filterAverage(struct Image*, int);
unsigned char matrixAverage(unsigned char**, int);
unsigned char **createMatrix(unsigned char**, int);
void freeMatrix(unsigned char**, int);
