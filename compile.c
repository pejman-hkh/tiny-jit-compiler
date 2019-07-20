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
		if( tok == '(' ) {
			sum(0);
			next();
		} else if( tok == ')') {
			break;
		} else if( tok == 1 ) {
			mov( EAX, atoi( tokc ) );
			next();
		} else if( tok == '-' ) {
			next();
			mov( EAX, atoi( tokc ) );
			mov(ECX,0);
			sub(EAX, ECX);
			neg( EAX );
			next();			
		}

		if( a == 2 )
			break;

		int a1 = 1;
		if( tok == '*' | tok == '/' | tok == '&' ) {
			a1 = 2;
		} else {		
			if( a == 1 ) {
				break;
			}
		}

		int tokt = tok;
		push(EAX);
		sum(a1);
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
			case '&':
				and(EAX, ECX);
				break;
			case '+':
				add(EAX, ECX);
				break;
			case '-':
				sub(EAX, ECX);
				neg( EAX );
				break;
			case '|':
				or( EAX, ECX );
				break;						
		}

	}
}

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