#define max 10
#include <stdio.h>

struct process {
    int at;
    int bt;
    int rt;
    int pr;
    int wt;
    int tat;
    int ct;
    int done;
};

void Priority_Preemptive(struct process p[], int n)
{
    int completed = 0;
    int t = 0;
    float total_wt = 0, total_tat = 0;

    while(completed < n)
    {
        int idx = -1;
        int highest_pr = 9999;

        // Find highest priority process among arrived processes
        for(int i = 0; i < n; i++)
        {
            if(p[i].at <= t && p[i].done == 0)
            {
                if(p[i].pr < highest_pr)
                {
                    highest_pr = p[i].pr;
                    idx = i;
                }
                else if(p[i].pr == highest_pr)
                {
                    // Tie-breaker: smaller remaining time
                    if(p[i].rt < p[idx].rt)
                    {
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1)
        {
            p[idx].rt--;
            t++;

            if(p[idx].rt == 0)
            {
                p[idx].ct = t;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                total_wt += p[idx].wt;
                total_tat += p[idx].tat;

                p[idx].done = 1;
                completed++;
            }
        }
        else
        {
            t++; // CPU Idle
        }
    }

    printf("\nID\tAT\tBT\tPR\tCT\tWT\tTAT\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i,
               p[i].at,
               p[i].bt,
               p[i].pr,
               p[i].ct,
               p[i].wt,
               p[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt/n);
    printf("Average Turnaround Time: %.2f\n", total_tat/n);
}

int main()
{
    int n;
    struct process p[max];

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(int i = 0; i < n; i++)
    {
        printf("Enter Arrival Time for P%d: ",i);
        scanf("%d",&p[i].at);

        printf("Enter Burst Time for P%d: ",i);
        scanf("%d",&p[i].bt);

        printf("Enter Priority for P%d: ",i);
        scanf("%d",&p[i].pr);

        p[i].rt = p[i].bt;
        p[i].done = 0;
    }

    Priority_Preemptive(p,n);

    return 0;
}
