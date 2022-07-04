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
#define READ_END 0
#define WRITE_END 1
int main(int argc, char **argv){
	int n;int fd[2]; pid_t pid;
	n = atoi(argv[1]);
	if(pipe(fd) == -1){
		fprintf(stderr, "Pipe Failed \n");
		return -1;
	}
	pid = fork();
	if(pid < 0){
		fprintf(stderr, "Fork Failed \n");
	}
	else if(pid == 0){
		unsigned int time; float write_msg;
		close(fd[READ_END]);
		for(int y = 0; y < n; y++){
			write_msg = 0.25 * y * y;
			write(fd[WRITE_END], &write_msg, sizeof(float));
			time = rand() % 5000000;
			usleep(time);
		}
		close(fd[WRITE_END]);
		exit(0);
	}
	else{
		float read_msg;
		close(fd[WRITE_END]);
		for(int y = 0; y < n; y++){
			read(fd[READ_END], &read_msg, sizeof(float));;
			printf("The value is: %.5f\n", read_msg);	
		}	
		close(fd[READ_END]);
		int status;
		wait(&status);	
	}
	return 0;

}
