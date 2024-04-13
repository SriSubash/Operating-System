#include<stdio.h>
#include<unistd.h>
void main()
{
        int a[2],k,num,r,sum=0,temp,x;
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
                        printf("Enter a Number :\n");
                        scanf("%d",&num);
                        close(a[0]);
                        write(a[1],&num,3);
                }
                else if(k>0)
                {
                        close(a[1]);
                        read(a[0],&num,3);
                        temp=num;
                        while(num>0)
                        {
                                r=num%10;
                                sum=sum+(r*r*r);
                                num=num/10;
                        }
                        if(temp!=sum)
                                printf("Not an Armstrong Number\n");
                        else
                                printf("Armstrong Number\n");
                }
        }
}
