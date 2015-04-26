
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
#define BUFSIZE 32
#define RANDOM_SEED   12345678 

//The main work routine
void generateRandomNumbers(long long, int);  
double getMilliSeconds();
long long int threadcount;
long long int randomcount;


/* The main work routine */
void generateRandomNumbers(long long int count, int threadid)  //use threadid as the seed
{
//int cnt;
//cnt = ((int*)threadid);


  int i;
	long int x;

//	random_r(threadid);
//    for (i = 0; i < count; i++) {
//		  x = random();
//		  printf("%ld\n", x);
//  	}
   
    struct random_data *rdata = (struct random_data *) malloc(sizeof(struct random_data));
    char *statebuf = (char*) malloc(sizeof(char) * BUFSIZE);

    int32_t value;

    initstate_r(threadid, statebuf, BUFSIZE, rdata);
    int status = random_r (rdata, &value);
    if(status != 0)
    {
        perror(" random_r");
        exit(status);
    }
      for (i = 0; i < count; i++) {
		  x = random();
		  printf("TID:%d  %ld\n",threadid, x);
  	}


}

void *run(void *ptr)//call genearateRandNum~~ here
{
int id;
id = *((int*)ptr);

printf("  Thread %d is generating %lld random numbers\n",id, randomcount);
    generateRandomNumbers(randomcount, id);
   //   printf("  generated %lld random numbers\n", randomcount);
	pthread_exit(NULL);
}

//TODO replace count with the incementing thread ids gotten from argv[2]
int main(int argc, char **argv) 
{
	int i;//, n;
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
    timeStart = getMilliSeconds();	//And we are off (START TIMER)
    tid = (pthread_t *) malloc(sizeof(pthread_t) * threadcount);
    for (i = 0; i < threadcount; i++){
    
    		value = (int *) malloc(sizeof(int));
	    	*value = i;
                //the value must be made or i will be read incorrectly
        pthread_create(&tid[i], NULL, run, (void *) value); 
       pthread_join(tid[i], NULL);

  	}
//   	for (i=0; i<threadcount; i++){
//     	pthread_join(tid[i], NULL);
//  }



    

//  generateRandomNumbers(count);
//  printf("generated %lld random numbers\n", count);

    timeElapsed = getMilliSeconds() - timeStart;
    printf("Elapsed time:  %lf seconds\n",(double)(timeElapsed/1000.0));
    fflush(stdout);
//    pthread_exit(NULL);
    exit(EXIT_SUCCESS);
}
