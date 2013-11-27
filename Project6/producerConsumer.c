#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


/*Tobias Kundig
  section 1
  Fall '13
  Project 6 */

#define TRUE 1

/* Let's assign a fancy name to our items to be 
produced and consumed. Now we can declare of variable
of type buffer_item when we want to produce or consume
an item*/
typedef int buffer_item;
#define BUFFER_SIZE 5

/* prototypes for insertion and removal functions  */
void insert_item(buffer_item item);
void remove_item(buffer_item *item);

/* declare buffer and three semaphores */
buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

/*  Pointers for keeping track of where left off
    when inserting and removing */

int insertPointer = 0, removePointer = 0;

/*  prototypes for thread functions. When create a thread you
    pass the creation function a pointer to the function
    that you want the  thread to execute. These are them
    and they are definded below.*/
void *producer(void *param);
void *consumer(void *param);

int main(int argc, char *argv[]){
  /* Initialize instance variable */
  int x = 0;
  int check = -1;

  /* acquire the command line arguments. The user should pass
   the length of time that the program should run, how many
  producers there are and how many consumers
  usage: <run time> <num producers> <num consumers>
  Each producer and each consumer will be a thread.*/

  /* If else loop that ensures proper number of arguments*/
  if(argc != 4){
	if(argc < 4){
		printf("Terminating: You entered less than 3 numbers\n");	
	}
	else{
		printf("Terminating: You entered more than 3 numbers\n");
	}
	return 0;	
  }

  /* Initialize the three locks */
  /* check is used to determine if initializations
	are successful*/
  check = pthread_mutex_init(&mutex, NULL);
  if(check == 0){
	printf("Successfully initialized the mutex\n");
  }
  else{
	printf("Did NOT initialize mutex");
  }
  check = sem_init(&empty, 0, BUFFER_SIZE);
  if(check == 0){
	printf("Successfully initialized the empty semaphore\n");
  }
  else{
	printf("Did NOT initialize empty semaphore");
  }

  check = sem_init(&full, 0, 0);
  if(check == 0){
	printf("Successfully initialized the full semaphore\n");
  }
  else{
	printf("Did NOT initialize full semaphore");
  }
  
  /* seed the random number generator with the time */
  srand(time(0));
  
  
  /* Create the producer threads */
  /* loop from 0 while less than number of producers */
    /* create a variable to store the thread id*/
    /* create a variable to store the thread attributes */
    /* initialize the thread attributes */
    /* create the thread */
  while (x < atoi(argv[2])){
	/*printf("%s\n",argv[x]);*/
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	/* Ensure thread creation using check */
	check = pthread_create(&tid, &attr, producer, NULL);
	if (check == 0){
		printf("created producer thread id: %lu\n", (unsigned long) tid);	
	}
	else{printf("We did NOT create the THREAD!!");}
	x++;
  }
  /* Create the consumer threads */
  /* loop from 0 while less than number of producers */
    /* create a variable to store the thread id*/
    /* create a variable to store the thread attributes */
    /* initialize the thread attributes */
    /* create the thread */
  x = 0;  
  while (x < atoi(argv[3])){
	/*printf("%s\n",argv[x]);*/
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	/* Ensure thread creation using check */
	check = pthread_create(&tid, &attr, consumer, NULL);
	if (check == 0){
		printf("created consumer thread id: %lu\n", (unsigned long) tid);
	}
	else{printf("We did NOT create the THREAD!!");}

	x++;
  } 
 
  /* Put this (the main) thread to sleap for a period of 
  time equal to the user passed argument for run time*/
  sleep(atoi(argv[1]));
  return 0;
}

void *producer(void *param)
{
  /* create a variable for a randomly generated buffer item */
  buffer_item buff_item = 0;

  /*  create a variable for randomly generated period of time 
      that producer will sleep just prior to producing each 
      item */
  int counter = 0;  
  /* infinite loop */
  while(TRUE){
    /* generate a random number between 0 and 5 */
    counter = rand()%6;
    /* sleep for that period of time */
    sleep(counter);
    /*  generate a random number and store in variable 
        created above */
    buff_item = rand();
    /*  Insert the item into the buffer using the insert_item 
        method (that you have to create, see below)*/
    printf("Producer produced %d\n", buff_item);
    insert_item(buff_item);
  }

}

void *consumer(void *param){
  /* create a variable for a randomly generated buffer item */
  buffer_item *con_buffItem = 0;

  /*  create a variable for randomly generated period of 
      time that producer will sleep just prior to 
      producing each item */
  int counter = 0;
  
  /* infinite loop */
  while(TRUE){
    /* generate a random number between 0 and 5 */
	counter = rand()%6; 
    
    /* sleep for that period of time */
	sleep(counter);    
    /* remove an item from the buffer utilizing the remove_item
    method (that you have to create, see below) */
	remove_item(con_buffItem);
  }
}


void insert_item(buffer_item item){
  /* Acquire (wait on) Empty Semaphore */
  sem_wait(&empty);
  /* Acquire mutex lock to protect buffer */
  pthread_mutex_lock(&mutex);
  /*  Set the buffer at location "insertPointer" equal to the 
      passed item */
  buffer[insertPointer] = item;

  /* Increment the insertPointer */
  insertPointer ++;
  /*  Mod the insertPointer with the buffer size in case it has
      to wrap around to beginning of buffer */
  if(insertPointer > BUFFER_SIZE){
	insertPointer = insertPointer - BUFFER_SIZE;
  }
  /* Release mutex lock and full semaphore */
  pthread_mutex_unlock(&mutex);
  sem_post(&full);
}


void remove_item(buffer_item *item){
  int removed = 0;
  /* Acquire (wait on) Full Semaphore */
  sem_wait(&full);
  /* Acquire mutex lock to protect buffer */
  pthread_mutex_lock(&mutex);
  /* Acquire item at location "removePointer" from buffer */
  removed = buffer[removePointer];	
  printf("Consumer consumed %d\n",removed);
  /* Set value at that location in buffer to -1 */
  
  buffer[removePointer] = -1;
  
  /* Increment "removePointer" */
  if(removed != 0){
       removePointer ++;
  }
  /*  Mod removePointer with the size of of the buffer in case
      have wrapped in the buffer */
  if(removePointer > BUFFER_SIZE){
	removePointer = removePointer - BUFFER_SIZE;
  }
  /* Release mutex lock and empty semaphore */
  pthread_mutex_unlock(&mutex);
  sem_post(&empty);
}
