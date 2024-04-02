#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
        int des, fhandle, i,k;
        char buf,line[160],line2[160];
        if (argc < 3)
        {
                printf("Insufficient Inputs.\n");
                return 0;
        }
        des = open(argv[2],O_RDONLY);
        do
        {
                i=0;
                do
                {
                        fhandle=read(des,&buf,1);
                        line[i++]=buf;
                }while( fhandle!= 0 && buf != '\n');
                line[i]='\0';
                i=0;
                while(line[i] != '\0')
                {
                        if(line[i] == argv[1][0])
                        {
                                k=1;
                                i++;
                                while((k < strlen(argv[1])) && (line[i] == argv[1][k]))
                                {
                                        i++; k++;
                                }
                        }
                        i++;
                }
                if(k == strlen(argv[1]))
                        printf("%s",line);
        }while( fhandle!= 0);
        close(des);
}
