#include <stdio.h>
#include "mshell.h"

typedef struct tet
{
	int good;
	struct tet *next;
}test;

void updatePointer(int** ptr) {
    *ptr = malloc(sizeof(int));
    **ptr = 42;
}

int main(int ac, char **str) 
{

    int i  = 0;
    
	
	return 0;
}

