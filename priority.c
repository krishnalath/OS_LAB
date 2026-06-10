#include <stdio.h>
struct process
{
    int at, bt, ct, wt, tat, done, pr;
};

void priority(struct process p[], int n)
{
    int completed = 0, t = 0;
    float awt = 0, atat = 0;

    int gantt[100];
    int times[101];
    int k = 0;

    times[0] = 0;

    while (completed < n)
    {
        int idx = -1;
        int highest_pr = 9999;

        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= t && p[i].done == 0)
            {
                if (p[i].pr < highest_pr)
                {
                    highest_pr = p[i].pr;
                    idx = i;
                }
                else if (p[i].pr == highest_pr)
                {
                    if (p[i].at < p[idx].at)
                        idx = i;
                }
            }
        }

        if (idx != -1)
        {
            p[idx].ct = t + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            awt += p[idx].wt;
            atat += p[idx].tat;

            p[idx].done = 1;
            completed++;

            gantt[k] = idx;
            times[k + 1] = p[idx].ct;
            k++;

            t = p[idx].ct;
        }
        else
        {
            t++;
        }
    }

    printf("\nID\tAT\tBT\tPR\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++)
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

    printf("\nAverage Waiting Time = %.2f\n", awt / n);
    printf("Average Turnaround Time = %.2f\n", atat / n);

    printf("\nGantt Chart:\n");

    for (int i = 0; i < k; i++)
        printf("| P%d ", gantt[i]);

    printf("|\n");

    printf("%d", times[0]);

    for (int i = 1; i <= k; i++)
        printf("    %d", times[i]);

    printf("\n");
}

int main()
{
    int n;
    struct process p[100];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter Arrival Time, Burst Time and Priority for P%d: ", i);
        scanf("%d%d%d",
              &p[i].at,
              &p[i].bt,
              &p[i].pr);

        p[i].done = 0;
    }

    priority(p, n);

    return 0;
}
