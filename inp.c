#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

#include "inp.h"

//
// Function to read a Plutus "untyped" script/program fro ma JSON file as it
// is used by the "cardano-cli" executable and (a) extract the hexed program,
// and (b) make a byte of "1" or "0" out of every bit of that bytstream.
//

void inPlutus_Script_Clear( struct inp_script_s *p )
{
   if( p != NULL ) {
      if( p->filedata != NULL ) free( p->filedata );
      if( p->bitchar != NULL ) free( p->bitchar );
      p->filedata = NULL;
      p->bitchar = NULL;
      p->size = 0;
      p->psize = 0;
      p->bsize = 0;
#ifdef _DEBUG_
      fprintf( stdout, " [DEBUG]  Cleared script struct \n" );
#endif
   }
}


int inPlutus_Script_Read( struct inp_script_s *p, const char filename[] )
{
   if( p == NULL || filename == NULL ) return 1;

   // perform some checks and get the file size
   struct stat fs;
   if( stat( filename, &fs ) != 0 ) {
      fprintf( stdout, " ERROR: could not stat() script \"%s\"\n",filename );
      return 2;
   }
   if( S_ISREG(fs.st_mode) != 1 ) {
      fprintf( stdout, " ERROR: File \"%s\" is not a regular file\n",filename );
      return 3;
   }

   size_t isize = (size_t) fs.st_size;
#ifdef _DEBUG_
   fprintf( stdout, " [DEBUG]  File: \"%s\" Size: %d\n", filename, (int) isize);
#endif

   // Allocate memory to store the entire file twice; the first one is to keep
   // it intact in memory, and the second where manipulation will take place.
   // (Over)Allocate memory for the storage of the program in "bits" as uchar.
   // (We will end up storing each bit in a uchar.)
   p->filedata = (char*) malloc( 2*(isize+1) * sizeof(char) );
   p->bitchar = (unsigned char*) malloc( (isize*8) * sizeof(unsigned char) );
   if( p->filedata == NULL || p->bitchar == NULL ) {
      fprintf( stdout, " ERROR: could not allocate memory \n" );
      if( p->filedata != NULL ) free( p->filedata);
      p->filedata = NULL;
      if( p->bitchar != NULL ) free( p->bitchar );
      p->bitchar = NULL;
      return -1;
   }
   p->size = isize;
   p->psize = 0;
   p->bsize = 0;

#ifdef _DEBUG_
   fprintf( stdout, " [DEBUG]  Opening script: \"%s\" \n", filename );
#endif
   int fp = open( filename, O_RDONLY );
   read( fp, p->filedata, (size_t) (p->size) );
   close( fp );

  p->filedata[ p->size ] = '\0';
#ifdef _DEBUG_
   fprintf( stdout, " [DEBUG]  JSON file: \n%s\n", p->filedata );
#endif

   // make a copy of the file
   p->hexprog = &( p->filedata[ isize+1 ] );
   memcpy( p->hexprog, p->filedata, isize+1 ); 

   // parse the copy for the hexcor string
#ifdef _DEBUG_
   fprintf( stdout, " [DEBUG]  Parsing for hexCbor \n");
#endif
   int n,m=-1;
   for(n=0;n<isize;++n) if( p->hexprog[n] == '\n' ) p->hexprog[n] = ' ';
   char *s, *token, *sptr;
   for( n=0, s = p->hexprog; ; ++n, s = NULL ) {
      token = strtok_r( s, "\"", &sptr );

#ifdef _DEBUG2_
      fprintf( stdout, " Token: --->%s<--- \n", token );
#endif
      if( token == NULL ) break;

      // set the index where we expect the hexCbor payload (2 instances later)
      if( strcmp( token, "cborHex" ) == 0 ) m = n + 2;
      // at this token we expect the hexBcor payload
      if( m == n ) p->hexprog = token;
   }
#ifdef _DEBUG_
   fprintf( stdout, " [DEBUG]  Found cborHex: \"%s\" \n", p->hexprog );
   fprintf( stdout, " [DEBUG]  cborHex size: %d \n",(int) strlen( p->hexprog ));
#endif

   // store hexcbor to (binary) cbor
   p->psize = (unsigned int ) strlen( p->hexprog )/2;
   // (will do a writeback to the same memory)
   p->prog = (unsigned char*) p->hexprog;
   for(n=0;n<p->psize;++n) {
      char string[4];
      sprintf( string, "%c%c", p->hexprog[2*n], p->hexprog[2*n+1] );
      sscanf( string, "%x", &m );
      p->prog[n] = (unsigned int) m;
   }
   p->bsize = 8 * p->psize;

   // pick each bit and make a byte of it... Yeah, piss off.
#ifdef _DEBUG_
   fprintf( stdout, " [DEBUG]  Program turned to bits \n");
#endif
   for(n=0;n<p->psize;++n) {
#ifdef _DEBUG_
      fprintf( stdout, " %6d  \"%.2x\"  (byte: %3d)  ",
               n, p->prog[n], p->prog[n] );
#endif
      for(m=0;m<8;++m) {
         unsigned char mask,uc;
         mask = ( 0x01 << 7 );     // start with a mask [1000000]
         mask = mask >> m;         // shift right a number of bits (0-7)
         uc = p->prog[n] & mask;   // use bitmask
         uc = uc >> (7 - m);       // bit-shift to get to position [_______b]
         p->bitchar[n*8+m] = uc;
#ifdef _DEBUG_
         fprintf( stdout, "%d ", p->bitchar[n*8+m] );
#endif
      }
#ifdef _DEBUG_
      fprintf( stdout, "\n" );
#endif
   }

   return 0;
}

