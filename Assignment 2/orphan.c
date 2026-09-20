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
        printf("Initial Parent PID: %d\n", getppid());

        sleep(10);

        printf("\nParent has terminated.\n");
        printf("Child is now an orphan.\n");
        printf("New Parent PID: %d\n", getppid());

        sleep(5);

        printf("Child process exiting...\n");
    }
    else
    {
        printf("Parent process started.\n");
        printf("Parent PID: %d\n", getpid());

        sleep(2);

        printf("Parent process exiting...\n");
        exit(0);
    }

    return 0;
}
