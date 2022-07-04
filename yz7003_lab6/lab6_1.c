#include <unistd.h>
#include <errno.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#define PORT 9999
int main(int argc, char**argv){
	int n; pid_t pid; int domain;
	if(argc <= 1){
		fprintf(stderr, "Input Argument Wrong.\n");
		return -1;
	}
	n = atoi(argv[1]);
	pid = fork();
	if(pid < 0){
		fprintf(stderr, "Fork Failed. \n");
		return -1;
	}
	else if(pid == 0){
		struct sockaddr_in my_addr;
		struct sockaddr_in client_addr;
		int sockfd;
		int clientfd;
		int sin_size;
		unsigned int socket_wait;
		unsigned int time;
		float write_msg;
		socket_wait = rand() % 4000000 + 1000000;
		/* create server socket*/
		if((sockfd = socket(AF_INET, SOCK_STREAM, 0))==-1){
			fprintf(stderr, "Server Socket Failed\n");
			return -1;
		}
		my_addr.sin_family = AF_INET;
		my_addr.sin_port = htons(PORT);
		my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		bzero(&(my_addr.sin_zero), 8);
		/* set socket option */
        	int option = 1;
	       	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == -1){
			fprintf(stderr, "Set Socket Option Failed.\n");
			return -1;
		}
        
        	/* bind socket address*/
	       	if(bind(sockfd, (struct sockaddr*) &my_addr, sizeof(struct sockaddr)) == -1){
			fprintf(stderr, "Bind Socket Failed.\n");
			return -1;
		}
		usleep(socket_wait);
		/* listen new connection*/ 
		listen(sockfd, 1);

		/* accept connection */
		clientfd = accept(sockfd, (struct sockaddr*) &client_addr, &sin_size);
		/* write message to client*/
		for(int y = 0; y < n; y++){
			write_msg = 0.25 * y * y;
			send(clientfd, &write_msg, sizeof(float), 0);
			time = rand() % 5000000;
			usleep(time);
		}

		close(clientfd);
		close(sockfd);
		exit(0);
	}
	else{
		struct sockaddr_in my_addr;
		int sockfd;
		float read_msg;
		/* create server socket */
		if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
			fprintf(stderr, "Client Socket Failed.\n");
			return -1;
		}
		my_addr.sin_family = AF_INET;
		my_addr.sin_port = htons(PORT);
		if(inet_pton(AF_INET, "127.0.0.1", &my_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported.\n");
        return -1;
    }
		bzero(&(my_addr.sin_zero), 8);

		/* keep connecting*/
		while (connect(sockfd, (struct sockaddr*) &my_addr,
				sizeof(struct sockaddr)) == -1) {
			usleep(100 * 1000);
		}
		for(int y = 0; y < n; y++){
			recv(sockfd, &read_msg, sizeof(float), 0);
			printf("The value is: %.5f\n", read_msg);
		}
		close(sockfd);
		wait(NULL);
	}
	return 0;

}
