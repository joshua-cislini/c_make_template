#include <stdio.h>

#include "test.h"

int main(void) {
	printf("Hello from main.c!\n");
	test_function();
	getchar();
	return 0;
}