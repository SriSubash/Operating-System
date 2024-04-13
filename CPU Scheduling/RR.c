#include<stdio.h>

void roundRobin(int processes[], int n, int burstTime[],int quantum) {
    int waitingTime[n], turnaroundTime[n], remainingTime[n];
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    int currentTime = 0, completed = 0, i;

    for (i = 0; i < n; i++) {
        remainingTime[i] = burstTime[i];
        waitingTime[i] = 0;
    }

    while (completed != n) {
        for (i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {
                // Process has remaining burst time
                if (remainingTime[i] > quantum) {
                    // Process executes for time quantum
                    currentTime += quantum;
                    remainingTime[i] -= quantum;
                } else {
                    // Process executes for remaining burst time
                    currentTime += remainingTime[i];
                    waitingTime[i] = currentTime - burstTime[i];
                    remainingTime[i] = 0;
                    completed++;
                }
            }
        }
    }

    for (i = 0; i < n; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i], burstTime[i], waitingTime[i], turnaroundTime[i]);
    }
    printf("Average Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}

int main() {
        int quantum,num,i;
        printf("Enter the No of Processes : \n");
        scanf("%d",&num);
        printf("Enter the Time Quantum : \n");
        scanf("%d",&quantum);
    int processes[10],burstTime[10];
        for(i=0;i<num;i++)
        {
                printf("Enter the Process and Burst Time : \n");
                scanf("%d",&processes[i]);
                scanf("%d",&burstTime[i]);
        }

    roundRobin(processes, num, burstTime,quantum);

    return 0;
}
