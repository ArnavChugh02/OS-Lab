#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure to represent a process
typedef struct
{
    int pid;            // Process ID
    int burst_time;     // Burst time
    int arrival_time;   // Arrival time
    int priority;       // Priority
    int remaining_time; // Remaining time for SJF
} Process;

void preemptive_sjf(Process processes[], int n);
void round_robin(Process processes[], int n, int quantum);
void non_preemptive_priority(Process processes[], int n);
void sort_by_arrival_time(Process processes[], int n);

int main()
{
    int choice, n, quantum;
    Process processes[MAX];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter process ID, arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d%d%d%d", &processes[i].pid, &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time; // Initialize remaining time
    }

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Preemptive Shortest Job First (SJF)\n");
        printf("2. Round Robin (RR)\n");
        printf("3. Non-preemptive Priority Scheduling\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            preemptive_sjf(processes, n);
            break;
        case 2:
            printf("Enter time quantum for Round Robin: ");
            scanf("%d", &quantum);
            round_robin(processes, n, quantum);
            break;
        case 3:
            non_preemptive_priority(processes, n);
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to sort processes by arrival time
void sort_by_arrival_time(Process processes[], int n)
{
    Process temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].arrival_time > processes[j + 1].arrival_time)
            {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Preemptive Shortest Job First (SJF)
void preemptive_sjf(Process processes[], int n)
{
    int time = 0, completed = 0, min_time, shortest = -1;
    int finish_time, waiting_time = 0, turnaround_time = 0;
    int check = 0;

    sort_by_arrival_time(processes, n);

    while (completed != n)
    {
        min_time = 9999;

        for (int i = 0; i < n; i++)
        {
            if ((processes[i].arrival_time <= time) && (processes[i].remaining_time < min_time) && (processes[i].remaining_time > 0))
            {
                min_time = processes[i].remaining_time;
                shortest = i;
                check = 1;
            }
        }

        if (check == 0)
        {
            time++;
            continue;
        }

        processes[shortest].remaining_time--;

        if (processes[shortest].remaining_time == 0)
        {
            completed++;
            finish_time = time + 1;

            waiting_time += finish_time - processes[shortest].burst_time - processes[shortest].arrival_time;
            turnaround_time += finish_time - processes[shortest].arrival_time;
        }

        time++;
    }

    printf("Average Waiting Time: %.2f\n", (float)waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)turnaround_time / n);
}

// Round Robin (RR)
void round_robin(Process processes[], int n, int quantum)
{
    int time = 0, completed = 0, waiting_time = 0, turnaround_time = 0;
    int remaining_bt[MAX];

    for (int i = 0; i < n; i++)
        remaining_bt[i] = processes[i].burst_time;

    while (completed != n)
    {
        int flag = 0;

        for (int i = 0; i < n; i++)
        {
            if (remaining_bt[i] > 0)
            {
                flag = 1;

                if (remaining_bt[i] > quantum)
                {
                    time += quantum;
                    remaining_bt[i] -= quantum;
                }
                else
                {
                    time += remaining_bt[i];
                    waiting_time += time - processes[i].burst_time - processes[i].arrival_time;
                    turnaround_time += time - processes[i].arrival_time;
                    remaining_bt[i] = 0;
                    completed++;
                }
            }
        }

        if (flag == 0)
            break;
    }

    printf("Average Waiting Time: %.2f\n", (float)waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)turnaround_time / n);
}

// Non-preemptive Priority Scheduling
void non_preemptive_priority(Process processes[], int n)
{
    int completed = 0, time = 0, waiting_time = 0, turnaround_time = 0;

    sort_by_arrival_time(processes, n);

    while (completed != n)
    {
        int highest_priority = 9999, idx = -1;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= time && processes[i].priority < highest_priority && processes[i].burst_time > 0)
            {
                highest_priority = processes[i].priority;
                idx = i;
            }
        }

        if (idx != -1)
        {
            time += processes[idx].burst_time;
            waiting_time += time - processes[idx].burst_time - processes[idx].arrival_time;
            turnaround_time += time - processes[idx].arrival_time;
            processes[idx].burst_time = 0;
            completed++;
        }
        else
        {
            time++;
        }
    }

    printf("Average Waiting Time: %.2f\n", (float)waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)turnaround_time / n);
}
