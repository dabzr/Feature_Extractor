#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct pgm{
	int w, h, pgmFormat, maxValue;
	size_t size;
	unsigned char *data;
};

int readPGMImage(struct pgm *, char *);
void viewPGMImage(struct pgm *);
int writePGMImage(struct pgm *, char *);
