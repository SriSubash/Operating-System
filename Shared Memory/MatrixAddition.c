#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
int main()
{
        int a,i,j,m3[32];
        int d1=shmget(70,32*sizeof(int),0666|IPC_CREAT);
        int *m1=(int*)shmat(d1,NULL,0);
        a=fork();
        if(a<0)
        {
                printf("Error");
        }
        else if(a==0)
        {
                printf("Enter the 4 x 4 Matrix 1 : \n");
                for(i=0;i<16;i++)
                {
                        scanf("%d",&a);
                        *(m1+i)=a;
                }
                printf("Enter the 4 x 4 Matrix 2 : \n");
                for(i=16;i<32;i++)
                {
                        scanf("%d",&a);
                        *(m1+i)=a;
                }
        }
        else if(a>0)
        {
                wait();
                printf("Addition of the Matrices : \n");
                for(i=0;i<16;i++)
                {
                        printf("%d\t",*(m1+i)+*(m1+(i+16)));
                        if(i==3||i==7||i==11||i==15)
                                printf("\n");
                }
        }
}
