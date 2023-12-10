# Feature_Extractor
Implementação de um extrator de características de uma imagem, para posterior classificação.

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
