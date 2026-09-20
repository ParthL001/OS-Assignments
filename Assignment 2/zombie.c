#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Fork failed!\n");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child process started.\n");
        printf("Child PID: %d\n", getpid());

        sleep(2);

        printf("Child process exiting...\n");
        exit(0);
    }
    else
    {
        printf("Parent process started.\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        printf("Parent sleeping for 20 seconds...\n");

        sleep(20);

        printf("Parent process exiting...\n");
    }

    return 0;
}
