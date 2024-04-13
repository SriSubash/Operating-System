#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
void main()
{
        int a[2],k,x,y;
        x=pipe(a);
        if(x==1)
                printf("Pipe not Created\n");
        else
        {
                k=fork();
                if(k<0)
                        printf("Process not Created\n");
                else if(k==0)
                {
                        close(a[0]);
                        printf("Enter the Year :\n");
                        scanf("%d",&y);
                        write(a[1],&y,1);
                }
                else if(k>0)
                {
                        close(a[1]);
                        read(a[0],&y,1);
                        if(y%4==0)
                                printf("Leap Year\n");
                        else if(y%400==0 || y%100==0)
                                printf("Leap Year\n");
                        else
                                printf("Not Leap Year\n");

                }
        }
}
