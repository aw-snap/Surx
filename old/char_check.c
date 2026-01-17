#include <stdio.h>
#include <stdlib.h>

int is_alphabed(char* c);
int is_ahh(char* c);

// Check if a char is in the standard english alphabet
int is_alphabed(char* c) {
	int opc = (int)*c;
	
	printf("\nOPC: %d\n", opc);
	
	if (opc >= 61 && opc <= 122) {
		return 1;
	}
	return 0;
}

int is_ahh(char* c) {
	c = (char*)(c - "A");
	if (c <= "z"-0) {
		return 1;
	}
	return 0;
}

int main(void) {
	char* c = "1";

	printf("Is in: %d\n", is_alphabed(c));
	printf("Is in: %d\n", is_ahh(c));

	return 0;
}
