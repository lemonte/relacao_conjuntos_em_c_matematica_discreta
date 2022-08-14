#include <stdio.h>
#include <stdlib.h>

#define TAM_MAX 10
typedef int (*Encontrar)(int[TAM_MAX][TAM_MAX], int, int, int);

// Funcoes auxiliares //

void ImprimeConjunto(int conj[TAM_MAX][TAM_MAX])
{
  int i, j;
  for (i = 0; i < TAM_MAX; i++)
  {
    printf(" ------- ");
    for (j = 0; j < TAM_MAX; j++)
    {
      printf("%d", conj[i][j]);
    }
    printf(" ------- ");
    printf("\n");
  }
}

void zeraMatriz(int conj[TAM_MAX][TAM_MAX])
{
  int i, j;
  for (i = 0; i < TAM_MAX; i++)
  {
    for (j = 0; j < TAM_MAX; j++)
    {
      conj[i][j] = 0;
    }
  }
}

int encontrarElementoRepetido(int conj[TAM_MAX][TAM_MAX], Encontrar verificador)
{
  int linha, coluna, aux;
  for (linha = 0; linha < TAM_MAX; linha++)
  {
    for (coluna = 0; coluna < TAM_MAX; coluna++)
    {
      for (aux = 0; aux < TAM_MAX; aux++)
      {
        if (verificador(conj, linha, coluna, aux) == 0)
          return 0;
      }
    }
  }
  return 1;
}
int encontrar_repetido_linha(int conj[TAM_MAX][TAM_MAX], int linha, int coluna, int aux)
{
  return !(conj[linha][coluna] == conj[linha][aux] && coluna != aux);
}

int encontrar_repetido_coluna(int conj[TAM_MAX][TAM_MAX], int linha, int coluna, int aux)
{
  return !(conj[linha][coluna] == conj[aux][coluna] && linha != aux);
}

void preencherMatriz(int conj[TAM_MAX][TAM_MAX])
{
  int i, j;
  for (i = 0; i < TAM_MAX; i++)
  {
    for (j = 0; j < TAM_MAX; j++)
    {
      conj[i][j] = ((j + 2 * i) / j) % 3 == 0;
    }
  }
}

int possuiApenasZero(int conj[TAM_MAX][TAM_MAX], int linha, int coluna)
{
  int aux;
  for (aux = 0; aux < TAM_MAX; aux++)
  {
    if (conj[linha != -1 ? linha : aux][coluna != -1 ? coluna : aux] != 0)
    {
      return 0;
    }
  }
  return 1;
}

int funcional(int conj[TAM_MAX][TAM_MAX])
{
  return encontrarElementoRepetido(conj, encontrar_repetido_linha);
}

int injetora(int conj[TAM_MAX][TAM_MAX])
{
  return encontrarElementoRepetido(conj, encontrar_repetido_coluna);
}

int sobrejetora(int conj[TAM_MAX][TAM_MAX])
{
  int i;
  for (i = 0; i < TAM_MAX; i++)
  {
    if (possuiApenasZero(conj, -1, i))
    {
      return 0;
    }
  }
  return 1;
}

int total(int conj[TAM_MAX][TAM_MAX])
{
  int i;
  for (i = 0; i < TAM_MAX; i++)
  {
    if (possuiApenasZero(conj, i, -1))
    {
      return 0;
    }
  }
  return 1;
}

int funcao_parcial(int conj[TAM_MAX][TAM_MAX])
{
  return (funcional(conj) && !total(conj));
}

int funcao_total(int conj[TAM_MAX][TAM_MAX])
{
  return (funcional(conj) && total(conj));
}

int funcao_bijetora(int conj[TAM_MAX][TAM_MAX])
{
  return injetora(conj) && sobrejetora(conj) && total(conj) && funcional(conj);
}

int monomorfismo(int conj[TAM_MAX][TAM_MAX])
{
  return total(conj) && injetora(conj);
}

int epimorfismo(int conj[TAM_MAX][TAM_MAX])
{
  return funcional(conj) && sobrejetora(conj);
}

int isorelacao(int conj[TAM_MAX][TAM_MAX])
{
  return monomorfismo(conj) && epimorfismo(conj);
}

int verificar_diagonal(int conj[TAM_MAX][TAM_MAX], int valor_diagonal)
{
  int i;
  for (i = 0; i < TAM_MAX; i++)
  {
    if (conj[i][i] != valor_diagonal)
    {
      return 0;
    }
  }
  return 1;
}

int reflexiva(int conj[TAM_MAX][TAM_MAX])
{
  return verificar_diagonal(conj, 1);
}

int irreflexiva(int conj[TAM_MAX][TAM_MAX])
{
  return verificar_diagonal(conj, 0);
}

int simetrica(int conj[TAM_MAX][TAM_MAX])
{

  int i, j;
  for (i = 0; i < TAM_MAX; i++)
  {
    for (j = 0; j < TAM_MAX; j++)
    {
      if (conj[i][j] != 0 && conj[j][i] == 0)
      {
        return 0;
      }
    }
  }
  return 1;
}

int antissimetrica(int conj[TAM_MAX][TAM_MAX])
{

  int i, j;
  for (i = 0; i < TAM_MAX; i++)
  {
    for (j = 0; j < TAM_MAX; j++)
    {
      if (i != j && conj[i][j] == conj[j][i])
      {
        return 0;
      }
    }
  }
  return 1;
}

