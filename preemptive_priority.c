#include <stdio.h>

struct process
{
    int at, bt, ct, wt, tat, rt, pr, done;
};

void preemp_priority(struct process p[], int n)
{
    int completed = 0, t = 0;
    float awt = 0, atat = 0;

    int gantt[1000];
    int k = 0;

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
                    if (p[i].rt < p[idx].rt)
                        idx = i;
                }
            }
        }

        if (idx != -1)
        {
            gantt[k++] = idx;

            p[idx].rt--;
            t++;

            if (p[idx].rt == 0)
            {
                p[idx].ct = t;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                awt += p[idx].wt;
                atat += p[idx].tat;

                p[idx].done = 1;
                completed++;
            }
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
        printf("|P%d", gantt[i]);

    printf("|\n0");

    for (int i = 1; i <= k; i++)
        printf(" %d", i);

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
        printf("Enter AT, BT and Priority for P%d: ", i);
        scanf("%d%d%d", &p[i].at, &p[i].bt, &p[i].pr);

        p[i].rt = p[i].bt;
        p[i].done = 0;
    }

    preemp_priority(p, n);

    return 0;
}
