#include <stdio.h>
#include "general.h"
#include "Nave.h"
#include "Defesa.h"
#include "Tiro.h"
#include "Cenario.h"

int main() {
   int i, k = 1;
   initShip();
   initCenario();
   /*a ideia e tirarmos esse for e usarmos algo com o timestep e sair quando o usuario
    * entrar com EOF ou com Q/<Insira uma letra de preferencia>*/
   for (i = 0; i < 10; i++, k *= 7) {
   }
   imprimeCenario();
   freeShip();
   freeCenario();
   printf("Testaremos tudo aqui!\n");
   return 0;
}
