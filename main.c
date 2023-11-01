/*Write a program for multilevel queue scheduling algorithm. There must be three queues generated. There must be specific range of priority associated with every queue. Now prompt the user to enter number of processes along with their priority and burst time. Each process must occupy the respective queue with specific priority range according to its priority. Apply Round robin algorithm with quantum time 4 on queue with highest priority range. Apply priority scheduling algorithm on the queue with medium range of priority and First come first serve algorithm on the queue with lowest range of priority. Each and every queue should get a quantum time of 10 seconds. Cpu will keep on shifting between queues after every 10 seconds  i.e. to apply round robin algorithm OF 10 seconds on over all structure.
Calculate Waiting time and turnaround time for every process. The input for number of processes  should be given by the user.
*/
#include<stdio.h>

struct process {
    int pid;
    int bt;
    int priority;
};

void findWaitingTime(struct process proc[], int n, int wt[]) {
    wt[0] = 0;
    for (int i = 1; i < n ; i++ )
        wt[i] = proc[i-1].bt + wt[i-1];
}

void findTurnAroundTime(struct process proc[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n ; i++)
        tat[i] = proc[i].bt + wt[i];
}

void findavgTime(struct process proc[], int n) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaitingTime(proc, n, wt);
    findTurnAroundTime(proc, n, wt, tat);

    printf("Processes   Burst Time   Waiting Time   Turnaround Time\n");
    for (int i=0; i<n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].bt, wt[i], tat[i]);
    }

    printf("Average waiting time: %.3f", (float)total_wt / (float)n);
    printf("\nAverage turnaround time: %.3f", (float)total_tat / (float)n);
}

void priorityScheduling(struct process proc[], int n) {
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            if(proc[i].priority > proc[j].priority) {
                struct process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    printf("Order of processes after priority scheduling: \n");
    for(int i=0; i<n; i++)
        printf("%d ", proc[i].pid);

    printf("\n");

    findavgTime(proc, n);
}

int main() {
    struct process proc[20];
    int n, i;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time and priority for each process\n");
    for(i=0; i<n; i++) {
        printf("Process[%d]\n", i+1);
        printf("Burst Time:");
        scanf("%d", &proc[i].bt);
        printf("Priority:");
        scanf("%d", &proc[i].priority);
        proc[i].pid = i+1;
        printf("\n");
    }

    priorityScheduling(proc, n);

    return 0;
}