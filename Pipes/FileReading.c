#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
void main()
{
        int a[2],k,x,fd;
        char ch,y[20];
        x=pipe(a);
        if(x==1)
                printf("Pipe not Created\n");
        else
        {
                k=fork();
                if(k<0)
                        printf("Process not Created\n");
                else if(k>0)
                {
                        close(a[0]);
                        printf("Enter the Filename :\n");
                        scanf("%s",y);
                        fd=open(y,O_RDONLY);
                        while(read(fd,&ch,1))
                                write(a[1],&ch,1);
                }
                else if(k==0)
                {
                        close(a[1]);
                        while(read(a[0],&ch,1))
                                printf("%c",ch);

                }
        }
}
