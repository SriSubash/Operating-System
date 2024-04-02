#include<stdio.h>
#include<dirent.h>
void main(int argc,char *argv[])
{
DIR *p;
struct dirent *d;
p=opendir(argv[1]);
if(p==NULL)
  {
  perror("Cannot find directory");
  }
else
{
while(d=readdir(p))
  printf("%s\n",d->d_name);
}
}
