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
Q * qPush( Q * qHead, Q * qTail, Q * element );
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
    int lastExitTime = 0;

    Q * q0head = NULL;
    Q * q1head = NULL;
    Q * q0tail = NULL;
    Q * q1tail = NULL;

    char * filename = argv[1];

    FILE * fptr;
    fptr = fopen( "test1.txt", "r" );
    while ( !feof(fptr) )
    {
        //read line
        int read = fscanf( fptr, "%d %d %d", &arrivalTime, &priority, &duration );
        //create element
        Q * element = qCreate( arrivalTime, priority, duration );
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
                q1tail -> next = element;
                q1tail = q1tail -> next;
                qPrint( q1head );
            }
        }
    }
    printf( "QUEUE 1\n");
    qPrint( q1head );
    printf( "QUEUE 0\n");
    qPrint( q0head );

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

Q * qPush( Q * qHead, Q * qTail, Q * element )
{
    printf("************\n");
    printf("Pushing element: %d %d %d\n", element -> arrivalTime, element -> priority, element -> duration );
    printf("************\n");
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

    return qHead;
}

Q * qPop( Q * qHead )
{
    printf("---------------------\n");
    printf("Popping element: %d %d %d\n", qHead -> arrivalTime, qHead -> priority, qHead -> duration);
    printf("---------------------\n");
    qPrint( qHead );
    if ( qHead -> next != NULL )
        printf("Next in queue: %d %d %d\n\n", qHead -> next -> arrivalTime, qHead -> next -> priority, qHead -> next -> duration );
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
            printf( "%d : %d %d %d\n", counter, temp -> arrivalTime, temp -> priority, temp -> duration);
            counter++;
            temp = temp -> next;
        }
        printf( "%d : %d %d %d\n", counter, temp -> arrivalTime, temp -> priority, temp -> duration);
        printf("\n");
    }
    else
    {
        printf("Queue is empty!!!\n\n");
    }
}
