/*Teste pra ver se ta funcionando o general*/
#include <stdio.h>
#include <stdlib.h>
#include "general.h"
int main()
{
  Point *a, *b;
  int x, y, z;
  printf("Digite tres inteiros do primeiro ponto\n");
  scanf("%d %d %d", &x, &y, &z);
  a = initPoint(x, y, z);
  printf("Mais tres inteiros\n");
  scanf("%d %d %d", &x, &y, &z);
  b = initPoint(x, y, z);
  printf("Distancia dos dois pontos: %f", calcDistance(a, b));
  free(a);
  free(b);
  return 0;
}

