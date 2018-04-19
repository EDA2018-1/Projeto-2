#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int recebePosicaoTreinamento(int *, int);
int *arqAleat(int *);
/*
  FUNCAO DE RANDOM, O Q FOR 1 SERA OS ESCOLHIDOS DE valores DA PASTA, TANTO ASFALTO QUANTO GRAMA,
  LOGO O QUE SOBRA É TESTE
*/
int main (int argc, char *argv[]){
  FILE *fp;
  int posicaoAsphalt;
  char *diretorioAsphalt;
  int  *sortyAsphalt, *sortyGrass, n;
  sortyAsphalt = (int *)malloc(50*sizeof(int));
  sortyGrass = (int *)malloc(50*sizeof(int));
  diretorioAsphalt = (char *)malloc(30*sizeof(char));
  int contImagem=10;
  sortyAsphalt = arqAleat(sortyAsphalt);
  sortyGrass = arqAleat(sortyGrass);
  int cont;
  posicaoAsphalt = recebePosicaoTreinamento(sortyAsphalt, contImagem);
  contImagem++;
  if(posicaoAsphalt<10)
    n = sprintf(diretorioAsphalt, "DataSet/asphalt/asphalt_0%d.txt", posicaoAsphalt);
  else
    n = sprintf(diretorioAsphalt, "DataSet/asphalt/asphalt_%d.txt", posicaoAsphalt);

  fp= fopen(diretorioAsphalt, "r");

  return 0;
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
