#include<stdio.h>
#include<stdlib.h>
struct node
{
        int data;
        struct node *next;
        struct node *prev;
};
typedef struct node *list;
void insert(list head,int data)
{
        list t=head,temp;
        temp=(list)malloc(sizeof(struct node));
        temp->data=data;
        temp->next=temp->prev=NULL;
        while(t->next!=NULL)
                t=t->next;
        if(t!=NULL)
        {
                temp->next=t->next;
                t->next=temp;
                temp->prev=t;
        }
}
void sort(list head)
{
        list t=head,q;
        int temp;
        for(t=head->next;t!=NULL;t=t->next)
        {
                for(q=t->next;q!=NULL;q=q->next)
                {
                        if(t->data>q->data)
                        {
                                temp=t->data;
                                t->data=q->data;
                                q->data=temp;
                        }
                }
        }
}
int main()
{
        int RQ,i,j,n,TotalHeadMoment=0,initial,move;
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
        printf("Enter the Arm Movement Direction :\n1->High\n0->Low\n");
        scanf("%d",&move);
        sort(head);
        list t=head;
        int index,k=0;
        while(t->next!=NULL)
        {
                t=t->next;
                if(initial<t->data)
                {
                        index=k;
                        break;
                }
                k++;
        }
        printf("%d",initial);
        if(move==1)
        {
                t=head;
                for(i=0;i<index;i++)
                        t=t->next;
                for(i=index;i<n;i++)
                {
                        t=t->next;
                        TotalHeadMoment=TotalHeadMoment+abs(t->data-initial);
                        initial=t->data;
                        printf("->%d",t->data);
                }
                t=head->next;
                for(i=0;i<index;i++)
                {
                        TotalHeadMoment=TotalHeadMoment+abs(t->data-initial);
                        initial=t->data;
                        printf("->%d",t->data);
                        t=t->next;
                }
        }
        else
        {
                t=head->next;
                for(i=0;i<index-1;i++)
                        t=t->next;
                for(i=index-1;i>=0;i--)
                {
                        TotalHeadMoment=TotalHeadMoment+abs(t->data-initial);
                        initial=t->data;
                        printf("->%d",t->data);
                        t=t->prev;
                }
                t=head;
                for(i=0;i<n;i++)
                        t=t->next;
                for(i=n-1;i>=index;i--)
                {
                        TotalHeadMoment=TotalHeadMoment+abs(t->data-initial);
                        initial=t->data;
                        printf("->%d",t->data);
                        t=t->prev;
                }
        }
        printf("\nTotal Arm Movements is %d\n",TotalHeadMoment);
        return 0;
}
