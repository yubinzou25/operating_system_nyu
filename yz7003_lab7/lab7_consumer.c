#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#define BUF_LEN 10
#define SHARED_MEMORY_NAME "lab7_shm"
int n = 1;
int main(int argc, char **argv){
	int SIZE, shmid; int *ptr; float *arr; float z;
	n = atoi(argv[1]);
	printf("The memory address of n is: %p\n", &n);
	SIZE = (BUF_LEN) * sizeof(float);
	shmid = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_RDWR, 0666);
	if(shmid == -1){
		printf("Share Memory Open Failed: %s\n", strerror(errno));
		exit(1);
	}
	ftruncate(shmid, SIZE);
	ptr = (int*)mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmid, SEEK_SET);
	if(ptr == (void*) -1){
		printf("connect to share memory failed: %s\n", strerror(errno));
        	exit(1);
	}
	int *in = ptr;
	int *out = ptr + 1;
	arr =(float*) (ptr + 2);
	printf("The memory address of the start of shared memory is: %p\n", arr);
	for(int i = 0; i < n; i++){
		while(*in == *out);
		z = arr[*out];
		*out = (*out + 1) % (BUF_LEN - 2);
		printf("The value is: %.5f\n", z);
	}
	shm_unlink("shared_memory");
	return 0;
	
}
