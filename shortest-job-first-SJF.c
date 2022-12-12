#include <stdio.h>

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// A function to implement bubble sort
void bubbleSortarrivaltime(int bursttime[],int arrivaltime[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++){
        for (j = 0; j < n - i - 1; j++){
            if (arrivaltime[j] > arrivaltime[j + 1]){
                swap(&bursttime[j], &bursttime[j + 1]);
                swap(&arrivaltime[j],&arrivaltime[j + 1]);
            }
            //this will sort according to burst time if arrival time is same
            else if(arrivaltime[j] == arrivaltime[j + 1]){
                if(bursttime[j] > bursttime[j + 1]){
                    swap(&bursttime[j],&bursttime[j + 1]);
                    swap(&arrivaltime[j],&arrivaltime[j + 1]);
                }
            }
        }
    }
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int findSBT(int bursttime[],int arrivaltime[],int vis[], int currtime,int n){
    int i = 0;
    int min = 10000,pos = -1; // just to set the maximum value
    for(i = 0;i < n;i++){
        if(arrivaltime[i] <= currtime){
            //if that is already not visited
            if(!vis[i]){
                if(bursttime[i] == min){
                    if(i < pos){
                        pos = i;
                    }
                }
                else if(bursttime[i] < min){
                    pos = i;
                    min = bursttime[i];
                }   
            }
        }
    }
    return pos;
}

int main(){
    int n = 0;
    int i; // for iterating
    printf("enter the number of process:");
    scanf("%d",&n);
    int bursttime[n],arrivaltime[n],completiontime[n],turnaroundtime[n],waitingtime[n],vis[n]; 
    for(i = 0;i < n;i++) vis[i] = 0;
    
    for(i = 0;i < n;i++){
        printf("enter the value of arrival time for process %d:",i + 1);
        scanf("%d",&arrivaltime[i]);
        printf("enter the value of burst time for process   %d:",i + 1);
        scanf("%d",&bursttime[i]);
    }
    bubbleSortarrivaltime(bursttime,arrivaltime,n);
    int currtime = arrivaltime[0];
    int pos = 0;
    while(pos != -1){
        printf("pos:%d bursttime: %d \n",pos,bursttime[pos]);
        vis[pos] = 1;
        currtime += bursttime[pos];
        completiontime[pos] = currtime;
        pos = findSBT(bursttime,arrivaltime,vis,currtime,n);//find shortest burst time with arrival time less than the current time
    }
    
    for(i = 0;i < n;i++){
        turnaroundtime[i] = completiontime[i] - arrivaltime[i];
        waitingtime[i] = turnaroundtime[i] - bursttime[i];
    }
    float avgtat = 0;
    for(int i = 0;i < n;i++){
        avgtat += turnaroundtime[i];
    }
    avgtat = avgtat / (float)n;
    printf("average turnaroundtime: %lf", avgtat);
    
    return 0;
}
