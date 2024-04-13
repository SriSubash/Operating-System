#include<stdio.h>
#include<stdlib.h>
struct process{
        int pid;
        int bt;
        int at;
        int wt;
        int tt;

        int et;

        int rbt;
        struct process *next;
};
struct process *front=NULL,*new,*temp=NULL;
struct process *ganttchart;
int total_burst=0,lst_arrival=0;
int p=0;
void runFirst()
{
        temp=front;
        while(temp!=NULL)
        {
                temp->rbt=temp->bt;
                temp->wt=0;
                temp->tt=0;
                temp->et=0;
                temp=temp->next;
        }
}
void insert(int b,int a){
        temp=front;
        new = (struct process *)malloc(sizeof(struct process));
        new->pid=++p;
        new->bt=b;
        new->at=a;

        new->wt=0;
        new->tt=0;
        new->et=0;
        new->rbt=b;
        new->next=NULL;
        if(front==NULL)
                front=new;
        else
        {
                while(temp->next!=NULL)
                        temp=temp->next;
                temp->next=new;
        }
}
void display(int n){
        float avgWT=0,avgTT=0;
        temp=front;
        printf("\n PROCESS ID\tBURST TIME\tARRIVAL TIME\tWAITING TIME\tTURNAROUND TIME");
        while(temp!=NULL)
        {
                printf("\n %d \t\t %d \t\t %d \t\t %d \t\t %d",temp->pid,temp->bt,temp->at,temp->wt,temp->tt);
                avgWT+=temp->wt;
                avgTT+=temp->tt;
                temp=temp->next;
        }
        printf("\nTOTAL WAITING TIME \t %f\nTOTAL TURNAROUND TIME\t%f\n",avgWT,avgTT);
        printf("Average WAITING TIME \t %f\nAverage TURNAROUND TIME\t%f\n",(avgWT/n),avgTT/n);
}
void srtf()
{
                int time=0;
                int min=total_burst;
                runFirst();
                while(time<=total_burst)
                {
                        ganttchart=NULL;
                        temp=front;
                        min=total_burst;
                        while(temp!=NULL)
                        {
                                if(temp->rbt!=0){
                                        if(time>=temp->at&&min>temp->rbt)
                                        {
                                                min=temp->rbt;
                                                ganttchart=temp;
                                        }

                                }
                                temp=temp->next;
                        }
                        if(ganttchart==NULL)
                        {
                                time++;
                        }
                        else{
                                time+=1;
                                ganttchart->rbt-=1;
                                ganttchart->wt=time-(ganttchart->at+ganttchart->bt);
                                ganttchart->tt=time-ganttchart->at;
                        }
                }

}
void main()
{
        int ch,i,n,a,b;
        printf("Enter the no of process \n");
        scanf("%d",&n);
        for(i=0;i<n;i++)
                {
                        printf("\n Enter the Burst time And Arrival Time for Process \t %d \t",p+1);
                        scanf("%d %d",&b,&a);
                        insert(b,a);
                        if(i==0||i==n-1)
                                total_burst+=a;
                        total_burst+=b;
        }
        srtf();
        display(n);
}
