
#ifndef _INUP_H_
#define _INUP_H_

//
// The Plutus "Untyped terms" as structs with members being pointers to arguments
// of a specific type as in Fig. 25. A struct for a generic term is built from a union
// of the individual structs (such that we can apply object oriented programming) and
// an enumeration so as to specify the type of term in the union when instantiated.
//

struct inupTerm_variable_s {
   void* ptr;        // not sure how to treat this ; see notes below
   unsigned int name;
   // This is a variable "named" by the de Bruijn indices convention, which means
   // that should really be an "unsigned integer", if I understood this correctly.
   // For now we will store the "name" as an unsigned integer and will keep it as
   // a pointer to memory, in case we have to give any other info to the interpreter.
};

struct inupTerm_delay_s {
   struct inup_term_s* term;
};

struct inupTerm_lambda_s {
   struct inupTerm_name_s* name;
   struct inupTerm_term_s* term;
};

struct inupTerm_application_s {
   struct inupTerm_term_s* term1;
   struct inupTerm_term_s* term2;
};

struct inupTerm_constant_s {
   struct inupConstant_s* constant;
};

struct inupTerm_force_s {
   struct inupTerm_term_s* term;
};

struct inupTerm_error_s {
   struct inupTerm_term_s* term;
};

struct inupTerm_builtin_s {
   struct inupBuiltin_s* builtin;
};


struct inupTerm_s {
   union {
      struct inupTerm_variable_s    variable;
      struct inupTerm_delay_s       delay;
      struct inupTerm_lambda_s      lambda_abs;
      struct inupTerm_application_s application;
      struct inupTerm_constant_s    constant;
      struct inupTerm_force_s       force;
      struct inupTerm_error_s       error;
      struct inupTerm_builtin_s     builtin;
   } term;
   enum inupTerm_enum {
      VARIABLE,
      DELAY,
      LAMBDA_ABSTRACTION,
      APPLICATION,
      CONSTANT,
      FORCE,
      ERROR,
      BUILTIN
   } type;
};


//
// Function prototypes
//

void inUPlutus_Term_Clear( struct inupTerm_s *p );

#endif

