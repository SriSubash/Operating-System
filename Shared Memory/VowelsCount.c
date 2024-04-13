#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
int main()
{
        int a,i,j,vow[10]={65,69,73,79,85,97,101,105,111,117};
        int shmid=shmget(70,1024,0666|IPC_CREAT),flag=0;
        char str[10],str1[10],*m=(char*)shmat(shmid,NULL,0);
        a=fork();
        if(a<0)
                printf("Error");
        else if(a==0)
        {
                printf("Enter the String :\n");
                scanf("%s",str);
                strcpy(m,str);
        }
        else if(a>0)
        {
                wait();
                strcpy(str1,m);
                for(i=0;i<10;i++)
                        for(j=0;j<10;j++)
                                if(str1[i]==vow[j])
                                        flag++;
                printf("No of Vowels : %d\n",flag);
        }
        return 0;
}
