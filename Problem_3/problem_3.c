#include <stdio.h>
#include <stdlib.h>

// Function to check if data can be transferred without losing any
const char* canTransferData(int n, int q, int s, int* sensor_to_queue, int* queue_capacities, int** downlink_windows) {
    // Initialize queues with 0 data
    int* queues = (int*)calloc(q, sizeof(int));
    if (queues == NULL) {
        return "impossible"; // Memory allocation failure
    }

    // Process each downlink window
    int i, j, k, l, m; // Declare loop variables outside of the for loops
    for (i = 0; i < n; i++) {
        // Transfer capacity during this window
        int transfer_capacity = downlink_windows[i][0];

        // Add data generated by sensors to their respective queues
        for (j = 0; j < s; j++) {
            int queue_index = sensor_to_queue[j] - 1; // Adjust index (1 to Q -> 0 to Q-1)
            queues[queue_index] += downlink_windows[i][j + 1];
            
            // Check if any queue exceeds its capacity
            if (queues[queue_index] > queue_capacities[queue_index]) {
                free(queues);
                return "impossible";
            }
        }

        // Sort queues in descending order to transfer from the most filled first
        for (k = 0; k < q - 1; k++) {
            for (l = k + 1; l < q; l++) {
                if (queues[k] < queues[l]) {
                    int temp = queues[k];
                    queues[k] = queues[l];
                    queues[l] = temp;
                }
            }
        }

        // Transfer data to Earth while respecting the transfer capacity
        for (m = 0; m < q && transfer_capacity > 0; m++) {
            int transfer_amount = (queues[m] < transfer_capacity) ? queues[m] : transfer_capacity;
            queues[m] -= transfer_amount;
            transfer_capacity -= transfer_amount;
        }
    }

    // Check if all queues are empty at the end
    for (i = 0; i < q; i++) {
        if (queues[i] != 0) {
            free(queues);
            return "impossible";
        }
    }

    free(queues);
    return "possible";
}

int main() {
    int n, q, s;
    // Read the input values for number of downlink windows, queues, and sensors
    scanf("%d %d %d", &n, &q, &s);

    // Array to map sensors to queues
    int* sensor_to_queue = (int*)malloc(s * sizeof(int));
    int i; // Declare loop variable outside of the for loop
    for (i = 0; i < s; i++) {
        scanf("%d", &sensor_to_queue[i]);
    }

    // Array to store capacities of each queue
    int* queue_capacities = (int*)malloc(q * sizeof(int));
    for (i = 0; i < q; i++) {
        scanf("%d", &queue_capacities[i]);
    }

    // 2D array to store downlink windows data
    int** downlink_windows = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++) {
        downlink_windows[i] = (int*)malloc((s + 1) * sizeof(int));
        int j; // Declare loop variable outside of the for loop
        for (j = 0; j < s + 1; j++) {
            scanf("%d", &downlink_windows[i][j]);
        }
    }

    // Call the function to check if transfer is possible and print the result
    const char* result = canTransferData(n, q, s, sensor_to_queue, queue_capacities, downlink_windows);
    printf("%s\n", result);

    // Free allocated memory
    free(sensor_to_queue);
    free(queue_capacities);
    for (i = 0; i < n; i++) {
        free(downlink_windows[i]);
    }
    free(downlink_windows);

    printf("Press Enter to exit...");
    scanf("%c"); 

    return 0;
}
