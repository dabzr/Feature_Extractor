#pragma once
#include "Image.h"
#include <stdio.h>
#include <stdlib.h>

struct Image filterAverage(struct Image*, int);
unsigned char matrixAverage(unsigned char**, int);
unsigned char **createMatrix(int);
void freeMatrix(unsigned char**, unsigned char*);
