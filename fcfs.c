// Online C compiler to run C program online
#include <stdio.h>
struct process{
  int id,at,bt,ct,wt,tat;  
};

void sort(struct process p[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(p[j].at>p[j+1].at){
                struct process temp = p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

void fcfs(struct process p[],int n){
    int t=0;
    float tWT=0,tTAT=0;
    for(int i=0;i<n;i++){
        if(p[i].at>t)
            t=p[i].at;
        p[i].ct = t+p[i].bt;
        p[i].tat = p[i].ct-p[i].at;
        p[i].wt = p[i].tat-p[i].bt;
        t=p[i].ct;
    }
    printf("\n%-5s%-5s%-5s%-5s%-8s%-8s\n", "PID", "AT", "BT", "CT", "WT", "TAT");
    for (int i=0; i<n; i++) {
        printf("%-5d%-5d%-5d%-5d%-8.2f%-8.2f\n",
               i, p[i].at, p[i].bt, p[i].ct,
               (float)p[i].wt, (float)p[i].tat);
        tWT+=p[i].wt;
        tTAT+=p[i].tat;
    }
    tWT/=n;
    tTAT/=n; printf("\nAverage Waiting Time = %.2f", tWT);
    printf("\nAverage Turnaround Time = %.2f\n", tTAT);
}

void ganttChart(struct process p[], int n)
{
    printf("\nGantt Chart:\n");

    for(int i=0;i<n;i++)
        printf("| P%d ", i);

    printf("|\n");

    printf("0");

    for(int i=0;i<n;i++)
        printf("    %d", p[i].ct);

    printf("\n");
}

int main() {
    int n;
    struct process p[100];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i=0; i<n; i++) {
        printf("Enter arrival time for process %d: ", i);
        scanf("%d", &p[i].at);
        printf("Enter burst time for process %d: ", i);
        scanf("%d", &p[i].bt);
    }
    sort(p, n); 
    fcfs(p, n);
    ganttChart(p,n);
    return 0;
}
