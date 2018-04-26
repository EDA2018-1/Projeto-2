#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

int recebePosicaoTreinamento(int *, int);
int *arqAleat(int *);
int *tamanhoImagem(FILE *, int *);
int **alocaMatriz(int *);
int **gravarMatriz(int *, int **, FILE*fp);
int *calculaIlbp(int **, int *, int *);
int calculaTrecho(int, int, int **);
/*
  FUNCAO DE RANDOM, O Q FOR 1 SERA OS ESCOLHIDOS DE valores DA PASTA, TANTO ASFALTO QUANTO GRAMA,
  LOGO O QUE SOBRA É TESTE
*/
int main (int argc, char *argv[]){
  FILE *fp;
  int posicaoAsphalt;
  char *diretorioAsphalt;
  int  *sortyAsphalt, *sortyGrass, n;
  int **mat;
  int *dimensoesImagem;
  int *frequenciaIlbp;

  sortyAsphalt = (int *)malloc(50*sizeof(int));
  sortyGrass = (int *)malloc(50*sizeof(int));
  diretorioAsphalt = (char *)malloc(30*sizeof(char));
  dimensoesImagem = (int *)malloc(2*sizeof(int));
  frequenciaIlbp = (int *)malloc(512*sizeof(int));
  int contImagem=0;
  sortyAsphalt = arqAleat(sortyAsphalt);
  sortyGrass = arqAleat(sortyGrass);

  contImagem++;// este contador é necessario fazer um for ainda para as 50 imagens
  posicaoAsphalt = recebePosicaoTreinamento(sortyAsphalt, contImagem);
  if(posicaoAsphalt<10)
    n = sprintf(diretorioAsphalt, "DataSet/asphalt/asphalt_0%d.txt", posicaoAsphalt);
  else
    n = sprintf(diretorioAsphalt, "DataSet/asphalt/asphalt_%d.txt", posicaoAsphalt);
  fp= fopen(diretorioAsphalt, "r");
  dimensoesImagem = tamanhoImagem(fp, dimensoesImagem); //dimensoesImagem[0] -> linha dimensoesImagem[1] ->coluna
  fp= fopen(diretorioAsphalt, "r");
  //printf("%s", diretorioAsphalt);
  mat = alocaMatriz(dimensoesImagem);
  mat = gravarMatriz(dimensoesImagem, mat, fp);
  int cont;
  frequenciaIlbp = calculaIlbp(mat, dimensoesImagem, frequenciaIlbp);
  //printf("\n\n\n" );
  //for(cont = 0;cont<512; cont++)
    //printf("%d  ",frequenciaIlbp[cont] );
  fclose(fp);
  return 0;
}
/*
CHAMA A FUNCAO CALCULAILBP QUE SELECIONA A POSICAO DO PIXEL A SER ANALISADO IGNORANDO AS BORDAS
NA FUNCAO calculaTrecho CALCULA A SOMA DOS TERMOS DA NOVA MATRIZ 3X3 E FAZ A MEDIA DELA AI TRANSFORMA
EM BINARIO, FAZ DE MANEIRA CIRCULAR 9 VEZES DESCOBRINDO O VALOR DECIMAL E DEFININDO O MENOR VALOR
RETORNA ESSE VALOR QUE POR SUA VEZ VIRA POSICAO NO VETOR DE FREQUENCIA Q NEM EXPLICADO NA AULA
E XABLAU AMIGOS.
ps: pensei num possivel erro, por conta que os vetores de frequencia estao repetindo muito e tem alguns
que nao aparecem, porem olhei a imagem e os pixel sao mto repetitivos mesmo e o menor valor sempre vai ser baixo
 
*/
int *calculaIlbp(int **mat, int *dimensoes, int *frequenciaIlbp){
  int cont, contaux;
  int valorIlbp;
  for(cont=0;cont<512;cont++)
    frequenciaIlbp[cont]=0;
  for(cont=1;cont<(dimensoes[0]-1);cont++){
    for(contaux=1;contaux<(dimensoes[1]-1);contaux++){
        valorIlbp = calculaTrecho(cont, contaux, mat);
        frequenciaIlbp[valorIlbp]++;
    }
  }
  return frequenciaIlbp;
}
int calculaTrecho(int posicaoLinha, int posicaoColuna, int **mat){
  int cont, contaux;
  int somaM3=0;
  float mediaM3;
  int vetorBina[9], contVetor=0;
  int valorVetorDecimal[9] = {0,0,0,0,0,0,0,0,0};
  for(cont = (posicaoLinha-1); cont<(posicaoLinha+2);cont++){
    for(contaux= (posicaoColuna-1); contaux<(posicaoColuna+2); contaux++){
      somaM3 +=mat[cont][contaux];

    }
  }

  mediaM3 = somaM3/9;
  contVetor = 0;
  for(cont = (posicaoLinha-1); cont<(posicaoLinha+2);cont++){
    for(contaux= (posicaoColuna-1); contaux<(posicaoColuna+2); contaux++){
      if(mat[cont][contaux]<=mediaM3)
        vetorBina[contVetor] = 0;
      else
        vetorBina[contVetor] = 1;
    contVetor++;
    }
  }
  int auxVetor;
  int menorValor=512;
  for (cont=0;cont<9;cont++){
    valorVetorDecimal[cont] = 0;
    for(contaux=0;contaux<9;contaux++){
      valorVetorDecimal[cont] = valorVetorDecimal[cont] + (vetorBina[contaux]*pow(2,contaux));
    }
    auxVetor = vetorBina[0];
    vetorBina[0] = vetorBina[1];
    vetorBina[1] = vetorBina[2];
    vetorBina[2] = vetorBina[3];
    vetorBina[3] = vetorBina[4];
    vetorBina[4] = vetorBina[5];
    vetorBina[5] = vetorBina[6];
    vetorBina[6] = vetorBina[7];
    vetorBina[7] = vetorBina[8];
    vetorBina[8] = auxVetor;
    if (valorVetorDecimal[cont]< menorValor)
      menorValor = valorVetorDecimal[cont];
  }
  return menorValor;
}
int **gravarMatriz(int *dimensoes, int **matriz, FILE*fp){
  int cont, contaux;
  char exc;
  for (cont=0;cont<dimensoes[0];cont++){
    for(contaux=0;contaux<dimensoes[1];contaux++){
      if(fscanf(fp, "%c", &exc) != ';'){
        fscanf(fp, "%d", &matriz[cont][contaux]);

      }
    }
  }
  return matriz;
}
int **alocaMatriz(int *dimensoes){
  int cont, contaux;
  int **matriz;
  matriz = (int **) malloc(dimensoes[0]* sizeof(int *));
  if (matriz == NULL){
    printf("MEMORIA INSUFICIENTE\n");
  }
  for ( cont = 0; cont < dimensoes[0]; cont++ ) {
    matriz[cont] = (int*) malloc(dimensoes[1] * sizeof(int));
    if (matriz[cont] == NULL) {
      printf ("MEMORIA INSUFICIENTE");
    }
  }
  return matriz;
}
int *tamanhoImagem(FILE*fp, int *dimensoesImagem){
  char str;
  dimensoesImagem[1] += 1; //devido ao ultimo ponto e virgula de cada linha que nao possui
  do{
    str =getc(fp);
    if(str == ';' &&dimensoesImagem[0]==0 ){
      dimensoesImagem[1]++;
    }
    if (str == '\n')
    dimensoesImagem[0]++;
  }while(str!=EOF);
  return dimensoesImagem;
}
int recebePosicaoTreinamento(int *sorteados, int contImagem){
    int cont=0;
    int posicao=0;
    int valida=-1;
    do{
      if(sorteados[cont]==1){
        posicao = cont;
        valida++;
      }
      cont++;
    }while(contImagem != valida);
    return posicao+1;
}
int *arqAleat(int *vetor){
  int aletaux[25];
  int cont, contaux;
  srand((unsigned)time(NULL));
  for (cont =0; cont<50;cont++){
    vetor[cont]= 1;
  }
  for (cont =0; cont<25;cont++){
    aletaux[cont] = -1;
  }

  for (cont =0; cont<25;cont++){
    int valida =-1;
    aletaux[cont] = rand()%50;
    for(contaux=0;contaux<25;contaux++){
      if (aletaux[cont] == aletaux[contaux])
        valida++;
    }

    if(valida <1)
      vetor[aletaux[cont]] = 0;
    else
      cont--;
  }
 return vetor;
}
