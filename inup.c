#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

#include "inup.h"


//
// Function to clear (or initialize raw) a Plutus "Untyped term" object.
// The struct that is referenced should have its member "type" set to the enumerator
// value that it represents so that the (implied) accessor retrieves a valid type
// so that the correct member initialization of the union-ed structs is performed.
// (For what members the structs have right now, this is over-complicated, but it is
// in the spirit of how this hsould be programmed.)
//

void inUPlutus_Term_Clear( struct inupTerm_s *p )
{
   if( p == NULL ) return;

#ifdef _DEBUG_
   fprintf( stdout, " [DEBUG]  Clearing Plutus untyped term: %d \n", (int) p->type );
#endif
   switch( p->type ) {

    case( VARIABLE ):
      p->term.variable.name = 0;    // we still do not know what to do here...
      p->term.variable.ptr = NULL;
    break;

    case( DELAY ):
      p->term.delay.term = NULL;
    break;

    case( LAMBDA_ABSTRACTION ):
      p->term.lambda_abs.name = NULL;
      p->term.lambda_abs.term = NULL;
    break;

    case( APPLICATION ):
      p->term.application.term1 = NULL;
      p->term.application.term2 = NULL;
    break;

    case( CONSTANT ):
      p->term.constant.constant = NULL;
    break;

    case( FORCE ):
      p->term.force.term = NULL;
    break;

    case( ERROR ):
      p->term.error.term = NULL;
    break;

    case( BUILTIN ):
      p->term.builtin.builtin = NULL;
    break;
   };
}


//
// Function to clear (or initialize raw) a Plutus "Untyped constant" object.
// The struct that is referenced should have its member "type" set to the enumerator
// value that it represents so that the (implied) accessor retrieves a valid type
// so that the correct member initialization of the union-ed structs is performed.
// (For what members the structs have right now, this is over-complicated, but it is
// in the spirit of how this hsould be programmed.)
//

void inUPlutus_Constant_Clear( struct inupConstant_s *p )
{
   if( p == NULL ) return;

#ifdef _DEBUG_
   fprintf( stdout, " [DEBUG]  Clearing Plutus untyped constant: %d \n",
            (int) p->type  );
#endif
   switch( p->type ) {

    case( INTEGER ):
      p->constant.integer.i = 0;   // ambiguously set this to zero and hope...
    break;

    case( BYTESTRING ):
      p->constant.bytestring.ptr = NULL;
    break;

    case( STRING ):
      p->constant.string.ptr = NULL;
    break;

    case( CHAR ):
      p->constant.charstring.ptr = NULL;
    break;

    case( UNIT ):
      // what did you think would happen here...?
    break;

    case( BOOL ):
      p->constant.boolean.bit = 0;     // ambiguously set this to zero
    break;
   };
}

