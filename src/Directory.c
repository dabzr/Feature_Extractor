/*

  Equipe: Emannuel Levi, Henrique Fernandes, Levi Mena, Raimundo Rafael
  Avaliação 04: Trabalho Final
  04.505.23 - 2023.2 - Prof.Daniel Ferreira
  Compilador: gcc (GCC) 13.2.1 20230801.

*/



#include "../include/Image.h"
#include "../include/Filter.h"
#include "../include/SCM.h"
#include "../include/Directory.h"
#include <stdio.h>
#include <stdlib.h>

#define SAVE_FILTERED_IMAGE 1 // Macro que define se as imagens filtrada serão ou não salvas  
void writeSCMtoCSV(FILE* csv, unsigned char** matrix, int matrixFactor, char * imageName){
  for (int i = 0; i < matrixFactor; i++){
    for(int j = 0; j < matrixFactor; j++){
      fprintf(csv, "%d,", matrix[i][j]); // Escreve cada número separado por vírgula
    }
  }
  char *type = (imageName[0] == '0')?"epithelium":"stroma"; // Imprime como ultimo item da linha do CSV epithelium ou strome
  fprintf(csv, "%s\n", type);
}

void readDataset(const char* path, int filterFactor, int values[2]){
    FILE *txt;
    FILE *csvs[2];
    char fileName[2][300], imagePath[300]; // Strings para escrever nomes e caminhos para os arquivos
    struct pgm imagem; // Cria a instancia da imagem 
    for (int i = 0; i < 2; i++){
      sprintf(fileName[i], "./csv/Image_%dx%d_%d.csv", filterFactor, filterFactor, values[i]); 
      /* Cria o nome do arquivo CSV baseado no valor de quantização e no tamanho da matriz de filtro */
      csvs[i] = fopen(fileName[i], "w");
    }
    txt = fopen("./csv/Imagens.txt", "w"); // Arquivo em que fica organizado o nome das imagens na ordem
    DIR *d;
    struct dirent *dir;
    d = opendir(path); // Abrir diretório
    if (!txt || !d || !csvs[0] || !csvs[1]) { // Verificação de erro ao abrir arquivos
      perror("ERRO"); 
    /* Função que imprime na tela do lado da mensagem erro relacionado à ultima chamada de sistema. Exemplo de uma mensagem: "ERRO: No such file or directory" */
      if(txt) fclose(txt); // Fecha os outros arquivos que foram abertos
      if(d) closedir(d);
      if(csvs[0]) fclose(csvs[0]);
      if(csvs[1]) fclose(csvs[1]);
      exit(1);
    };

    for(int i = 0; i < 2; i++){
      for(int j = 0; j < (values[i] * values[i]); j++){
        fprintf(csvs[i], "%d,", j); // Coloca o índice do CSV
      }
      fprintf(csvs[i], "%d",(values[i] * values[i]));
      fprintf(csvs[i], "\n");
    }

    while ((dir = readdir(d)) != NULL) {
      if (dir->d_type != DT_REG) continue;  
    /* DT_REG é um macro para verificar se é um arquivo regular, e no código utilizei-o para caso não seja ele pule para proxima iteração */
      fprintf(txt, "%s\n", dir->d_name);
      sprintf(imagePath, "%s/%s", path, dir->d_name); // Caminho para a imagem
      if(!readPGMImage(&imagem, imagePath)) continue; // Le a imagem que está no caminho escolhido
      struct pgm filtrada = filterAverage(imagem, filterFactor); // Filtra a imagem e salva em outra struct de pgm
      #if SAVE_FILTERED_IMAGE != 0 // Verificação se as imagens filtradas devem ser salvas ou não
        sprintf(imagePath, "./filtered/%dx%d/%s", filterFactor, filterFactor, dir->d_name); // Cria o caminho do diretório da imagem filtrada baseada no seu filtro
        writePGMImage(&filtrada, imagePath); // Salva a imagem filtrada
      #endif 
      for(int i = 0; i < 2; i++){
        unsigned char** matriz = CreateSCM(imagem, filtrada, values[i]); // cria a SCM
        writeSCMtoCSV(csvs[i], matriz, values[i], dir->d_name); // Escreve a matriz no arquivo CSV
        freeMatrix(matriz); // Libera a memoria alocada na matriz
      }
      free(imagem.data);
      free(filtrada.data); // Libera a memória alocada nos dados da imagem (Ver Image.c, lá os dados são alocados utilizando a função malloc())
    }
    closedir(d); // Fecha diretório
    fclose(txt); // Fecha os arquivos abertos
    fclose(csvs[0]);
    fclose(csvs[1]);
}
