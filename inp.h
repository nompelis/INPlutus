
#ifndef _INP_H_
#define _INP_H_

struct inp_script_s {
   char *filedata;
   unsigned int size;
   char *hexprog;
   unsigned char *prog;
   unsigned int psize;
   unsigned char *bitchar;
   unsigned int bsize;
};


void inPlutus_Script_Clear( struct inp_script_s *p );

int inPlutus_Script_Read( struct inp_script_s *p, const char filename[] );


#endif

