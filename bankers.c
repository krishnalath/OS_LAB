#include <stdio.h>
#include <stdbool.h>

#define max 10

int main() {
    int n,m;
    int allocation[max][max],max_demand[max][max],need[max][max],available[max];
    int safeSeq[max];
    bool finish[max]={false};
    int work[max];
    printf("Enter number of processes and resources: ");
    scanf("%d%d",&n,&m);
    printf("Enter allocation matrix: ");
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&allocation[i][j]);
            
    printf("Enter MAX matrix: ");
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&max_demand[i][j]);
            
    printf("Enter available vector: ");
    for(int i=0;i<m;i++)
        scanf("%d",&available[i]);
        
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            need[i][j] = max_demand[i][j]-allocation[i][j];
            
    for(int i=0;i<m;i++)
        work[i]=available[i];
        
    int count=0;
    while(count<n){
        bool found=false;
        for(int i=0;i<n;i++){
            if(!finish[i]){
                bool canFinish = true;
                for(int j=0;j<m;j++){
                    if(need[i][j]>work[j]){
                        canFinish=false;
                        break;
                    }
                }
                if(canFinish){
                    for(int k=0;k<m;k++)
                        work[k]+=allocation[i][k];
                    safeSeq[count]=i;
                    finish[i]=true;
                    count++;
                    found=true;
                }
            }
        }
        if(!found) break;
    }
    bool safe=true;
    for(int i=0;i<n;i++){
        if(!finish[i]){
            safe=false;
            break;
        }
    }
    if(safe){
        printf("\nSystem is in safe state:\n");
        printf("Safe sequence:\n");
        for(int i=0;i<n;i++)
            printf("%d ",safeSeq[i]);
    }
    else{
    printf("\nSystem is NOT in a safe state.\n");
}

    int process;
    int request[max];
    printf("Enter process number making request: ");
    scanf("%d",&process);
    printf("enter request vector: ");
    for(int i=0;i<m;i++)
        scanf("%d",&request[i]);
    for(int i=0;i<m;i++){
        if(request[i]>need[process][i]){
            printf("\nError: Request exceeds process need.\n");
            return 0;
        }
    }
    for(int i=0;i<m;i++){
        if(request[i]>available[i]){
            printf("\nNot available , process must wait\n");
            return 0;
        }
    }
    for(int i=0;i<m;i++){
        available[i]-=request[i];
        allocation[process][i]+=request[i];
        need[process][i]-=request[i];
    }
    for(int i=0;i<n;i++)
        finish[i]=false;
    for(int i=0;i<m;i++)
        work[i]=available[i];
    count=0;
    while(count<n){
        bool found=false;
        for(int i=0;i<n;i++){
            if(!finish[i]){
                bool canFinish=true;
                for(int j=0;j<m;j++){
                    if(need[i][j]>work[j]){
                        canFinish=false;
                        break;
                    }
                }
                if(canFinish){
                    for(int k=0;k<m;k++)
                        work[k]+=allocation[i][k];
                    safeSeq[count]=i;
                    finish[i]=true;
                    count++;
                    found=true;
                }
            }
        }
        if(!found) break;
    }
    safe=true;
    for(int i=0;i<n;i++){
        if(!finish[i]){
            safe=false;
            break;
        }
    }
    if (safe)
    {
        printf("\nRequest can be GRANTED.\n");
        printf("New Safe Sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
        printf("\n");
    }
    else
    {
        printf("\nRequest CANNOT be granted.\n");
        printf("System will enter unsafe state.\n");
    }

    return 0;
}
