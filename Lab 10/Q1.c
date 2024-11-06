#include <stdio.h>
#include <stdlib.h>

void fifo(int *pages, int n, int frames) {
    int *frame = (int *)malloc(frames * sizeof(int));
    int index = 0, faults = 0;

    for (int i = 0; i < frames; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;
        
        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
            frame[index] = page;
            index = (index + 1) % frames;
            faults++;
        }
    }

    printf("FIFO Page Faults: %d\n", faults);
    free(frame);
}

void optimal(int *pages, int n, int frames) {
    int *frame = (int *)malloc(frames * sizeof(int));
    int faults = 0;

    for (int i = 0; i < frames; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;
        
        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int replaceIndex = -1, farthest = i + 1;

            for (int j = 0; j < frames; j++) {
                int nextIndex = -1;
                for (int k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k]) {
                        nextIndex = k;
                        break;
                    }
                }
                
                if (nextIndex == -1) {
                    replaceIndex = j;
                    break;
                } else if (nextIndex > farthest) {
                    farthest = nextIndex;
                    replaceIndex = j;
                }
            }

            frame[replaceIndex] = page;
            faults++;
        }
    }

    printf("Optimal Page Faults: %d\n", faults);
    free(frame);
}

int main() {
    int n, frames;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int *pages = (int *)malloc(n * sizeof(int));
    printf("Enter page references: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    fifo(pages, n, frames);
    optimal(pages, n, frames);

    free(pages);
    return 0;
}
