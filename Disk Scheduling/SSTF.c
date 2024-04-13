#include<stdio.h>
#include<stdlib.h>
struct node
{
        int data;
        struct node *next;
};
typedef struct node *list;
void insert(list head,int data)
{
        list t,temp;
        temp=(list)malloc(sizeof(struct node));
        temp->data=data;
        temp->next=NULL;
        t=head;
        while(t->next!=NULL)
            t=t->next;
        if(t!=NULL)
        {
            temp->next=t->next;
            t->next=temp;
        }
}
int main()
{
    int RQ,i,n,TotalHeadMoment=0,initial,count=0;
    list head;
    head=(list)malloc(sizeof(struct node));
    head->next=NULL;
    printf("Enter the Number of Requests :\n");
    scanf("%d",&n);
    printf("Enter the Request Sequence :\n");
    for(i=0;i<n;i++)
    {
                scanf("%d",&RQ);
                insert(head,RQ);
        }
    printf("Enter Current Arm Position :\n");
    scanf("%d",&initial);
        list t,temp;
        printf("%d",initial);
    while(count!=n)
    {
        t=head;
        int min=1000,d,index;
        i=0;
        while(t->next!=NULL)
        {
                t=t->next;
            d=abs(t->data-initial);
            if(min>d)
            {
                min=d;
                index=i;
            }
            i++;
        }
        TotalHeadMoment=TotalHeadMoment+min;
        temp=head->next;
        for(i=0;i<index;i++)
                temp=temp->next;
        initial=temp->data;
        printf("->%d",temp->data);
        temp->data=1000;
        count++;
    }

    printf("\nTotal Arm Movements : %d\n",TotalHeadMoment);
    return 0;
}
