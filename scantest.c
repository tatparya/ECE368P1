#include <stdlib.h>
#include <stdio.h>

int main()
{
	FILE * fptr;
	fptr = fopen( "test1.txt", "r" );
	int a, b, c;
	printf( "Testing\n" );
	while ( !feof(fptr))
	{
		fscanf( fptr, "%d %d %d", &a, &b, &c );
		printf( "a= %d, b= %d, c= %d\n", a, b, c);
	}

	return 0;
}
