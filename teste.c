#include <stdio.h>
#include "general.h"
#include "Nave.h"
#include "Defesa.h"
#include "Tiro.h"
#include "Cenario.h"

int main() {
   int gameRunning = TRUE;
   clock_t start = clock();
   int fps = 2;
   double timestep = (double) 1 / fps;
   initShip();
   initCenario();
   /*a ideia eh usarmos algo com o timestep e sair quando o usuario
    * entrar com EOF ou com Q/<Insira uma letra de preferencia>*/
   while (gameRunning)
   { 
     clock_t now = clock();
     if (((double) (now - start)) >= timestep)
     {
       gameRunning = update();
       if (ship->vidas == 0) gameRunning = FALSE;
       imprimeCenario();
       start = now; 
     }

   }
     freeShip();
     freeCenario();
   printf("Fim de execucao!\n");
   return 0;
}
