/*Aqui para algumas structs e funções que podem ser usadas varias vezes*/
#include "general.h"
#include <math.h>
#include <stdlib.h>

double calcDistance(Point *a, Point *b)
{
  return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2) + pow(a->z - b->z, 2));
}

Point *initPoint(double x, double y, double z)
{
  Point *ponto = malloc(sizeof(Point));
  ponto->x = x;
  ponto->y = y;
  ponto->z = z;
  return ponto;  
}

 
/*-------------------------------------------------------------*/ 
/*  mallocSafe 

   O parâmetro de mallocSafe é do tipo size_t.  
   Em muitos computadores, size_t é equivalente a unsigned int.  
   A função mallocSafe não está em nenhuma biblioteca e é desconhecida 
   fora destas notas de aula. 
   Ela é apenas uma abreviatura conveniente.

   Fonte:  http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html
 */

void *
mallocSafe (size_t nbytes)
{
   void *ptr;

   ptr = malloc (nbytes);
   if (ptr == NULL) {
     fprintf (stderr, "Socorro! malloc devolveu NULL!\n");
     exit (EXIT_FAILURE);
   }

   return ptr;
}
 
