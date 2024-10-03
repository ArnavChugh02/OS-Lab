#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_STRINGS 100
#define MAX_LENGTH 100

void bubble_sort(char *arr[], int n);
void quick_sort(char *arr[], int low, int high);
int partition(char *arr[], int low, int high);
void swap(char **a, char **b);

int main()
{
    int n;
    char *strings[MAX_STRINGS];

    printf("Enter the number of strings: ");
    scanf("%d", &n);

    if (n > MAX_STRINGS)
    {
        fprintf(stderr, "Number of strings exceeds the maximum limit.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        strings[i] = (char *)malloc(MAX_LENGTH * sizeof(char));
        if (strings[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed.\n");
            return 1;
        }
        printf("Enter string %d: ", i + 1);
        scanf("%s", strings[i]);
    }

    pid_t pid1 = fork();
    if (pid1 < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid1 == 0)
    {
        printf("Child 1 (Bubble Sort) sorting:\n");
        bubble_sort(strings, n);
        for (int i = 0; i < n; i++)
        {
            printf("%s\n", strings[i]);
        }
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid2 == 0)
    {
        printf("Child 2 (Quick Sort) sorting:\n");
        quick_sort(strings, 0, n - 1);
        for (int i = 0; i < n; i++)
        {
            printf("%s\n", strings[i]);
        }
        exit(0);
    }

    int status;
    pid_t finished_pid = wait(&status);
    if (finished_pid == pid1)
    {
        printf("Child 1 has terminated.\n");
    }
    else if (finished_pid == pid2)
    {
        printf("Child 2 has terminated.\n");
    }

    // Clean up
    for (int i = 0; i < n; i++)
    {
        free(strings[i]);
    }

    return 0;
}

void bubble_sort(char *arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(arr[j], arr[j + 1]) > 0)
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void quick_sort(char *arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int partition(char *arr[], int low, int high)
{
    char *pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++)
    {
        if (strcmp(arr[j], pivot) < 0)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void swap(char **a, char **b)
{
    char *temp = *a;
    *a = *b;
    *b = temp;
}