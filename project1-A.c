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

void incTime( Q * qHead );
int qLength( Q * qHead );
Q * qPop( Q * qHead );
Q * qCreate( int arrivalTime, int priority, int duration );
void qPush( Q * qHead, Q * qTail, Q * element );
void qPrint( Q * qHead );

int main (int argc, char ** argv)
{
	int arrivalTime;
	int priority = 0;
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
    int AvgQLength = 0;
   	int lastExitTime = 1;

    Q * q0head = NULL;
    Q * q1head = NULL;
    Q * q0tail = NULL;
    Q * q1tail = NULL;
    Q * elementBeingServed = NULL;

    char * filename = argv[1];

    FILE * fptr;
    fptr = fopen( argv[1], "r" );
    while ( !feof(fptr) )
    {
        //read line
        int read = fscanf( fptr, "%d %d %d", &arrivalTime, &priority, &duration );

        //create element
        Q * element = qCreate( arrivalTime, priority, duration );

        if( element -> arrivalTime != SystemTime )
        {
            //  Time changed
            SystemTime++;

            incTime( q0head );
            incTime( q1head );
            TotalLength += qLength( q0head ) + qLength( q1head );

            printf( "#################################\n");
            printf( "\nSystem Time = %d\n\n", SystemTime );
            if ( elementBeingServed == NULL )
                printf( "No element being served" );
            else
                printf( "element Being served: %d %d %d %d\n\n", elementBeingServed -> arrivalTime, elementBeingServed -> priority, elementBeingServed -> duration, elementBeingServed -> elementTotalTime );

            printf( "QUEUE 1\n");
            qPrint( q1head );
            printf( "QUEUE 0\n");
            qPrint( q0head );
            printf( "\n#################################\n\n");
        }

        if ( priority == 0 )
        {
            TotalServiceTime0 += duration;
            TotalNumCustomers0++;
            if ( q0tail == NULL )
              //  Initiallizing queue
            {
                q0tail = element;
                q0head = q0tail;
                qPrint( q0head );
            }
            //  Adding to queue
            else
            {
                printf("************\n");
                printf("Pushing element: %d %d %d %d\n", element -> arrivalTime, element -> priority, element -> duration, element -> elementTotalTime );
                printf("************\n");
                q0tail -> next = element;
                q0tail = q0tail -> next;
                qPrint( q0head );
            }
        }
        else if ( priority == 1 )
        {
            TotalServiceTime1 += duration;
            TotalNumCustomers1++;
            if ( q1tail == NULL )
            {
                q1tail = element;
                q1head = q1tail;
                qPrint( q1head );
            }

            else
            {
                printf("************\n");
                printf("Pushing element: %d %d %d\n", element -> arrivalTime, element -> priority, element -> duration );
                printf("************\n");
                q1tail -> next = element;
                q1tail = q1tail -> next;
                qPrint( q1head );
            }
        }

        //  Check if new time is time to pop
        if( q0head != NULL )
        {
            if( SystemTime == ( lastExitTime + q0head -> duration ) )
            {
                //  POP!!
                TotalTime0 += q0head -> elementTotalTime;
                q0head = qPop( q0head );
    			lastExitTime = SystemTime;
			}
        }
        else if( q1head != NULL )
        {
            if( SystemTime == ( lastExitTime + q1head -> duration ) )
            {
                //  POP!!
                TotalTime1 += q1head -> elementTotalTime;
                q1head = qPop( q1head );
				lastExitTime = SystemTime;
            }
        }

        printf( "############# t + 1 - del ####################\n");
        printf( "\nSystem Time = %d\n\n", SystemTime );
        printf( "QUEUE 1\n");
        qPrint( q1head );
        printf( "QUEUE 0\n");
        qPrint( q0head );
        printf( "\n#################################\n\n");

        //push to correct Q, create Q if empty

        printf( "TotalLength = %d\n", TotalLength );
    	printf( "Totalwaitingtime0 = %d\n", TotalNumCustomers0 );
    	printf( "Totalwaitingtime1 = %d\n", TotalNumCustomers1 );
        printf( "Totalservicetime0 = %d\n", TotalServiceTime0 );
        printf( "Totalservicetime1 = %d\n", TotalServiceTime1 );
        printf( "TotalwaitTime0 = %d\n", TotalTime0 );
        printf( "TotalwaitTime1 = %d\n", TotalTime1 );

	}

    printf( "__+_+_+_+_+_+_+_+_____________________________\n\n");
    printf( "TotalLength = %d\n", TotalLength );
    printf( "Totalwaitingtime0 = %d\n", TotalNumCustomers0 );
    printf( "Totalwaitingtime1 = %d\n", TotalNumCustomers1 );
    printf( "TotalwaitTime0 = %d\n", TotalTime0 );
    printf( "TotalwaitTime1 = %d\n", TotalTime1 );
    printf( "System Time = %d\n\n", SystemTime );

    while( q1head != NULL || q0head != NULL )
    {
        //  Keep popping
        while( q0head != NULL )
        {
            //  POP!!
            TotalTime0 += q0head -> elementTotalTime;
            TotalServiceTime0 += q0head -> duration;
            SystemTime += q0head -> duration;
            duration = q0head -> duration;
            q0head = qPop( q0head );
            TotalLength += ( qLength( q0head ) + qLength( q1head ) ) * duration;
        }
        while( q1head != NULL )
        {
            //  POP!!
            TotalTime1 += q1head -> elementTotalTime;
            TotalServiceTime1 += q1head -> duration;
            SystemTime += q1head -> duration;
            duration = q1head -> duration;
            q1head = qPop( q1head );
            TotalLength += ( qLength( q0head ) + qLength( q1head ) ) * duration;
        }

        printf( "TotalLength = %d\n", TotalLength );
        printf( "Totalwaitingtime0 = %d\n", TotalNumCustomers0 );
        printf( "Totalwaitingtime1 = %d\n", TotalNumCustomers1 );
        printf( "System Time = %d\n\n", SystemTime );

	    printf( "TotalLength = %d\n", TotalLength );
        printf( "TotalwaitTime0 = %d\n", TotalTime0 );
        printf( "TotalwaitTime1 = %d\n", TotalTime1 );
		printf( "Totalservicetime0 = %d\n", TotalServiceTime0 );
		printf( "Totalservicetime1 = %d\n", TotalServiceTime1 );
		printf( "System Time = %d\n\n", SystemTime );

    }

    WaitTime0 = TotalTime0 - TotalServiceTime0;
    WaitTime1 = TotalTime1 - TotalServiceTime1;

    printf( "\nwaitTime0 = %d\n", WaitTime0 );
    printf( "waitTime1 = %d\n", WaitTime1 );

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
    element -> elementTotalTime = 0;

    return element;
}

