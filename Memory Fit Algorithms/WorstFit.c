#include<stdio.h>
#define max 25
void main()
{
        int frag[max],b[max],f[max],i,j,nb,nf,temp,highest=0;
        static int bf[max],ff[max];
        for(i=0;i<max;i++)
        {
                b[i]=0;
        }
        printf("\tMemory Management Scheme - Worst Fit");
        printf("\nEnter the number of Segments:");
        scanf("%d",&nb);
        printf("Enter the number of Processes:");
        scanf("%d",&nf);
        printf("\nEnter the size of the Segments:-\n");
        for(i=1; i<=nb; i++)
        {
                printf("Segment %d:",i);
                scanf("%d",&b[i]);
        }
        printf("Enter the size of the Processes :-\n");
        for(i=1; i<=nf; i++)
        {
                printf("Process %d:",i);
                scanf("%d",&f[i]);
        }
        for(i=1; i<=nf; i++)
        {

                for(j=1; j<=nb; j++)
                {
                        if(bf[j]!=1)
                        {
                                temp=b[j]-f[i];
                                if(temp>=0)
                                        if(highest<temp)
                                        {
                                                ff[i]=j;
                                                highest=temp;
                                        }
                        }
                }
                frag[i]=highest;
                bf[ff[i]]=1;
                highest=0;
        }
        printf("\nProcess no:\tProcess size :\tSegment no:\tSegment size:\tFree Space");
        for(i=1; i<=nf; i++)
                printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",i,f[i],ff[i],b[ff[i]],frag[i]);
        printf("\n\n");
        printf("Segment Diagram:-\n");
        for(i=1;i<=nb;i++)
        {
                printf("---------\n");
                printf("|---");
                printf("%d",bf[i]);
                printf("---| Segment %d\n",i);
                printf("---------\n");
}
}
