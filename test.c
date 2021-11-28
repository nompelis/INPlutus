#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "inp.h"
#include "inup.h"


int main( int argc, char *argv[] )
{

   struct inupTerm_s t;
   struct inupConstant_s c;

   t.type = VARIABLE;
   t.type = LAMBDA_ABSTRACTION;
   inUPlutus_Term_Clear( &t );

   c.type = BOOL;
   inUPlutus_Constant_Clear( &c );

   return 0;
}

