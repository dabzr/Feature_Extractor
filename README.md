# Feature_Extractor
Programa que visa extrair características de imagens a partir de uma SCM.

![image](https://github.com/RafaelAndradeDEV/Feature_Extractor/assets/128552152/2e148cd9-60e2-401c-9ba9-e0875f965891)

## Detalhes para a execução:
### Instalação:

`git clone https://github.com/RafaelAndradeDEV/Feature_Extractor.git`

`cd Feature_Extractor`

`mkdir filtered filtered/3x3 filtered/5x5 filtered/7x7 datasets`

(coloque as imagens na pasta datasets)

`make`
### Execução:

  `./bin/imagefilter <N1-de-Quantização> <N2-de-Quantização> <Diretório-do-Dataset>`

  Por padrão é executado como:

  `./bin/imagefilter 8 16 datasets`
  
  ATENÇÃO, caso o programa não seja executado no diretório raiz do projeto (por padrão se chama Feature_Extractor), o programa não irá funcionar.

  No arquivo Directory.c existe a macro SAVE_FILTERED_IMAGE que define se as imagens filtradas serão ou não salvas, caso ela seja zero as imagens filtradas não serão salvas, porém, caso seja diferente de zero elas serão salvas (por padrão nos diretorios filtered/3x3 filtered/5x5 filtered/7x7). 
