#include <stdio.h>

typedef struct {
    int process_id;          // process ID
    int arrival_time;      // arrival time
    int burst_time;        // original burst time
    int remaining_time;    // remaining burst time 
    int waiting_time;      // waiting time
    int turnaround_time;   // turnaround time
    int completed_time;    // 0/1 flag 
} Process;


//Function so manually sort process by arrival time
void sortProcessbyArrival(Process proc[],int n){
    for (int i=0;i <n-1;i++){
        for (int j=0; j<n-i-1; j++) { 
            if (proc[j].arrival_time > proc[j+1].arrival_time) { 
                //swap the process
                Process temp = proc[j]; 
                proc[j] = proc[j+1]; 
                proc[j+1] = temp; 
            } 
        }
    }
}

//Funtion for SJF: Shortest Remaining Time First
void sjt(Process proc[], int n) {
    sortProcessbyArrival(proc, n);

    int time = 0;
    int completed = 0;

    printf("\n--- Execution Timeline ---\n");

    while (completed < n) {

        // find shortest remaining job
        int idx = -1;
        int min = 999999;

        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= time &&
                proc[i].completed_time == 0 &&
                proc[i].remaining_time < min) {

                min = proc[i].remaining_time;
                idx = i;
            }
        }

        //no process is ready to run at the current time.
        if (idx == -1) {
            time++;
            continue;
        }

        // first time starting
        if (proc[idx].remaining_time == proc[idx].burst_time) {
            printf("Time %d: Process %d starts\n", time, proc[idx].process_id);
        }

        proc[idx].remaining_time--;
        time++;

        if (proc[idx].remaining_time == 0) {
            proc[idx].completed_time = 1;
            proc[idx].turnaround_time = time - proc[idx].arrival_time;
            proc[idx].waiting_time = proc[idx].turnaround_time - proc[idx].burst_time;

            printf("Time %d: Process %d completes\n", time, proc[idx].process_id);

            completed++;
        }
    }
}

//Function for print table

void printTable(Process proc[], int n) {
    printf("\n--- Process Table ---\n");
    printf("Process ID\tArrival Time\tBurst Time \tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("\t%d\t\t\t%d\t\t\t\t%d\t\t\t%d\t\t\t\t\t%d\n",
               proc[i].process_id,
               proc[i].arrival_time,
               proc[i].burst_time,
               proc[i].waiting_time,
               proc[i].turnaround_time);
    }
}
int main() {
    Process proc[] = {
        {1, 0, 8, 8, 0, 0, 0},
        {2, 1, 4, 4, 0, 0, 0},
        {3, 2, 9, 9, 0, 0, 0},
        {4, 3, 5, 5, 0, 0, 0}
    };

    int n = sizeof(proc) / sizeof(proc[0]);

    sjt(proc, n);
    printTable(proc, n);

    return 0;
}
