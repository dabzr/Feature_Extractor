#include "../include/Image.h"

void readPGMImage(struct pgm *img, char *filename){

	FILE *fp;
	char ch;

	if (!(fp = fopen(filename,"r"))){
		perror("Erro.");
		exit(1);
	}

	if ( (ch = getc(fp))!='P'){
		puts("A imagem fornecida não está no formato pgm");
		exit(2);
	}
	
	img->pgmFormat = getc(fp)-48;
	
	fseek(fp,1, SEEK_CUR);

	while((ch=getc(fp))=='#'){
		while( (ch=getc(fp))!='\n');
	}

	fseek(fp,-1, SEEK_CUR);

	fscanf(fp, "%d %d",&img->w,&img->h);
	if (ferror(fp)){ 
		perror(NULL);
		exit(3);
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

}

void writePGMImage(struct pgm *img, char *filename){
	FILE *fp;
	char ch;

	if (!(fp = fopen(filename,"wb"))){
		perror("Erro.");
		exit(1);
	}

	fprintf(fp, "%s\n","P5");
	fprintf(fp, "%d %d\n",img->w, img->h);
	fprintf(fp, "%d\n", 255);

	fwrite(img->data, sizeof(unsigned char),img->size, fp);
	fclose(fp);

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
