#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "asm.h"

void next();
void fop();
void sum();
void inp();

char ch;
int ofst = 0;
int tok;
char *tokc;

void next() {
	inp();

	if( isdigit( ch ) ) {
		char a[100];
		int i = 0;
		a[i++] = ch;

		while( 1 ) {
			inp();

			if( ! isdigit( ch ) ) {
				ofst--; break;
			}

			a[i++] = ch;
			
		}
		a[i] = '\0';

		tokc = a;
		tok = 1;
	} else {
		tok = ch;
		tokc = "";
	}
}

void fop() {
	next();

	if( tok == '*' ) {
		next();

		push(EAX);
		mov(EAX, atoi(tokc) );

		printf("push eax\nmov eax, %s\n", tokc );

		printf("\n");

		pop(ECX);
		imul( EAX, ECX);

		printf("pop ecx\n");
		printf("imul eax,ecx\n");
		printf("\n");

		sum();
	} else if( tok == '/') {
		next();

		push(EAX);
		mov(EAX, atoi(tokc) );

		printf("push eax\nmov eax, %s\n", tokc );
		printf("\n");


		pop(ECX);
		xchg( ECX, EAX );
		cdq();
		idiv( ECX );
		
		printf("pop ecx\n");
		printf("xchg   ecx,eax\n");
		printf("cdq\n");
		printf("idiv  ecx\n");
		printf("\n");

		sum();
	}
}

void sum() {
	fop();

	if( tok == '+' ) {
		next();

		push(EAX);
		mov(EAX, atoi(tokc) );

		printf("push eax\nmov eax, %s\n", tokc );
		printf("\n");

		sum();

		pop(ECX);
		add(EAX, ECX);

		printf("pop ecx\n");
		printf("add eax,ecx\n");
		printf("\n");

	} else if( tok == '-' ) {
		next();

		push(EAX);
		mov(EAX, atoi(tokc) );

		printf("push eax\nmov eax, %s\n", tokc );
		printf("\n");

		sum();

		pop(ECX);
		sub(EAX, ECX);
		neg( EAX );

		printf("pop ecx\n");
		printf("sub eax,ecx\n");
		printf("neg eax\n");
	}
}

char *str = "30+4/2*2+4";


void inp() {
	ch = str[ofst++];
}


int main(int argc, char const *argv[])
{

	printf("%s", str);
	printf("\n");
	next();
	mov( EAX, atoi( tokc ) );

	printf("mov eax, %s\n", tokc );
	printf("\n");
	sum();

	ret();

	printf("%d\n", exec( asm_instruction, asm_iter ) );

	return 0;
}