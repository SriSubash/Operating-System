#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
        int btime;
        int ttime;
        int wtime;
        char proc[5];
        struct node *next;
};
typedef struct node *queue;
queue enqueue(queue rear,int x,char a[]);
queue dequeue(queue rear,queue front);
void display(queue front);
void ttime(queue front,int n);
void wtime(queue front,int n);
int isempty(queue front);
int tsum=0,tavg=0,wsum=0,wavg=0;
int main()
{
        queue rear,front;
        front=(queue)malloc(sizeof(struct node));
        front->next=NULL;
        rear=front;
                char a[5];
        int x,i,n;
        printf("Enter the No of Processes :\n");
        scanf("%d",&n);
        for(i=1;i<=n;i++)
        {
            printf("Enter Process Name:\n");
                scanf("%s",a);
                printf("Enter Burst Time:\n");
                scanf("%d",&x);
                        rear=enqueue(rear,x,a);
        }
        display(front);
        ttime(front,n);
        wtime(front,n);
        for(i=0;i<n;i++)
                rear=dequeue(rear,front);
        printf("Total Waiting Time :%d\n",wsum);
        printf("Average Waiting Time :%d\n",wavg);
        printf("Total Turn Around Time :%d\n",tsum);
        printf("Average Turn Around :%d\n",tavg);
        return 0;
}
queue enqueue(queue rear,int x,char a[])
{
        queue temp;
        temp=(queue)malloc(sizeof(struct node));
        temp->btime=x;
        strcpy(temp->proc,a);
        temp->next=NULL;
        temp->next=rear->next;
        rear->next=temp;
        rear=temp;
        return rear;
}
queue dequeue(queue rear,queue front)
{
        queue k;
        k=(queue)malloc(sizeof(struct node));
        if(!isempty(front))
        {
                k=front->next;
                front->next=front->next->next;
                if(front->next==NULL)
                        rear=front;
                free(k);
        }
        else
        {
                printf("QUEUE UNDERFLOW.\n");
        }
        return rear;
}
int isempty(queue front)
{
        if(front->next==NULL)
                return 1;
        else
                return 0;
}
void ttime(queue front,int n)
{
        queue t=front;
        int total=0;
        while(t->next!=NULL)
        {
            t=t->next;
                total=total+t->btime;
            tsum=tsum+total;
            t->ttime=total;
            printf("Turn Around Time of (%s)\t%d\n",t->proc,total);
        }
        tavg=tsum/n;
}
void wtime(queue front,int n)
{
        queue t=front->next;
        int total=0;
        printf("Waiting Time of (%s)\t%d\n",t->proc,total);
        while(t->next!=NULL)
        {
                total=total+t->btime;
                wsum=wsum+total;
                t=t->next;
                t->wtime=total;
                printf("Waiting Time of (%s)\t%d\n",t->proc,total);
        }
        wavg=wsum/n;
}
void display(queue front)
{
        queue t=front;
        printf("Process\tBurst Time\n");
        while(t->next!=NULL)
        {
                t=t->next;
                printf("%s\t%d\n",t->proc,t->btime);
        }
}
