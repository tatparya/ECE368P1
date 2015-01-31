#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct q_element {
	int arrival_time;
	int priority;
	int duration;
	struct q_element * next;
} Q;

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
