#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

// Function prototypes
bool isSafe(int processes, int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES]);
bool requestResources(int processes, int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int process_id, int request[]);

int main()
{
    int processes, resources;

    // Get number of processes and resources from the user
    printf("Enter the number of processes: ");
    scanf("%d", &processes);
    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    int available[MAX_RESOURCES], max[MAX_PROCESSES][MAX_RESOURCES], allocation[MAX_PROCESSES][MAX_RESOURCES], need[MAX_PROCESSES][MAX_RESOURCES];

    // Get available resources
    printf("Enter the available resources for each resource type: \n");
    for (int i = 0; i < resources; i++)
    {
        printf("Resource %d: ", i + 1);
        scanf("%d", &available[i]);
    }

    // Get the maximum demand of each process
    printf("Enter the maximum demand matrix:\n");
    for (int i = 0; i < processes; i++)
    {
        printf("Process %d:\n", i + 1);
        for (int j = 0; j < resources; j++)
        {
            printf("Resource %d: ", j + 1);
            scanf("%d", &max[i][j]);
        }
    }

    // Get the allocation matrix
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < processes; i++)
    {
        printf("Process %d:\n", i + 1);
        for (int j = 0; j < resources; j++)
        {
            printf("Resource %d: ", j + 1);
            scanf("%d", &allocation[i][j]);
            // Need matrix is max - allocation
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Check if the system is initially in a safe state
    if (isSafe(processes, available, max, allocation, need))
    {
        printf("The system is in a safe state.\n");
    }
    else
    {
        printf("The system is NOT in a safe state.\n");
    }

    // Resource request handling
    int process_id;
    int request[MAX_RESOURCES];

    printf("Enter the process number making a resource request (1 to %d): ", processes);
    scanf("%d", &process_id);
    process_id--; // Convert to zero-indexed

    printf("Enter the resource request for process %d:\n", process_id + 1);
    for (int i = 0; i < resources; i++)
    {
        printf("Resource %d: ", i + 1);
        scanf("%d", &request[i]);
    }

    // Try to allocate requested resources
    if (requestResources(processes, available, max, allocation, need, process_id, request))
    {
        printf("The resources have been allocated successfully.\n");
    }
    else
    {
        printf("The request cannot be granted without leaving the system in an unsafe state.\n");
    }

    return 0;
}

// Function to check if the system is in a safe state
bool isSafe(int processes, int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES])
{
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int safeSequence[MAX_PROCESSES];
    int count = 0;

    // Initialize work to available resources
    for (int i = 0; i < MAX_RESOURCES; i++)
    {
        work[i] = available[i];
    }

    while (count < processes)
    {
        bool found = false;
        for (int i = 0; i < processes; i++)
        {
            if (!finish[i])
            {
                int j;
                for (j = 0; j < MAX_RESOURCES; j++)
                {
                    if (need[i][j] > work[j])
                        break;
                }

                // If all resources needed by the process are available
                if (j == MAX_RESOURCES)
                {
                    for (int k = 0; k < MAX_RESOURCES; k++)
                    {
                        work[k] += allocation[i][k];
                    }
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        // If no process was found in this cycle, the system is not in a safe state
        if (!found)
        {
            return false;
        }
    }

    printf("System is in a safe state. Safe sequence is: ");
    for (int i = 0; i < processes; i++)
    {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}

// Function to request resources for a process
bool requestResources(int processes, int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int process_id, int request[])
{
    for (int i = 0; i < MAX_RESOURCES; i++)
    {
        if (request[i] > need[process_id][i])
        {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
    }

    for (int i = 0; i < MAX_RESOURCES; i++)
    {
        if (request[i] > available[i])
        {
            printf("Error: Resources are not available.\n");
            return false;
        }
    }

    // Pretend to allocate resources temporarily
    for (int i = 0; i < MAX_RESOURCES; i++)
    {
        available[i] -= request[i];
        allocation[process_id][i] += request[i];
        need[process_id][i] -= request[i];
    }

    // Check if the system is still in a safe state after allocation
    if (isSafe(processes, available, max, allocation, need))
    {
        return true;
    }

    // If not safe, rollback the allocation
    for (int i = 0; i < MAX_RESOURCES; i++)
    {
        available[i] += request[i];
        allocation[process_id][i] -= request[i];
        need[process_id][i] += request[i];
    }

    return false;
}
