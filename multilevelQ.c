#include <stdio.h>

#define MAX 100

struct process
{
    int id;
    int at;
    int bt;
    int ct;
    int wt;
    int tat;
    int queue;
    int done;
};

int gantt[100];
int times[101];
int k = 0;

void sortByArrival(struct process p[], int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(p[j].at > p[j+1].at)
            {
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void runFCFS(struct process p[], int n, int *currentTime)
{
    for(int i=0;i<n;i++)
    {
        if(*currentTime < p[i].at)
            *currentTime = p[i].at;

        p[i].ct = *currentTime + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        *currentTime = p[i].ct;
        p[i].done = 1;

        gantt[k] = p[i].id;
        times[k+1] = p[i].ct;
        k++;
    }
}

int main()
{
    int n;

    struct process all[MAX];
    struct process sysQueue[MAX];
    struct process userQueue[MAX];

    int sysCount = 0;
    int userCount = 0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        all[i].id = i;

        printf("Enter AT, BT and Queue(0-System,1-User) for P%d: ",i);
        scanf("%d%d%d",
              &all[i].at,
              &all[i].bt,
              &all[i].queue);

        all[i].done = 0;

        if(all[i].queue == 0)
            sysQueue[sysCount++] = all[i];
        else
            userQueue[userCount++] = all[i];
    }

    sortByArrival(sysQueue, sysCount);
    sortByArrival(userQueue, userCount);

    int currentTime = 0;

    times[0] = 0;

    runFCFS(sysQueue, sysCount, &currentTime);
    runFCFS(userQueue, userCount, &currentTime);

    for(int i=0;i<sysCount;i++)
        all[sysQueue[i].id] = sysQueue[i];

    for(int i=0;i<userCount;i++)
        all[userQueue[i].id] = userQueue[i];

    printf("\nID\tAT\tBT\tQ\tCT\tWT\tTAT\n");

    float awt = 0;
    float atat = 0;

    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               all[i].id,
               all[i].at,
               all[i].bt,
               all[i].queue,
               all[i].ct,
               all[i].wt,
               all[i].tat);

        awt += all[i].wt;
        atat += all[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f\n", awt/n);
    printf("Average Turnaround Time = %.2f\n", atat/n);

    printf("\nGantt Chart:\n");

    for(int i=0;i<k;i++)
        printf("|P%d", gantt[i]);

    printf("|\n");

    printf("%d", times[0]);

    for(int i=1;i<=k;i++)
        printf(" %d", times[i]);

    printf("\n");

    return 0;
}
