#include <stdlib.h>
#include <stdio.h>
#include "Cenario.h"
#include "Defesa.h"
#include "Tiro.h"
#include "Nave.h"

static nodeTiro *tiroList;
static nodeDefense *defenseList;
static boolean init = FALSE;
static float maxDefense = 10;
static int N = 0;

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
  nodeDefense *corredor = defenseList;
  while (corredor->next != NULL)
    corredor = corredor->next;
  /*corredor->next é null agora*/
  corredor->next = mallocSafe(sizeof(nodeDefense));
  corredor->next->defense = d;
  N++;
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
  /*Corredor->next é null agora*/
  corredor->next = mallocSafe(sizeof(nodeTiro));
  corredor->next->tiro = t;
}

void imprimeCenario() {
   nodeDefense *p = defenseList->next;
   nodeTiro *q = tiroList->next;
   Point *c;
   printf("Imprindo as defesas\n");
   while (p != NULL) {
      c = p->defense->position;
      printf("Posicao (%4.2f, %4.2f, %4.2f)\n precisao: %4.2f\n hp: %d\n", c->x, c->y, c->z, p->defense->accuracy, p->defense->hp);
      p = p->next;
   }
   printf("Imprimindo os tiros\n");
   while (q != NULL) {
      c = q->tiro->position;
      printf("Posicao (%4.2f, %4.2f, %4.2f)\n", c->x, c->y, c->z);
      q = q->next;
   }
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
  N = 0;
}

void update() {
   Point *p;
   nodeDefense *d;
   nodeTiro *t;
   /*Atualiza posições. Essas funções estão em Tiro.c, Defesa.c, Nave.c*/
   t = tiroList->next;
   while (t != NULL){
     updateTiro(t);
   }
   /*Cria nova defesa, se necessário*/
   createDefense();
   /*A fazer - cria novo tiro, se necessário*/
   /*Checa colisões de tiro<=>defesa*/
   collisionsDefense();
   /*Checa colisão nave<=>tiro*/
   collisionsShip();
   /*movimenta nave de acordo com o que o usuario digitar
    * W, A, S, D controlam a direcao
    * U atirar
    * comandos para mudar a orientacao, talvez? por hora,
    * */
   /*criar um role para movimentar os tiros pelo cenario,
    * como vamos usar a orientacao do tiro?
    * como vamos usar a orientacao da nave?
    * */
}
void createDefense(){
  if (N < (int) maxDefense) {
      p = mallocSafe(sizeof(Point));
      p->x = RandomNumber(0.0, 500.0);
      p->y = RandomNumber(0.0, 600.0);
      p->z = RandomNumber(ship->scenarioPos, 1000.0 + ship->scenarioPos);
      includeDefense(initDefense(p, DEFAULT_HP, NORMAL)); 
   }
}

void collisionsDefense()
{
   nodeDefense *d;
   nodeTiro *t;
   d = defenseList->next;
   while (d != NULL) {
      t = tiroList->next;
      while (t != NULL) {
         if (collision(d->defense->position, t->tiro->position)) {
            defenseGotHit(d->defense, t->tiro->shotPower);
            t = t->next;
            nodeTiro *aux = t;
            freeTiro(aux->tiro);
            free(aux);
         }
         else t = t->next;
      }
      if (isDefenseDestroyed(d->defense)) {
         nodeDefense *auxd = d;
         d = d->next;
         freeDefense(auxd->defense);
         free(auxd);
      }
      else d = d->next;
   }
}

void collisionsShip(){
   t = tiroList->next;
   while (t != NULL) {
      /*criar um campo position para a nave*/
      if (collision(ship->position, t->tiro->position)) {
         shipGotHit(t->tiro->shotPower);
         nodeTiro *aux = t;
         t = t->next;
         freeTiro(aux->tiro);
         free(aux);
       }
      else t = t->next;

   }
}
