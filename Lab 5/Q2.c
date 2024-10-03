#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Enter more strings");
        exit(EXIT_FAILURE);
    }

    int count = argc - 1;
    char *agv[argc - 1];
    for (int i = 0; i < count; i++)
    {
        agv[i] = argv[i + 1];
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count - i - 1; j++)
            {
                if (strcmp(agv[j], agv[j + 1]) > 0)
                {

                    char *temp = agv[j];
                    agv[j] = agv[j + 1];
                    agv[j + 1] = temp;
                }
            }
        }
        printf("After sorting:\n");
        for (int i = 0; i < count; i++)
        {
            printf("%s\n", agv[i]);
        }
        exit(EXIT_SUCCESS);
    }
    else
    {

        wait(NULL);
        printf("Before sorting:\n");
        for (int i = 0; i < count; i++)
        {
            printf("%s\n", argv[i + 1]);
        }
    }

    return 0;
}