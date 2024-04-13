#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
void main()
{
        int a,b;
        a=fork();
        b=fork();
        if(a<0)
                printf("No Process is Created\n");
        else if(a>0 && b>0)
                printf("A : %d\n",getpid());
        else if(a==0 && b>0)
                printf("B : %d %d\n",getpid(),getppid());
        else if(a>0 && b==0)
                printf("C : %d %d\n",getpid(),getppid());
        else if(a==0 && b==0)
                printf("D : %d %d\n",getpid(),getppid());
}