void qPush( Q * qHead, Q * qTail, Q * element )
{
    printf("************\n");
	//printf("Pushing element: %d %d %d\n", element -> arrivalTime, element -> priority, element -> duration );
	//printf("************\n");
	if ( qHead != NULL )
    {
        qTail -> next = element;
        qTail = qTail -> next;
        qPrint( qHead );
    }
    else
    {
        qTail = element;
        qHead = qTail;
        qPrint( qHead );
    }

}

Q * qPop( Q * qHead )
{
	printf("---------------------\n");
	printf("Popping element: %d %d %d %d\n", qHead -> arrivalTime, qHead -> priority, qHead -> duration, qHead -> elementTotalTime);
	printf("---------------------\n");
    qPrint( qHead );
	if ( qHead -> next != NULL )
		printf("Next in queue: %d %d %d %d\n\n", qHead -> next -> arrivalTime, qHead -> next -> priority, qHead -> next -> duration, qHead -> elementTotalTime );
    if( qHead != NULL )
    {
        Q * NewqHead = qHead -> next;
        qHead -> next = NULL;

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
        temp -> elementTotalTime++;
    }
}

void qPrint( Q * qHead )
{
    int counter = 0;
    if ( qHead != NULL )
    {
        Q * temp = qHead;
        counter = 1;
        printf( "QUEUE\n_______\n");
        while( temp -> next != NULL )
        {
            printf( "%d : %d %d %d %d\n", counter, temp -> arrivalTime, temp -> priority, temp -> duration, temp -> elementTotalTime );
            counter++;
            temp = temp -> next;
        }
        printf( "%d : %d %d %d %d\n", counter, temp -> arrivalTime, temp -> priority, temp -> duration, temp -> elementTotalTime );
        printf("\n");
    }
    else
    {
        printf("Queue is empty!!!\n\n");
    }
}
