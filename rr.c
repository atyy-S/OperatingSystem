#include <stdio.h>
// Round Robin (RR)

typedef struct {
    int process_id;          // process ID
    int arrival_time;        // arrival time
    int burst_time;          // original burst time
    int remaining_time;      // remaining burst time 
    int waiting_time;        // waiting time
    int turnaround_time;     // turnaround time
    int completed_time;      // 0/1 flag 
} Process;

// Function to manually sort processes by arrival time
void sortProcessbyArrival(Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrival_time > proc[j+1].arrival_time) {
                Process temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }
}

// Preemptive Round Robin scheduling
void roundRobin(Process proc[], int n, int quantum) {

    //  quantum must be positive
    if (quantum <= 0) {
        printf("PLEASE enter positive integer.\n");
        return;
    }

    sortProcessbyArrival(proc, n);

    int time = 0;
    int completed = 0;

    printf("\n--- Execution Timeline (RR) ---\n");
    
    printf("Execution Order: ");
    while (completed < n) {
        int didSomething = 0;

        for (int i = 0; i < n; i++) {

            // Process is ready and not finished
            if (proc[i].arrival_time <= time && proc[i].remaining_time > 0) {
                didSomething = 1;

                
                printf("P%d ", proc[i].process_id);


                // If process needs more than one quantum
                if (proc[i].remaining_time > quantum) {
                    proc[i].remaining_time -= quantum;
                    time += quantum;
                } 
                else {
                    // Process finishes in this slice
                    time += proc[i].remaining_time;
                    proc[i].remaining_time = 0;

                    proc[i].completed_time = 1;
                    proc[i].turnaround_time = time - proc[i].arrival_time;
                    proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;

                    completed++;

                    printf("P%d ", proc[i].process_id);

                }
            }
        }

        // No process was ready 
        if (!didSomething) {
            time++;
        }
    }
}

// Function to print results table
void printTable(Process proc[], int n) {
    printf("\n--- Process Table ---\n");
    printf("%-12s %-12s %-12s %-12s %-12s\n",
           "Process ID", "Arrival", "Burst", "Waiting", "Turnaround");

    for (int i = 0; i < n; i++) {
        printf("%-12d %-12d %-12d %-12d %-12d\n",
               proc[i].process_id,
               proc[i].arrival_time,
               proc[i].burst_time,
               proc[i].waiting_time,
               proc[i].turnaround_time);
    }
}


int main() {

    // ensure number of processes is valid
    int n = 3;
    if (n <= 0) {
        printf("XXXX Number of processes must be greater than zero.\n");
        return 1;
    }

    // Test case 
    Process proc[] = {
        {1, 0, 24, 24, 0, 0, 0},
        {2, 0, 3, 3, 0, 0, 0},
        {3, 0, 3, 3, 0, 0, 0}
    };

    int quantum = 4;  

    roundRobin(proc, n, quantum);
    printTable(proc, n);

    return 0;
}
