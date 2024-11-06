#include <stdio.h>
#include <stdlib.h>

void lru(int *pages, int n, int frames) {
    int *frame = (int *)malloc(frames * sizeof(int));
    int *recent = (int *)malloc(frames * sizeof(int));
    int faults = 0;

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;  // Initialize frames as empty
        recent[i] = -1; // Initialize recent usage tracking
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0, leastUsedIndex = 0;

        // Check if page is already in frame
        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                found = 1;
                recent[j] = i; // Update recent usage for the found page
                break;
            }
        }

        // If page not found, replace the least recently used page
        if (!found) {
            faults++;

            // Find the least recently used frame
            for (int j = 1; j < frames; j++) {
                if (recent[j] < recent[leastUsedIndex]) {
                    leastUsedIndex = j;
                }
            }

            // Replace the least recently used page
            frame[leastUsedIndex] = page;
            recent[leastUsedIndex] = i; // Update recent usage
        }
    }

    printf("LRU Page Faults: %d\n", faults);

    free(frame);
    free(recent);
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

    lru(pages, n, frames);

    free(pages);
    return 0;
}
