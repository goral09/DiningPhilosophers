#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <vector>
#include <algorithm> 
#include <cstdlib>


#include "Fork.h"
#include "Philosopher.h"

using namespace std;

#define NUM_PHIL 5
#define NUM_FORKS 5
#define NUM_GAMES 10

void *start_eating(void *philosopher);
double stopTimer( timespec * spec );
timespec * startTimer();

int main()
{

    pthread_t threads[NUM_PHIL];
    

    for(int i = 0 ; i < 10 ; i++){
        
        Fork* fork1 = new Fork(1, false);
        Fork* fork2 = new Fork(2, false);
        Fork* fork3 = new Fork(3, false);
        Fork* fork4 = new Fork(4, false);
        Fork* fork5 = new Fork(5, false);

        Philosopher* phil1 = new Philosopher(1, fork1);
        Philosopher* phil2 = new Philosopher(2, fork2);
        Philosopher* phil3 = new Philosopher(3, fork3);
        Philosopher* phil4 = new Philosopher(4, fork4);
        Philosopher* phil5 = new Philosopher(5, fork5);

        (*phil1).setLeftNeighbour(phil5);
        (*phil1).setRightNeighbour(phil2);

        (*phil2).setLeftNeighbour(phil1);
        (*phil2).setRightNeighbour(phil3);

        (*phil3).setLeftNeighbour(phil2);
        (*phil3).setRightNeighbour(phil4);

        (*phil4).setLeftNeighbour(phil3);
        (*phil4).setRightNeighbour(phil5);

        (*phil5).setLeftNeighbour(phil4);
        (*phil5).setRightNeighbour(phil1);

        int iret1, iret2, iret3, iret4, iret5;
        iret1 = pthread_create(&threads[0], NULL, start_eating, (void*) phil1);
        iret2 = pthread_create(&threads[1], NULL, start_eating, (void*) phil2);
        iret3 = pthread_create(&threads[2], NULL, start_eating, (void*) phil3);
        iret4 = pthread_create(&threads[3], NULL, start_eating, (void*) phil4);
        iret5 = pthread_create(&threads[4], NULL, start_eating, (void*) phil5);

        pthread_join( threads[0], NULL);
        pthread_join( threads[1], NULL);
        pthread_join( threads[2], NULL);
        pthread_join( threads[3], NULL);
        pthread_join( threads[4], NULL);

        /*printf("\nThread 1 returns: %d",iret1);
        printf("\nThread 2 returns: %d",iret2);
        printf("\nThread 3 returns: %d",iret3);
        printf("\nThread 4 returns: %d",iret4);
        printf("\nThread 5 returns: %d",iret5);*/
        cout << endl;
    }
    
    //printf("\nList size: %d\n", times.size());
    //printf("\nMax time: %f.", max_element(times, times + 7));
    return 0;
}

void *start_eating(void *philosopher){
    Philosopher* phil = (Philosopher*) philosopher;
    //Start timer
    timespec * spec = startTimer();
    while(phil -> isDoneEating() == 0)
    {

        phil -> acquireForks();
        if(phil -> hasBothForks() == 1)
            phil -> iAmEating();
    }
    //End timer
    double value = stopTimer( spec );
    //times.push_back(value);
    printf("\nPhilosopher #%d was eating %.8f", phil -> sayYourNameBitch(), value);
    phil = NULL;
}

timespec * startTimer()
{
    timespec * spec = new timespec;
    clock_gettime( CLOCK_REALTIME , spec );
    return spec;
}

double stopTimer( timespec * spec )
{
    timespec spec2;
    clock_gettime( CLOCK_REALTIME , & spec2 );
    int sec = spec2.tv_sec - spec->tv_sec;
    long int nsec = spec2.tv_nsec - spec->tv_nsec;
    if ( nsec < 0 )
    {
        sec--;
        nsec = 1000000000 - nsec;
    }
    double value = sec + nsec / 1000000000.0;
    if ( spec != NULL )
    delete spec;
    return value;
}