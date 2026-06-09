#define max 10
#include <stdio.h>

struct process {
    int at, bt;
    int ct, wt, tat;
};

void FCFS(struct process p[], int n)
{
    int t = 0;
    float total_wt = 0, total_tat = 0;

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(p[i].at > p[j].at)
            {
                struct process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    for(int i = 0; i < n; i++)
    {
        if(t < p[i].at)
            t = p[i].at;

        p[i].ct = t + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        total_wt += p[i].wt;
        total_tat += p[i].tat;

        t = p[i].ct;
    }

    printf("\nAT\tBT\tCT\tWT\tTAT\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n",
               p[i].at, p[i].bt,
               p[i].ct, p[i].wt, p[i].tat);
    }

    printf("\nAverage WT = %.2f", total_wt/n);
    printf("\nAverage TAT = %.2f\n", total_tat/n);
}

int main()
{
    int n;
    struct process p[max];

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        printf("AT of P%d: ",i);
        scanf("%d",&p[i].at);

        printf("BT of P%d: ",i);
        scanf("%d",&p[i].bt);
    }

    FCFS(p,n);

    return 0;
}
