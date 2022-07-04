#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define NUM_TRIALS 100000
#define NUM_THREADS 4
int nhits; 
void* WorkerThread(void* pvar);
int main(int argc, char *argv[]){
	pthread_t workers[NUM_THREADS]; pthread_attr_t attr; float result;
	pthread_attr_init(&attr);
	nhits = 0;
	for(int i = 0; i < NUM_THREADS; i++){
		pthread_create(&workers[i], &attr, WorkerThread, argv[1]);
	}
	for(int i = 0; i < NUM_THREADS; i++){
		pthread_join(workers[i], NULL);
	}
	result = (float)nhits / (NUM_TRIALS * NUM_THREADS);
	printf("The result of Monte_Carlo simulation is: %.5f\n", result);
}

void* WorkerThread(void* pvar){
	int i, num, n;
	unsigned int rand_state = (unsigned int) time(NULL) + pthread_self();
	bool count[365];
	n = atoi(pvar);
	for(int i = 0; i < NUM_TRIALS; i++){
		for(int j = 0; j < 365; j++){
			count[j] = false;
		}
		for(int j = 0; j < n; j++){
			num = rand_r(&rand_state) % 365;
			if(count[num]){
				nhits++;
				break;
			}
			count[num] = true;	
		}
		
	}
	pthread_exit(0);
}
