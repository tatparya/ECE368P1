#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

typedef struct Q {
	int arrivalTime;
	int priority;
	int duration;
	int elementTotalTime;
	struct Q * next;
} Q;

int main (int argc, char ** argv)
{
    int duration = 0;
	int TotalTime0 = 0;
	int TotalTime1 = 0;
	int TotalServiceTime0 = 0;
	int TotalServiceTime1 = 0;
	int TotalNumCustomers0 = 0;
	int TotalNumCustomers1 = 0;
	int TotalLength = 0;
	int SystemTime = 0;
	int WaitTime0 = 0;
	int WaitTime1 = 0;
	int AvgWaitTime0 = 0;
	int AvgWaitTime1 = 0;
	int CPU = 0;
	int AvgQLength = 0
	
	Q * q0head = NULL;
	Q * q1head = NULL;
	Q * q0tail = NULL;
	Q * q1tail = NULL;

	char filename = argv[1];

	FILE * fptr;
	ptr = fopen( filename, "wq" );
	while ( !feof(fptr) )
	{
		//read line
		fscanf( fptr, "%d %d %d", &arrivalTime, &priority, &duration );
        
		//create element
		element = qCreate( arrivalTime, priority, duration );
        
        //  Check if new time is time to pop
        if( q0head != NULL )
        {
            if( element -> arrivalTime == ( q0head -> arrivalTime + q0head -> duration ) )
            {
                //  POP!!
                TotalTime0 += q0head -> elementTotalTime;
                TotalServiceTime0 += q0head -> duraton
                qPop( q0head );
            }
        }
        else if( q1head != NULL )
        {
            if( element -> arrivalTime == ( q1head -> arrivalTime + q1head -> duration ) )
            {
                //  POP!!
                TotalTime1 = q1head -> elementTotalTime;
                TotalServiceTime1 += q1head -> duration;
                qPop( q1head );
            }
        }
        
		//push to correct Q, create Q if empty
		if( element -> priority == 0 )
        {
            TotalNumCustomers0++;
            if ( q0tail == NULL )
            //  Initiallizing queue
            {
                q0tail = element;
                q0head = q0tail;
            }
            //  Adding to queue
            else
            {
                qPush( q0head, q0tail, element );  
            }
        }
        if( element -> priority == 1 )
        {
            TotalNumCustomers1++;
            if ( q1tail == NULL )
            {
                q1tail = element;
                q1head = q1head;
            }
            
            else
            {
                qPush( q1head, q1tail, element );
            }
        }
        
        if( element -> arrivalTime != t )
        {
            //  Time changed
            SystemTime++;
            incTime( q0head );
            incTime( q1head );
            TotalLength += qLength( q0Head ) + qLength( q1Head );
        }
	}
	
	while( q1head != NULL || q0head != NULL )
	{
	    //  Keep popping
	    while( q0head != NULL )
        {
            //  POP!!
            TotalTime0 += q0head -> elementTotalTime;
            TotalServiceTime0 += q0head -> duraton;
            SystemTime += q0head -> duration;
            duration = q0head -> duration;
            qPop( q0head );
            TotalLength += ( qLength( q0head ) + qLength( q1head ) ) * duration;
        }
        while( q1head != NULL )
        {
            //  POP!!
            TotalTime1 = q1head -> elementTotalTime;
            TotalServiceTime1 += q1head -> duration;
            SystemTime += q1head -> duration;
            duration = q1head -> duration;
            qPop( q1head );
            TotalLength += ( qLength( q0head ) + qLength( q1head ) ) * duration;
        }
	}
	
	WaitTime0 = TotalTime0 - TotalServiceTime0;
	WaitTime1 = TotalTime1 - TotalServiceTime1;
	
	AvgWaitTime0 = WaitTime0 / TotalNumCustomers0;
    AvgWaitTime1 = WaitTime1 / TotalNumCustomers1;
    
    AvgQLength = TotalLength / SystemTime;
    
    CPU = ( TotalNumCustomers0 + TotalNumCustomers1 ) / ( TotalServiceTime0 + TotalServiceTime1 );
    
    printf("AvgWaitTime0: %d \nAvgWaitTime1: %d \nAvgQLength: %d \nAvgCPUUtilisation: %d\n", AvgWaitTime0, AvgWaitTime1, AvgQLength, CPU );
    
	return 0;
}

Q * qCreate( int arrivalTime, int priority, int duration )
{
	Q * element = malloc( sizeof(Q) );
	element -> arrivalTime = arrivalTime;
	element -> priority = priority;
	element -> duration = duration;
	element -> next = NULL;
	
	return element;
}

void qPush( Q * qHead, Q * qTail, Q * element )
{
    qTail -> next = element;
    element = qTail;
}

Q * qPop( Q * qHead )
{
    
    if( qHead != NULL )
    {
        Q * NewqHead = qHead -> next;
        qHead = NULL;
    
        return NewqHead;
    }
    return NULL;
    //  Destroy element here
}

int qLength( Q * qHead )
{
    if( qHead != NULL )
    {
        Q * temp = qHead;
        int count = 1;
        while( temp -> next != NULL )
        {
            temp = temp -> next;
            count++;
        }
        return count;
    }
    return 0;
}

void incTime( Q * qHead )
{
    if( qHead != NULL )
    {
        Q * temp = qHead;
        while( temp -> next != NULL )
        {
            temp -> elementTotalTime++;
            temp = temp -> next;
        }
    }
}











