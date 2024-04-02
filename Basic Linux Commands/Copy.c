#include<sys/types.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
        int fd1,fd2;
        char c;
        fd1=open(argv[1],O_RDONLY);
        fd2=open(argv[2],O_WRONLY);
        if(fd1==-1 || fd2==-1)
                printf("Cannot Open File.\n");
        else
        {

                while(read(fd1,&c,1))
                {
                        write(fd2,&c,1);

                }
        }
        close(fd1);
        close(fd2);
        return 0;
}
