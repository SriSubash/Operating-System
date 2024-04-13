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
typedef struct node *list;
void insert(list head);
void display(list head);
void delete1(list head);
void sort(list head);
void ttime(list head,int n);
void wtime(list head,int n);
int tsum=0,tavg=0,wsum=0,wavg=0;
int main()
{
        list head,t;
        head=(list)malloc(sizeof(struct node));
        head->next=NULL;
        char a[5];
        int x,i,n;
        printf("Enter the No of Processes :\n");
        scanf("%d",&n);
        for(i=1;i<=n;i++)
        {
            insert(head);
        }
        sort(head);
        display(head);
        ttime(head,n);
        wtime(head->next,n);
        printf("Total Waiting Time :%d\n",wsum);
        printf("Average Waiting Time :%d\n",wavg);
        printf("Total Turn Around Time :%d\n",tsum);
        printf("Average Turn Around :%d\n",tavg);
        return 0;
}
void insert(list head)
{
        list t=head,temp;
        int i;
        temp=(list)malloc(sizeof(struct node));
        printf("Enter Process Name:\n");
        scanf("%s",temp->proc);
        printf("Enter Burst Time:\n");
        scanf("%d",&temp->btime);
        temp->next=NULL;
        temp->next=t->next;
        t->next=temp;
}
void display(list head)
{
        list t=head;
        printf("Process\tBurst Time\n");
        while(t->next!=NULL)
        {
                t=t->next;
                printf("%s\t%d\n",t->proc,t->btime);
        }
}
void sort(list head)
{
        list t=head,q;
        int temp;
        char tem[5];
        for(t=head->next;t!=NULL;t=t->next)
        {
                for(q=t->next;q!=NULL;q=q->next)
                {
                        if(t->btime>q->btime)
                        {
                                temp=t->btime;
                                strcpy(tem,t->proc);
                                t->btime=q->btime;
                                strcpy(t->proc,q->proc);
                                q->btime=temp;
                                strcpy(q->proc,tem);
                        }
                }
        }
}
void delete1(list head)
{
        list t=head,k;
        while(t->next!=NULL)
        {
                k=t->next;
                t->next=t->next->next;
                free(k);
        }
}
void ttime(list head,int n)
{
        list t=head;
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
void wtime(list head,int n)
{
        list t=head;
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
