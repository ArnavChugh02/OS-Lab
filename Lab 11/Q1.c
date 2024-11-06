#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void print_head_movement(int *movement, int count) {
    printf("Head movement: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", movement[i]);
    }
    printf("\n");
}

void sstf(int *requests, int n, int head) {
    int *visited = (int *)calloc(n, sizeof(int));
    int *movement = (int *)malloc((n + 1) * sizeof(int));
    int total_distance = 0, move_count = 0;

    movement[move_count++] = head;

    for (int i = 0; i < n; i++) {
        int min_distance = INT_MAX, closest_index = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && abs(requests[j] - head) < min_distance) {
                min_distance = abs(requests[j] - head);
                closest_index = j;
            }
        }

        visited[closest_index] = 1;
        total_distance += min_distance;
        head = requests[closest_index];
        movement[move_count++] = head;
    }

    printf("SSTF Total Distance: %d\n", total_distance);
    print_head_movement(movement, move_count);
    free(visited);
    free(movement);
}

void scan(int *requests, int n, int head, int disk_size) {
    int *movement = (int *)malloc((n + 2) * sizeof(int));
    int total_distance = 0, move_count = 0;

    requests[n] = 0;
    requests[n + 1] = disk_size - 1;
    n += 2;

    movement[move_count++] = head;
    for (int i = 0; i < n; i++) if (requests[i] > head) break;

    for (int j = i - 1; j >= 0; j--) {
        total_distance += abs(head - requests[j]);
        head = requests[j];
        movement[move_count++] = head;
    }

    for (int j = i; j < n; j++) {
        total_distance += abs(head - requests[j]);
        head = requests[j];
        movement[move_count++] = head;
    }

    printf("SCAN Total Distance: %d\n", total_distance);
    print_head_movement(movement, move_count);
    free(movement);
}

void cscan(int *requests, int n, int head, int disk_size) {
    int *movement = (int *)malloc((n + 2) * sizeof(int));
    int total_distance = 0, move_count = 0;

    requests[n] = 0;
    requests[n + 1] = disk_size - 1;
    n += 2;

    movement[move_count++] = head;
    for (int i = 0; i < n; i++) if (requests[i] > head) break;

    for (int j = i; j < n; j++) {
        total_distance += abs(head - requests[j]);
        head = requests[j];
        movement[move_count++] = head;
    }

    head = 0;
    movement[move_count++] = head;

    for (int j = 0; j < i; j++) {
        total_distance += abs(head - requests[j]);
        head = requests[j];
        movement[move_count++] = head;
    }

    printf("C-SCAN Total Distance: %d\n", total_distance);
    print_head_movement(movement, move_count);
    free(movement);
}

void clook(int *requests, int n, int head) {
    int *movement = (int *)malloc((n + 1) * sizeof(int));
    int total_distance = 0, move_count = 0;

    movement[move_count++] = head;

    for (int i = 0; i < n; i++) if (requests[i] > head) break;

    for (int j = i; j < n; j++) {
        total_distance += abs(head - requests[j]);
        head = requests[j];
        movement[move_count++] = head;
    }

    for (int j = 0; j < i; j++) {
        total_distance += abs(head - requests[j]);
        head = requests[j];
        movement[move_count++] = head;
    }

    printf("C-LOOK Total Distance: %d\n", total_distance);
    print_head_movement(movement, move_count);
    free(movement);
}

void sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    int n, head, disk_size, choice;

    printf("Enter number of requests: ");
    scanf("%d", &n);
    int *requests = (int *)malloc((n + 2) * sizeof(int));

    printf("Enter requests: ");
    for (int i = 0; i < n; i++) scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    sort(requests, n);

    do {
        printf("\nDisk Scheduling Algorithms:\n1. SSTF\n2. SCAN\n3. C-SCAN\n4. C-LOOK\n5. Exit\nChoose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: sstf(requests, n, head); break;
            case 2: scan(requests, n, head, disk_size); break;
            case 3: cscan(requests, n, head, disk_size); break;
            case 4: clook(requests, n, head); break;
            case 5: printf("Exiting program.\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    free(requests);
    return 0;
}
