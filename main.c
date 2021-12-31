#import <stdio.h>
#import <stdlib.h>
#import <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>

#define READ 0
#define WRITE 1

int main() {
    while (1) {
        int pipe1[2];
        int pipe2[2];
        pipe(pipe1);
        pipe(pipe2);
        int f = fork();
        if (f) {
            close(pipe1[READ]);
            char input[100];
            printf("input message: ");
            fgets(input, sizeof(input), stdin);
            write(pipe1[WRITE], input, strlen(input)+1);
            close(pipe1[WRITE]);

            wait(NULL);

            close(pipe2[WRITE]);
            read(pipe2[READ], input, 100);
            printf("response: %s\n", input);
            close(pipe2[READ]);
        } else {
            close(pipe1[WRITE]);

            char response[100];
            read(pipe1[READ], response, 100);

            int i;
            for (i = 0; i < strlen(response); i++) {
                response[i] = toupper(response[i]);
            }

            close(pipe1[READ]);
            close(pipe2[READ]);
            write(pipe2[WRITE], response, strlen(response)+1);
            close(pipe2[WRITE]);
            exit(0);
        }
    }
    return 0;
}