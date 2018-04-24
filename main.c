#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int recebePosicaoTreinamento(int *, int);
int *arqAleat(int *);
int *tamanhoImagem(FILE *, int *);
int **alocaMatriz(int *);
int **gravarMatriz(int *, int **, FILE*fp);

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

  sortyAsphalt = (int *)malloc(50*sizeof(int));
  sortyGrass = (int *)malloc(50*sizeof(int));
  diretorioAsphalt = (char *)malloc(30*sizeof(char));
  dimensoesImagem = (int *)malloc(2*sizeof(int));
  int contImagem=0;
  sortyAsphalt = arqAleat(sortyAsphalt);
  sortyGrass = arqAleat(sortyGrass);

  contImagem++;
  posicaoAsphalt = recebePosicaoTreinamento(sortyAsphalt, contImagem);
  if(posicaoAsphalt<10)
    n = sprintf(diretorioAsphalt, "DataSet/asphalt/asphalt_0%d.txt", posicaoAsphalt);
  else
    n = sprintf(diretorioAsphalt, "DataSet/asphalt/asphalt_%d.txt", posicaoAsphalt);
  fp= fopen(diretorioAsphalt, "r");
  dimensoesImagem = tamanhoImagem(fp, dimensoesImagem); //dimensoesImagem[0] -> linha dimensoesImagem[1] ->coluna
  fp= fopen(diretorioAsphalt, "r");
  mat = alocaMatriz(dimensoesImagem);
  mat = gravarMatriz(dimensoesImagem, mat, fp);
  fclose(fp);
  return 0;
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
