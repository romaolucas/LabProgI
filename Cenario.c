#include <stdlib.h>
#include <stdio.h>
#include "Cenario.h"
#include "Defesa.h"
#include "Tiro.h"

static nodeTiro *tiro_list;
static nodeDefense *defense_list;
static boolean init = FALSE;

/*Essas serão as cabeças, não vai ter nenhum tiro ou defesa associado a elas*/
void initCenario()
{
  tiro_list = mallocSafe(sizeof(nodeTiro));
  defense_list = mallocSafe(sizeof(nodeDefense));
  /*Incluir aqui depois a parte em que o cenario é gerado aleatoriamente*/
  init = TRUE;
}

void includeDefense(double x, double y, double z, int hp, TIRO_TIPO shotType)
{
  /*Se não estiver inicializado*/
  if(init == FALSE)
  {
    printf("ERRO: tentativa de incluir defesa sem inicializar listas\n");
    return;
  }
  Point *p = initPoint(x, y, z);
  nodeDefense *corredor = defense_list;
  while (corredor->next != null)
    corredor = corredor->next;
  corredor->next = initDefesa(p, hp, shotType);
}

void includeTiro(Tiro *t)
{
  if(init == FALSE)
  {
    printf("ERRO: tentativa de incluir tiro sem inicializar listas\n");
    return;
  }
  nodeTiro *corredor  = tiro_list;
  while(corredor->next != null)
    corredor = corredor->next;
  corredor->next = t;
}

void freeCenario()
{
  if (init == FALSE)
    return;     
  freeListaTiros();
  freeListaDefesas();
}
void freeListaTiros()
{
  nodeTiro *corredor = tiro_list;
  nodeTiro *proximo = corredor->next;
  while(proximo != null)
  {
    freeTiro(corredor->tiro);
    free(corredor);
    corredor = proximo;
    proximo = proximo->next;
  }
  /*Na última vez, o proximo vai chegar a null e o corredor não vai ser liberado.
    Para evitar isso, no final adicionamos:*/
  freeTiro(corredor->tiro);
  free(corredor);
}

void freeListaDefesas()
{
  nodeDefense *corredor = defense_list;
  nodeDefense *proximo = corredor->next;
  while(proximo != null)
  {
    freeDefense(corredor->defense);
    free(corredor);
    corredor = proximo;
    proximo = proximo->next;
  }
  /*Aplica-se a mesma lógica do anterior*/
  freeDefense(corredor->defense);
  free(corredor);
}
