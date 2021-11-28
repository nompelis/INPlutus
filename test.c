#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "inp.h"
#include "inup.h"


int main( int argc, char *argv[] )
{

   struct inupTerm_s *t;
   struct inupConstant_s *c;

   t = inUPlutus_Term_Factory( VARIABLE );
   t = inUPlutus_Term_Factory( DELAY );
   t = inUPlutus_Term_Factory( LAMBDA_ABSTRACTION );
   t = inUPlutus_Term_Factory( APPLICATION );
   t = inUPlutus_Term_Factory( CONSTANT );
   t = inUPlutus_Term_Factory( FORCE );
   t = inUPlutus_Term_Factory( ERROR );
   t = inUPlutus_Term_Factory( BUILTIN );

   c = inUPlutus_Constant_Factory( INTEGER );
   c = inUPlutus_Constant_Factory( BYTESTRING );
   c->constant.bytestring.ptr = malloc( 1000 );
   inUPlutus_Constant_Clear( c );
   c = inUPlutus_Constant_Factory( STRING );
   c->constant.string.ptr = malloc( 2000 );
   inUPlutus_Constant_Clear( c );
   c = inUPlutus_Constant_Factory( CHAR );
   c->constant.charstring.ptr = malloc( 3000 );
   inUPlutus_Constant_Clear( c );
   c = inUPlutus_Constant_Factory( UNIT );
   c = inUPlutus_Constant_Factory( BOOL );

   return 0;
}

