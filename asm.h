#ifndef ASM
#define ASM
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>

unsigned char asm_instruction[1000];
int asm_iter;
enum {
  EAX,
  EBX,
  ECX,
  EDX,
};

int exec( unsigned char *code, int size );
void set_asm( unsigned char * ret, int size );
void mov( int reg, int val );
void push( int reg );
void neg( int reg );
void add( int reg, int reg1 );
void sub( int reg, int reg1 );
void imul( int reg, int reg1 );
void idiv( int reg );
void xchg( int reg, int reg1 );
void pop( int reg );
void cdq();
void leave();
void ret();
void and( int reg, int reg1 );
void or( int reg, int reg1 );

#endif