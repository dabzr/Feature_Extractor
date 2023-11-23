#include "../include/Image.h"
struct Image readPGM(const char *filename) {
    struct Image img;
    FILE *file;
    char type[3];
    int maxVal;

    file = fopen(filename, "rb"); // Abre o arquivo PGM em modo de leitura binária

    if (file == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo.\n");
        exit(1);
    }

    fscanf(file, "%2s", type); // Lê o tipo de arquivo PGM

    if (strcmp(type, "P5") != 0) { // Verifica se o tipo de arquivo é P5 (PGM binário)
        fprintf(stderr, "Formato de arquivo não suportado. Este não é um arquivo PGM do tipo P5.\n");
        exit(1);
    }


    fscanf(file, "%d %d\n%d\n", &img.w, &img.h, &maxVal);

    img.channels = 1; // Para PGM, é uma imagem em tons de cinza (um canal)

    img.size = img.w * img.h * img.channels;
    img.data = (unsigned char *)malloc(img.size * sizeof(unsigned char));

    fread(img.data, sizeof(unsigned char), img.size, file); // Lê os dados dos pixels

    fclose(file);
    return img;
}

void savePGM(const char *filename, const struct Image *img) {
    FILE *file = fopen(filename, "wb"); // Abre o arquivo PGM em modo de escrita binária

    if (file == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo para escrita.\n");
        exit(1);
    }

    // Escreve o cabeçalho do arquivo PGM
    fprintf(file, "P5\n%d %d\n255\n", img->w, img->h);

    // Escreve os dados dos pixels
    fwrite(img->data, sizeof(unsigned char), img->size, file);

    fclose(file);
}
