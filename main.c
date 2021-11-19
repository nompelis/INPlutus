#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "inp.h"


int main( int argc, char *argv[] )
{
   if( argc == 1 ) {
      printf("Supply a filename \n");
      return 1;
   }

   struct inp_script_s scr;

   (void) inPlutus_Script_Read( &scr, argv[1] );
   inPlutus_Script_Clear( &scr );

   return 0;
}

