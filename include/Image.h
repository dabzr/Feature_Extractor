#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct Image{
  int w, h, channels;
  unsigned char *data;
  size_t size;
};

struct Image readPGM(const char *filename);
void savePGM(const char *filename, const struct Image *img);
