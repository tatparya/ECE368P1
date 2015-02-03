#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>


int main (int argc, char ** argv)
{
    int arrivalTime;
    int priority;
    int duration;
    int sum = 0;
    FILE * fptr;
    fptr = fopen( "test1.txt", "r" );
    while ( !feof(fptr) )
    {
        //read line
        int read = fscanf( fptr, "%d %d %d", &arrivalTime, &priority, &duration );
        //create element
        sum += duration;
    }

    printf("sum = %d\n", sum);
    return 0;
}
