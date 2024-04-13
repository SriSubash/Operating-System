#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
void main()
{
        int a,b,c;
        a=fork();
        if(a<0)
                printf("No Process is Created\n");
        if(a>0)
        {
                printf("A : %d\n",getpid());
        }
        if(a==0)
        {
                printf("B : %d %d\n",getpid(),getppid());
                b=fork();
                if(b<0)
                        printf("No Process is Created\n");
                if(b==0)
                        printf("C : %d %d\n",getpid(),getppid());
                c=fork();
                if(c<0)
                        printf("No Process is Created\n");
                if(c==0 && b>0)
                        printf("D : %d %d\n",getpid(),getppid());
        }

}
