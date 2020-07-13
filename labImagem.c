//João Henrique de Oliveira Kocssis RA 2760481921003
//Programa de tratamento de imagens que implementa os filtros escala de cinza e esticar contraste

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 129
// readImage abre o arquivo de imagem, le o cabecalho e cria as matrizes R,G e B além dos ponteiros col e rows
void readImage(char *name, int R[MAX][MAX], int G[MAX][MAX], int B[MAX][MAX], int *cols, int *rows){
	int i, j, lixo;
	char p;

	FILE *f;
	f = fopen(name, "r");
	if(f==NULL){
		printf("Erro ao abrir a imagem \"%s\".\n", name);
		return;
	}
	fscanf(f, "%c", &p);
	fscanf(f, "%d", &lixo);
	fscanf(f, "%d %d", cols, rows);
	fscanf(f, "%d", &lixo);
	for(i=0;i<(*rows);i++){
		for(j=0;j<(*cols);j++){
			fscanf(f, "%d %d %d", &R[i][j], &G[i][j], &B[i][j]);
      
		}
	}
	fclose(f);
}
// writeImage recebe o nome do arquivo de saida e escreve R,G,B modificados
void writeImage(char *arqSaida, int R[MAX][MAX], int G[MAX][MAX], int B[MAX][MAX], int cols, int rows){
  	int i, j;
  	FILE *f;

  	f = fopen(arqSaida, "w");
  	fprintf(f, "P3\n%d %d\n255\n",cols, rows);

	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			fprintf(f, "%d %d %d", R[i][j], G[i][j], B[i][j]);
      
			if (j<cols-1){
				fprintf(f, " ");
			}
		}
		fprintf(f, "\n");
	}
	fclose(f);
}


//determina o máximo de uma matriz
int maximo(int v[MAX][MAX], int cols, int rows)
{
  int maxIn=v[0][0],i,j;
  for (i = 0; i < rows; i++)
  {
    for (j = 0; j < cols; j++)
    {
      if(v[i][j]>maxIn)
      {
        maxIn = v[i][j];
      }
    }
  }
  return maxIn;

}


//determina o minimo de uma matriz
int mminimo(int v[MAX][MAX], int cols, int rows)
{
  int miniIn=v[0][0],i,j;
  for (i = 0; i < rows; i++)
  {
    for (j = 0; j < cols; j++)
    {
      if(v[i][j]<miniIn)
      {
        miniIn = v[i][j];
      }
    }
  }
  return miniIn;

}
//implementa estica contraste a partir das matrizes R,G,B e cria as novas novaR,novaG,novaB
void esticarContraste(int R[MAX][MAX], int G[MAX][MAX], int B[MAX][MAX], int novaR[MAX][MAX], int novaG[MAX][MAX], int novaB[MAX][MAX], int cols, int rows){
	int maxR, minR, maxG, minG, maxB, minB;
  maxR = maximo(R, cols,  rows);//para cada cor determina os máximos e mínimos
  minR = mminimo(R,  cols,  rows);
  maxB = maximo(B, cols,  rows);
  minB = mminimo(B,  cols,  rows);
  maxG = maximo(G, cols,  rows);
  minG = mminimo(G,  cols,  rows);

  //calcula o novo contraste a partir de maximos e minimos determinados anteriormente
  int intR =(maxR-minR), intB = (maxB-minB), intG =(maxG - minG);
  for(int i = 0; i < rows; i++)
  {
    for (int j = 0; j<cols; j++)
    {
      novaR[i][j] = ((R[i][j] - minR) * 255 )/ intR;
      novaG[i][j] = ((G[i][j] - minG) * 255 )/ intG;
      novaB[i][j] = ((B[i][j] - minB) * 255 )/ intB; 
    }
  }

}

//implementa escala de cinza a partir de R,G,B
void escalaCinza(int R[MAX][MAX], int G[MAX][MAX], int B[MAX][MAX], int novaR[MAX][MAX], int novaG[MAX][MAX], int novaB[MAX][MAX], int cols, int rows){
  float media = 0;
  
  
  for(int i=0;i < rows; i++)
  {
    for (int j=0; j<cols; j++)
    {
      media = ((R[i][j] + B[i][j] + G[i][j])/3);//calcula a media das matrizes R,G,B
      novaR[i][j]= (int) media; //faz cast de float para int
      novaG[i][j]=novaR[i][j];
      novaB[i][j]=novaR[i][j];
      media = 0;
      
    }
  };
  
  
}

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "Argumentos invalidos.\n");//se nao for passado argumento, retorna erro
    fprintf(stderr, "Usado:");
    for (int i=0; i<argc; i++) {
			fprintf(stderr, " %s", argv[i]);
    }
    fprintf(stderr, "\n");
    return 1;
  }
  char efeito[20];
  char *arqEntrada = argv[1];
  char *arqSaida = argv[2];
  int R[MAX][MAX], G[MAX][MAX], B[MAX][MAX], novaR[MAX][MAX], novaG[MAX][MAX], novaB[MAX][MAX];
  int cols, rows;

  printf("Digite o efeito desejado:\n");
  printf("cinza - Escala de cinza\n");
  printf("contraste - Esticar contraste\n");
  scanf("%s", efeito);

	// Insira seu código aqui
	readImage(arqEntrada, R, G, B, &cols, &rows);// abre o arquivo

  
  if (strcmp(efeito, "cinza")==0) //opcoes
  {
      escalaCinza(R, G, B, novaR, novaG, novaB, cols,  rows);
  }
  else
  {
    esticarContraste(R, G, B,novaR, novaG, novaB, cols,  rows);
  }
   
	
	writeImage(arqSaida,novaR, novaG, novaB, cols,rows);

  return 0;
}