void fechoReflexivo(int conj[TAM_MAX][TAM_MAX], int fechoReflexivo[TAM_MAX][TAM_MAX])
{
  zeraMatriz(fechoReflexivo);

  int i, j;
  for (i = 0; i < TAM_MAX; i++)
  {
    for (j = 0; j < TAM_MAX; j++)
    {
      fechoReflexivo[i][j] = conj[i][j];
      if (!reflexiva(conj))
      {
        fechoReflexivo[i][i] = 1;
      }
    }
  }
}

void fechoSimetrico(int conj[TAM_MAX][TAM_MAX], int fechoSimetrico[TAM_MAX][TAM_MAX])
{

  int i, j;
  zeraMatriz(fechoSimetrico);
  for (i = 0; i < TAM_MAX; i++)
  {
    for (j = 0; j < TAM_MAX; j++)
    {
      fechoSimetrico[i][j] = conj[i][j];
      if (!simetrica(conj) && conj[i][j] != 0)
      {
        fechoSimetrico[j][i] = 1;
      }
    }
  }
}

int transitiva(int R[TAM_MAX][TAM_MAX])
{
  int i, j, k;
  i = j = k = 0;
  //aRb ^ bRc -> aRc
  //olho todas as rela��es poss�veis
  for (i = 0; i < TAM_MAX; i++)
  {
    for (j = 0; j < TAM_MAX; j++)
    {
      //se tiver rela��o... verifico se o elemento 2 do par tem outra rela��o
      if (R[i][j] == 1)
      {
        for (k = 0; k < TAM_MAX; k++)
        {
          //bRc verifico se exite
          if (R[j][k] == 1)
          {
            if (R[i][k] == 0)
            {
              return 0; //falhou no aRc
            }
          }
        }
      }
    }
  }
  return 1;
}

int conexa(int conj[TAM_MAX][TAM_MAX])
{
  int i, j;
  for (i = 0; i < TAM_MAX; i++)
  {
    for (j = 0; j < TAM_MAX; j++)
    {
      if (conj[i][j] < 1 && conj[j][i] < 1 && j != i)
      {
        return 0;
      }
    }
  }
  return 1;
}

int ordemParcialAmpla(int conj[TAM_MAX][TAM_MAX])
{
  return reflexiva(conj) && antissimetrica(conj) && transitiva(conj);
}

int ordemParcialEstrita(int conj[TAM_MAX][TAM_MAX])
{
  return irreflexiva(conj) && antissimetrica(conj) && transitiva(conj);
}

int ordemConexaAmpla(int conj[TAM_MAX][TAM_MAX])
{
  return ordemParcialAmpla(conj) && conexa(conj);
}

int ordemConexaEstrite(int conj[TAM_MAX][TAM_MAX])
{
  return ordemParcialEstrita(conj) && conexa(conj);
}

int main()
{
  int conjA[TAM_MAX][TAM_MAX];
  int fechoReflex[TAM_MAX][TAM_MAX];
  int fechoSimet[TAM_MAX][TAM_MAX];
  printf("\n ------- Abrir programa !! ------- \n");
  zeraMatriz(conjA);
  preencherMatriz(conjA);
  printf("\n ------- Imprimir conjunto A ------ \n\n");
  ImprimeConjunto(conjA);
  printf("\n O conjunto é funcional : ");
  funcional(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf(" O conjunto é injetora : ");
  injetora(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf(" O conjunto é total : ");
  total(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf(" O conjunto sobrejetora : ");
  sobrejetora(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf(" é funcao parcial : ");
  funcao_parcial(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf(" é funcao total : ");
  funcao_total(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf(" é funcao bijetora : ");
  funcao_bijetora(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf(" O conjunto possui monomorfismo : ");
  monomorfismo(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf(" O conjunto possui epimorfismo : ");
  epimorfismo(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf(" O conjunto possui isorelacao : ");
  isorelacao(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf(" O conjunto é reflexivo : ");
  reflexiva(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf(" O conjunto é irreflexivo : ");
  irreflexiva(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf(" O conjunto é simetrico : ");
  simetrica(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf(" O conjunto é antissimetrica : ");
  antissimetrica(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf(" O conjunto é transitivo : ");
  transitiva(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf(" O conjunto é conexo : ");
  conexa(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf(" O conjunto é de ordemParcialAmpla : ");
  ordemParcialAmpla(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf(" O conjunto é de ordemConexaEstrite : ");
  ordemConexaEstrite(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf(" O conjunto é de ordemConexaAmpla : ");
  ordemConexaAmpla(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf(" O conjunto é de ordemConexaEstrite : ");
  ordemConexaEstrite(conjA) ? printf("Sim \n") : printf("Nao \n");
  printf("\n O conjunto é feche reflexivo : ");
  printf("\n\n ------- Fecho reflexivo ------ \n");
  printf(" -------------------------- \n");
  fechoReflexivo(conjA, fechoReflex);
  ImprimeConjunto(fechoReflex);
  printf(" -------------------------- \n");
  printf("\n O conjunto é feche Simetrico : ");
  printf("\n\n ------- Fecho Simetrico ------ \n");
  printf(" -------------------------- \n");
  fechoSimetrico(conjA, fechoSimet);
  ImprimeConjunto(fechoSimet);
  printf(" -------------------------- \n\n");
  return 0;
}