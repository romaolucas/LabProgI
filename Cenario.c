#include <stdlib.h>
#include <stdio.h>
#include "Cenario.h"
#include "Defesa.h"
#include "Tiro.h"

static nodeTiro *tiroList;
static nodeDefense *defenseList;
static boolean init = FALSE;

/*Essas serão as cabeças, não vai ter nenhum tiro ou defesa associado a elas*/
void initCenario()
{
  tiroList = mallocSafe(sizeof(nodeTiro));
  defenseList = mallocSafe(sizeof(nodeDefense));
  /*Incluir aqui depois a parte em que o cenario é gerado aleatoriamente*/
  init = TRUE;
}

void includeDefense(Defense *d)
{
  /*Se não estiver inicializado*/
  if(init == FALSE)
  {
    printf("ERRO: tentativa de incluir defesa sem inicializar listas\n");
    return;
  }
  Point *p = initPoint(x, y, z);
  nodeDefense *corredor = defenseList;
  while (corredor->next != NULL)
    corredor = corredor->next;
  corredor->next->defense = d;
}

void includeTiro(Tiro *t)
{
  if(init == FALSE)
  {
    printf("ERRO: tentativa de incluir tiro sem inicializar listas\n");
    return;
  }
  nodeTiro *corredor  = tiroList;
  while(corredor->next != NULL)
    corredor = corredor->next;
  corredor->next->tiro = t;
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
  nodeTiro *corredor = tiroList;
  nodeTiro *proximo = corredor->next;
  while(proximo != NULL)
  {
    freeTiro(corredor->tiro);
    free(corredor);
    corredor = proximo;
    proximo = proximo->next;
  }
  /*Na última vez, o proximo vai chegar a NULL e o corredor não vai ser liberado.
    Para evitar isso, no final adicionamos:*/
  freeTiro(corredor->tiro);
  free(corredor);
}

void freeListaDefesas()
{
  nodeDefense *corredor = defenseList;
  nodeDefense *proximo = corredor->next;
  while(proximo != NULL)
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
