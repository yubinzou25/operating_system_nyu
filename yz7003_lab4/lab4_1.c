#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid1 = 33, pid2 = 22, pid3 = 11;
    pid1 = fork();
    printf("First fork done: %d, %d, %d\n", pid1, pid2, pid3);
    if (pid1 > 0) {
        pid2 = fork();
    }
    printf("Second fork done: %d, %d, %d\n", pid1, pid2, pid3);
    if (pid2 == 0){
    pid3 = fork();
    }
    printf("Third fork done: %d, %d, %d\n", pid1, pid2, pid3);

    return 0;
}
