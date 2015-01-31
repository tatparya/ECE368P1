#include<stdlib.h>
#include<stdio.h>

int main( int argc, char ** argv )
{
	int mode;

	if ( argc < 1 )
	{
		mode = 1;
	}
	else if ( argc == 1 )
	{
		mode = 2;
	}
	
	return 0;
}
