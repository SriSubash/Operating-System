#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc,char* argv[])
{
        int fd1,fd2;
        char c;
        if(argc==1)
                printf("Cannot Open File.\n");
        else if(argc==2)
        {
                fd1=open(argv[1],O_RDONLY);
                while(read(fd1,&c,1))
                {
                        printf("%c",c);
                }
        }
        else if(argc==3)
        {
                fd1=open(argv[1],O_RDONLY);
                fd2=open(argv[2],O_RDONLY);
                while(read(fd1,&c,1))
                {
                        printf("%c",c);
                }
                while(read(fd2,&c,1))
                {
                        printf("%c",c);
                }
        }
        else if(strcmp(argv[2],">>")==0)
        {
                        fd1=open(argv[1],O_RDONLY);
                        fd2=open(argv[3],O_APPEND);
                        while(read(fd1,&c,1))
                        {
                                write(fd2,&c,1);
                        }
        }
        else if(strcmp(argv[2],">")==0)
        {
                        fd1=open(argv[1],O_RDONLY);
                        fd2=open(argv[3],O_TRUNC);
                        while(read(fd1,&c,1))
                        {
                                write(fd2,&c,1);
                        }
        }
                close(fd1);
                close(fd2);
        return 0;
}
