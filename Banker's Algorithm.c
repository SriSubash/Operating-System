#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int NUM_RESOURCES,NUM_PROCESSES;
int safe_seq[10];
typedef struct Process {
        int id;
        int *allocated;
        int *max;
        int *need;
        bool finished;
        struct Process *next;
} Process;

typedef struct ResourceManager
{
        int *available;
        Process *processes;
} ResourceManager;
bool canExecute(Process *p, int *work);
void display(ResourceManager *rm)
{
        Process *p=rm->processes;
        printf("PROCESSES\tALLOCATION\t\tMAX RESOURCES\n");
        while(p!=NULL)
        {
                int i;
                printf("P%d\t\t",p->id);
                for(i=0;i<NUM_RESOURCES;i++)
                        printf("%d\t",p->allocated[i]);
                for(i=0;i<NUM_RESOURCES;i++)
                        printf("%d\t",p->max[i]);
                printf("\n");
                p=p->next;
        }
}
void initResourceManager(ResourceManager *rm)
{
        rm->available = (int*)malloc(NUM_RESOURCES * sizeof(int));
        rm->processes = NULL;
}
void addProcess(ResourceManager *rm, int id, int *allocated, int *max)
{
        int i;
        Process *p = (Process*)malloc(sizeof(Process));
        p->id = id;
        p->allocated = (int*)malloc(NUM_RESOURCES * sizeof(int));
        p->max = (int*)malloc(NUM_RESOURCES * sizeof(int));
        p->need = (int*)malloc(NUM_RESOURCES * sizeof(int));
        p->finished = false;
        p->next = NULL;

        for (i = 0; i < NUM_RESOURCES; i++)
        {
                p->allocated[i] = allocated[i];
                p->max[i] = max[i];
                p->need[i] = max[i] - allocated[i];
        }

        if (rm->processes == NULL)
        {
                rm->processes = p;
        }
        else
        {
                Process *temp = rm->processes;
                while (temp->next != NULL)
                {
                        temp = temp->next;
                }
                temp->next = p;
        }
}

bool isSafeState(ResourceManager *rm)
{
        int i;
        int *work = (int*)malloc(NUM_RESOURCES * sizeof(int));
        for ( i = 0; i < NUM_RESOURCES; i++)
        {
                work[i] = rm->available[i];
        }
        bool *finish = (bool*)malloc(NUM_PROCESSES * sizeof(bool));
        for (i = 0; i < NUM_PROCESSES; i++)
        {
                finish[i] = false;
        }

        bool found = false;
        int k=0;
        while (!found)
        {
                found = true;
                Process *p = rm->processes;
                while (p != NULL)
                {
                        if (!p->finished && canExecute(p, work))
                        {
                                for (i = 0; i < NUM_RESOURCES; i++)
                                {
                                        work[i] += p->allocated[i];
                                }
                                finish[p->id] = true;
                                safe_seq[k]=p->id;
                                k++;
                                p->finished = true;
                                found = false;
                                break;
                        }
                        p = p->next;
                }
        }
        for (i = 0; i < NUM_PROCESSES; i++) {
                if (!finish[i]) {
                        return false;
                }
        }
        return true;
}

bool canExecute(Process *p, int *work)
{
        int i;
        for ( i = 0; i < NUM_RESOURCES; i++)
        {
                if (p->need[i] > work[i])
                {
                        return false;
                }
        }
        return true;
}
int main()
{
        int i,j;
        printf("Enter the No of Processes : \n");
        scanf("%d",&NUM_PROCESSES);
        printf("Enter the No of Resources : \n");
        scanf("%d",&NUM_RESOURCES);
        ResourceManager rm;
        initResourceManager(&rm);

        int available[NUM_RESOURCES];
        printf("Enter the available resources:\n");
        for (i = 0; i < NUM_RESOURCES; i++)
        {
                scanf("%d", &available[i]);
        }
        rm.available = available;

        for ( i = 0; i < NUM_PROCESSES; i++)
        {
                int allocated[NUM_RESOURCES];
                int max[NUM_RESOURCES];
                printf("Enter the allocated resources for process %d:\n", i);
                for (j = 0; j < NUM_RESOURCES; j++)
                {
                        scanf("%d", &allocated[j]);
                }
                printf("Enter the maximum resources for process %d:\n", i);
                for (j = 0; j < NUM_RESOURCES; j++)
                {
                        scanf("%d", &max[j]);
                }
                addProcess(&rm, i, allocated, max);
        }
                display(&rm);
        if (isSafeState(&rm))
        {
                printf("System is in a safe state.\n");
                printf("The Safe Sequence is : \n");
                printf("<-");
                for (i=0; i<NUM_PROCESSES; i++)
                        printf("P%d-",safe_seq[i]);
                printf(">");
        }
        else
        {
                printf("System is not in a safe state.\n");
        }
        printf("\n");
        return 0;
}
