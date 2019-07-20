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
int tok = -1;
char tokc[100];
char *str;
int str_len;

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

void sum(int a) {
	next();
	while(ofst < str_len+1) {

		if( tok == 1) {
			mov( EAX, atoi( tokc ) );
			next();
		}

		if( tok == '*' | tok == '/' ) {
			int tokt = tok;
			next();

			push(EAX);
			mov( EAX, atoi( tokc ) );
			pop(ECX);

			switch( tokt ) {
				case '*':
					imul( EAX, ECX);
					break;
				case '/':
					xchg( ECX, EAX );
					cdq();
					idiv( ECX );
					break;
			}

			next();
		}

		if( tok == '+' | tok == '-' ) {
			if( a == 1 )
				break;
			int tokt = tok;
			push(EAX);
			sum(1);
			pop(ECX);

			switch( tokt ) {
				case '+':
					add(EAX, ECX);
					break;
				case '-':
					sub(EAX, ECX);
					neg( EAX );
					break;
			}


		}
	}
}


//3*2+2*5
/*
mov eax 3



*/


/*int a;
void sum( int l ) {
	a = tok;
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
		
		if( a == 1 ) {
			push(EAX);
			sum(1);
			pop(ECX);
			sub(EAX, ECX);
			neg( EAX );
		} else {
			int b = a;
			sum(0);
			mov(ECX, 0);
			sub(EAX, ECX);
			neg( EAX );
			if( b == -1 )
				sum(1);
		}		

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
*/

void inp() {
	ch = str[ofst++];
}

int main(int argc, char const *argv[])
{
	str = argv[1];
	str_len = strlen( str );
	printf("%s\n", str);

	sum(0);
	leave();
	ret();
	printf("%d\n", exec( asm_instruction, asm_iter ) );

	return 0;
}