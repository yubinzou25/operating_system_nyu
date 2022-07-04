#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
	pid_t pid, ppid;
	pid = fork();
	ppid = getpid();
	if(pid < 0){
		fprintf(stderr, "Fork Failed\n");
		return 1;
	}
	else if(pid == 0){
		printf("process ID of the parent is %d\n", ppid);
	}
	else{
		wait(NULL);
		printf("Child Complete \n");
	}

}
