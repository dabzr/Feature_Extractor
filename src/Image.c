/*

  Equipe: Emannuel Levi, Henrique Fernandes, Levi Mena, Raimundo Rafael
  Avaliação 04: Trabalho Final
  04.505.23 - 2023.2 - Prof.Daniel Ferreira
  Compilador: gcc (GCC) 13.2.1 20230801.

*/

#include "../include/Image.h"

int readPGMImage(struct pgm *img, char *filename){

	FILE *fp;

	if (!(fp = fopen(filename,"r"))){
		perror("Erro.");
		return 0;
	}

  if(getc(fp) !='P'){
		puts("A imagem fornecida não está no formato pgm");
		return 0;
	}
	
	img->pgmFormat = getc(fp)-48;
	
	fseek(fp,1, SEEK_CUR);

  while(getc(fp)=='#'){
    while((getc(fp) != '\n'));
  }

	fseek(fp,-1, SEEK_CUR);

	fscanf(fp, "%d %d",&img->w,&img->h);
	if (ferror(fp)){ 
		perror(NULL);
		return 0;
	}
	fscanf(fp, "%d",&img->maxValue);
	fseek(fp,1, SEEK_CUR);
  img->size = img->w * img->h;
	img->data = (unsigned char*) malloc(img->size * sizeof(unsigned char));

	switch(img->pgmFormat){
		case 2:
//			puts("Lendo imagem PGM (dados em texto)");
			for (int k=0; k < img->size; k++){
				fscanf(fp, "%hhu", img->data+k);
			}
		break;	
		case 5:
//			puts("Lendo imagem PGM (dados em binário)");
			fread(img->data,sizeof(unsigned char),img->size, fp);
		break;
		default:
			puts("Não está implementado");
	}
	
	fclose(fp);
  return 1;
}

int writePGMImage(struct pgm *img, char *filename){
	FILE *fp;

	if (!(fp = fopen(filename,"wb"))){
		perror("Erro.");
		return 0;
	}

	fprintf(fp, "%s\n","P5");
	fprintf(fp, "%d %d\n",img->w, img->h);
	fprintf(fp, "%d\n", 255);

	fwrite(img->data, sizeof(unsigned char),img->size, fp);
	fclose(fp);
  return 1;
}


void viewPGMImage(struct pgm *img){
	printf("Tipo: %d\n",img->pgmFormat);
	printf("Dimensões: [%d %d]\n",img->w, img->h);
	printf("Max: %d\n",img->maxValue);

	for (int k=0; k < (img->size); k++){
		if (!( k % img->w)) printf("\n");
		printf("%2hhu ",*(img->data+k));
	}
	printf("\n");
}
