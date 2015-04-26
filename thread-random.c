
//TODO: Use a basically sec-random program and update it w/ additional functionality
//
//Copy-Pasted from seq-random.c
//Some code from thread-ids.c
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>  // must include stdio  for pvm3.h to compile correctly
#include <sys/times.h> /* for times system call */
#include <sys/time.h>  /* for gettimeofday system call */
#include <pthread.h>

/*#define DEBUG 1*/

#define RANDOM_SEED   12345678 

//The main work routine
void generateRandomNumbers(long long);  
double getMilliSeconds();
long long int threadcount;
long long int randomcount;


/* The main work routine */
void generateRandomNumbers(long long int count)  
{
  int i;
	long int x;

	srandom(RANDOM_SEED);
    for (i = 0; i < count; i++) {
		x = random();
		printf("%ld\n", x);
  	}
}

void *run(void *ptr)//call genearateRandNum~~ here
{


	pthread_exit(NULL);
}

//TODO replace count with the incementing thread ids gotten from argv[2]
int main(int argc, char **argv) 
{
	int i, n;
	int *value;
    pthread_t *tid; 
 
    double timeStart = 0;//TIMER
    double timeElapsed = 0;

	if (argc != 3) {
	 	fprintf(stderr, "Usage: thread-random <num-randoms> <num-threads>\n");
		exit(EXIT_FAILURE);
	}
 //   sscanf(argv[1],"%lld",&count); /* lld for long long int */
    threadcount = atoi(argv[2]);
    randomcount = atoi(argv[1]);
    for (i = 0; i < threadcount; i++){
        generateRandomNumbers(randomcount);
        printf("generated %lld random numbers\n", randomcount);

    }
    
    timeStart = getMilliSeconds();	//And we are off
//  generateRandomNumbers(count);
//  printf("generated %lld random numbers\n", count);

    timeElapsed = getMilliSeconds() - timeStart;
    printf("Elapsed time:  %lf seconds\n",(double)(timeElapsed/1000.0));
    fflush(stdout);

    exit(0);
}
