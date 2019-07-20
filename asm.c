#include "asm.h"

char * regStr[] = { "eax", "ebx", "ecx", "edx" };

int exec( unsigned char *code, int size ) {

  void *mem = mmap(NULL, size, PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0);

  memcpy(mem, code, size);

  int (*func)() = mem;

  return func();
}

void set_asm( unsigned char * ret, int size ) {
  for( int i = 0; i < size; i++ ) {
    asm_instruction[asm_iter++] = ret[i];
  } 
}

void mov( int reg, int val ) {
  unsigned char ret[5];

  printf("mov %s, %d\n", regStr[reg], val );

  switch( reg ) {
    case EAX :
      ret[0] = 0xB8;
      ret[1] = val;
      ret[2] = 0x00;
      ret[3] = 0x00;
      ret[4] = 0x00;
      break;

    case EBX : 
      ret[0] = 0xBB;
      ret[1] = val;
      ret[2] = 0x00;
      ret[3] = 0x00;
      ret[4] = 0x00;

      break;

    case EDX :
      ret[0] = 0xBA;
      ret[1] = val;
      ret[2] = 0x00;
      ret[3] = 0x00;
      ret[4] = 0x00;
      break;

    case ECX :
      ret[0] = 0xB9;
      ret[1] = val;
      ret[2] = 0x00;
      ret[3] = 0x00;
      ret[4] = 0x00;
      break;
  }

  set_asm( ret, sizeof( ret ) );
}

void push( int reg ) {
  printf("push %s\n", regStr[reg] );

  unsigned char ret[1];
  switch( reg ) {
    case EAX :
      ret[0] = 0x50;
      break;
    case EBX :
      ret[0] = 0x53;
       break;
    case ECX :
      ret[0] = 0x51; 
      break;
  }

  set_asm( ret, sizeof( ret ) );
}

void neg( int reg ) {
  printf("neg %s\n", regStr[reg] );
  
  unsigned char ret[2];
  ret[0] = 0xF7;
  switch( reg ) {
    case EAX :
      ret[1] = 0xD8;
      break;
  }

  set_asm( ret, sizeof( ret ) );
}

void idiv( int reg ) {
  printf("idiv %s\n", regStr[reg] );

  unsigned char ret[2];
  ret[0] = 0xF7;
  switch( reg ) {
    case ECX :
      ret[1] = 0xF9;
      break;
  }

  set_asm( ret, sizeof( ret ) );
}

void add( int reg, int reg1 ) {
  printf("add %s, %s\n", regStr[reg], regStr[reg1]  );
    
  unsigned char ret[2];
  switch( reg ) {
    case EAX :
      ret[0] = 0x01;
      switch( reg1 ) {
        case EBX :
          ret[1] = 0xD8;
          break;
        case ECX :
          ret[1] = 0xC8;
          break;            
      }
      break; 
  }

  set_asm( ret, sizeof( ret ) );
}

void and( int reg, int reg1 ) {
  printf("and %s, %s\n", regStr[reg], regStr[reg1]  );
    
  unsigned char ret[2];
  switch( reg ) {
    case EAX :
      ret[0] = 0x21;
      switch( reg1 ) {
        case EBX :
          ret[1] = 0xD8;
          break;
        case ECX :
          ret[1] = 0xC8;
          break;            
      }
      break; 
  }

  set_asm( ret, sizeof( ret ) );
}

void or( int reg, int reg1 ) {
  printf("or %s, %s\n", regStr[reg], regStr[reg1]  );
    
  unsigned char ret[2];
  switch( reg ) {
    case EAX :
      ret[0] = 0x09;
      switch( reg1 ) {
        case EBX :
          ret[1] = 0xD8;
          break;
        case ECX :
          ret[1] = 0xC8;
          break;            
      }
      break; 
  }

  set_asm( ret, sizeof( ret ) );
}


void sub( int reg, int reg1 ) {
  printf("sub %s, %s\n", regStr[reg], regStr[reg1]  );

  unsigned char ret[2];
  switch( reg ) {
    case EAX :
      ret[0] = 0x29;
      switch( reg1 ) {
        case EBX :
          ret[1] = 0xD8;
          break;
        case ECX :
          ret[1] = 0xC8;
          break;            
      }
      break; 
  }

  set_asm( ret, sizeof( ret ) );
}

void imul( int reg, int reg1 ) {
  printf("imul %s, %s\n", regStr[reg], regStr[reg1]  );

  unsigned char ret[3];
  switch( reg ) {
    case EAX :
      ret[0] = 0x0F;
      ret[1] = 0xAF;
      switch( reg1 ) {
        case EBX :
          ret[2] = 0xC3;
          break;
        case ECX :
          ret[2] = 0xC1;
          break;            
      }
      break; 
  }

  set_asm( ret, sizeof( ret ) );
}

void xchg( int reg, int reg1 ) {
  printf("xchg %s, %s\n", regStr[reg], regStr[reg1]  );

  unsigned char ret[1];
  switch( reg ) {
    case ECX :
      switch( reg1 ) {
        case EAX :
          ret[0] = 0x91;
          break;
      }
      break; 
  }

  set_asm( ret, sizeof( ret ) );
}


void pop( int reg ) {
  printf("pop %s\n", regStr[reg] );

  unsigned char ret[1];

  switch( reg ) {
    case EAX :
      ret[0] = 0x58;
      break;
    case EBX :
      ret[0] = 0x5B;
      break;     
    case ECX :
      ret[0] = 0x59;
      break; 
  }

  set_asm( ret, sizeof( ret ) );

}

void cdq() {
  printf("cdq\n");
  unsigned char ret[1];
  ret[0] = 0x99;
  set_asm( ret, sizeof( ret ) );
}

void ret() {
  printf("ret\n");  
  unsigned char ret[1];
  ret[0] = 0xC3;
  set_asm( ret, sizeof( ret ) );
}

void leave() {
  printf("leave\n");  
  unsigned char ret[1];
  ret[0] = 0xC9;
  set_asm( ret, sizeof( ret ) );
}
