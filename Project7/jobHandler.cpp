#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include "Job.cpp"

using namespace std;

  // Declare global instance data
  vector<Job> jobJar;
  vector<Job> completedJobs;
  pthread_mutex_t mutex;

  void *threadFunc(void *param);

  // Main
int main(int argc, char *argv[]){

  // Declare instance data
  int x = 0;
  int check = -1;
  int numJobs = 100;
  int numThreads = 16;
  Job myJob;
  vector<pthread_t> vectorOfThreads;
  pthread_mutex_init(&mutex, NULL);

  /* If else loop that ensures proper number of arguments*/
  if(argc != 3){
	printf("Terminating: You didn't enter three numbers but we'll let you by this time and use default values.\n");
	}

  // Get number of threads and jobs
  if(argc == 3){
 	numThreads = atoi(argv[1]);
	numJobs = atoi(argv[2]);
  }
  // Creates the Jobs and adds them to the jobJar
  // also assigns a number to jobData and jobID
  while (x < numJobs){
	myJob.jobData = rand()%100;
	myJob.jobID = x;
	jobJar.push_back(myJob);
	x++;
  }
  // Resets X
  x = 0;

  // WHile loop that creates the threads
  while (x < numThreads){
	pthread_t tid;

	/* Ensure thread creation using check */
	check = pthread_create(&tid, NULL, threadFunc, NULL);
	// Push the tids onto the vectorOfThreads
	vectorOfThreads.push_back(tid);
	if (check == 0){printf("Thread %lu:\n", tid);}
	else{printf("We did NOT create the THREAD!!");}
	x++;
  }
  // Resets X
  x = 0;
  // While loop that joins the threads
  while(x < numThreads){
	cout << "Joining the thread:" <<  ((unsigned long) vectorOfThreads[x]) << endl;
	pthread_join(vectorOfThreads[x], NULL);
	cout << "Join Complete:" <<  ((unsigned long) vectorOfThreads[x]) << endl;
	x++;
  }
  // Resets X
  x = 0;
  // While loop that prints the job data when completed
  // I did comment it out but left it for you to check the work
  while (x < numJobs){
	if(completedJobs.size() > 0){
		myJob = completedJobs.back();
		completedJobs.pop_back();//removes last job
  	}
	//cout << "Job ID: " << myJob.jobID << endl;
	//cout << "Job data: " << myJob.jobData << endl;
	//cout << "Processed data: " << myJob.processedData << endl;
	x ++;	
  }
  return 0;
}


// Thread function. This does the work
void *threadFunc(void *param){

  // Declare instance data
  bool jobStatus;
  Job myJob;
  // Locks the jobJar and sets jobStatus
  pthread_mutex_lock(&mutex);
  if(jobJar.size() > 0){jobStatus= true;}
  else{jobStatus = false;}
  // Unlock
  pthread_mutex_unlock(&mutex);

  // Loop that does the work until jobStatus = false
  while(jobStatus){
	// Lock
	pthread_mutex_lock(&mutex);

 	// You gave us this!! Gets the last job and pops it off
	// or sets jobStatus to false
  	if(jobJar.size() > 0){
		// printf("Job jar size: %lu\n", jobJar.size());
		myJob = jobJar.back();
		jobJar.pop_back();//removes last job
	}
  	else{
		printf("Jobs are done!!\n");
		jobStatus = false;
	}
	//cout << "I am thread" << pthread_self() << endl;
	// Unlock
	pthread_mutex_unlock(&mutex);

	// If look that only lets in if jobStatus is still true
	// To DO the job, then put the completed job onto the completed
	// stack.
	if(jobStatus){
		myJob.doJob();
		pthread_mutex_lock(&mutex);
		completedJobs.push_back(myJob);
		pthread_mutex_unlock(&mutex);
	}

  }
  // exits with no return value
  pthread_exit(NULL);
}


