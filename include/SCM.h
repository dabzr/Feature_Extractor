#include "Image.h"

unsigned char **CreateSCM(struct pgm img, struct pgm filtered_img, unsigned char level);
void freeMatrix(unsigned char**);
