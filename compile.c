#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "asm.h"

void next();
void sum( int l );
void inp();

char ch;
int ofst = 0;
int tok;
char tokc[100];

void next() {
	inp();

	if( isdigit( ch ) ) {
		int i = 0;
		while( isdigit( ch ) ) {
			tokc[i++] = ch;	
			inp();		
		}

		ofst--;
		tokc[i] = '\0';
		tok = 1;
	} else {
		tok = ch;
		memset(tokc, 0, sizeof (tokc) );
	}
}

void sum( int l ) {
	next();
	if( tok == 1) {
		mov( EAX, atoi( tokc ) );
		if( l == 1 )
			next();
	}

	if( tok == '+' ) {
		push(EAX);
		sum(1);
		pop(ECX);
		add(EAX, ECX);
	} else if( tok == '-' ) {
		push(EAX);
		sum(1);
		pop(ECX);
		sub(EAX, ECX);
		neg( EAX );
	} else if( tok == '*' ) {
		push(EAX);
		sum(0);
		pop(ECX);
		imul( EAX, ECX);
		sum(1);
	} else if( tok == '/') {
		push(EAX);
		sum(0);
		pop(ECX);
		xchg( ECX, EAX );
		cdq();
		idiv( ECX );
		sum(1);
	}
}

char *str = "4*3+2*9";

void inp() {
	ch = str[ofst++];
}

int main(int argc, char const *argv[])
{

	printf("%s\n", str);
	sum(1);
	ret();
	printf("%d\n", exec( asm_instruction, asm_iter ) );

	return 0;
}