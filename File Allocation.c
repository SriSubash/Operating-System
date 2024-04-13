#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stddef.h>
#define MAX 100
#define FREE 0
typedef struct File
{
    char name[21];
    int size;
    int start_block;
    int end_block;
    int *indices;
    int length;
} File;

typedef struct Directory
{
    File f[MAX];
    int size;
} Directory;

typedef struct Block
{
    int id;
    unsigned status : 1;
    struct Block *next_file_blk;
} Block;

void init_file(File *const);
void init_dir(Directory *const);
void init_block(Block *const);
void contiguous(File *const, const int, const int, const int);
void linked(File *const, const int, const int, const int);
void indexed(File *const, const int, const int, const int);
typedef Block Data;
typedef struct Node
{
    Data d;
    struct Node *next;
} Node;

typedef Node *List;

extern void init_block(Block *const);

List createEmptyList()
{
    Node *head = (Node *)malloc(sizeof(Node));

    init_block(&(head -> d));

    head->next = NULL;

    return head;
}

void insertLast(List head, const Data d)
{
    Node *new = (Node *)malloc(sizeof(Node));

    new->d = d;

    Node *tmp = head;

    while (tmp->next)
    {
        tmp = tmp->next;
    }

    new->next = NULL;

    tmp->next = new;
}

void insertFirst(List head, const Data d)
{
    Node *new = (Node *)malloc(sizeof(Node));

    new->d = d;

    new->next = head->next;

    head->next = new;
}

Data delete (List prev)
{
    Data rVal;
    if (!prev)
    {
        return rVal;
    }
    if (!prev->next)
    {
        return rVal;
    }

    Node *tmp = prev->next;

    rVal = tmp->d;

    prev->next = prev->next->next;

    free(tmp);

    return rVal;
}

Data deleteFirst(List head)
{
    Data rVal;
    if (head->next == NULL)
    {
        printf(" Empty List! \n\n");
        return rVal;
    }

    delete (head);
}

Data deleteLast(List head)
{
    Data rVal;
    if (head->next == NULL)
    {
        printf(" Empty List! \n\n");
        return rVal;
    }

    Node *tmp = head;

    while (tmp->next->next != NULL)
    {
        tmp = tmp->next;
    }

    delete (tmp);
}

void display(List head)
{
    Node *tmp = head->next;

    if (tmp == NULL)
    {
        printf(" Empty! \n\n");
        return;
    }

    while (tmp)
    {
        printf(" BID : %-2d\tStatus: %d\n\n", tmp->d.id, tmp->d.status);
        tmp = tmp->next;
    }
}

int length(List head)
{
    Node *tmp = head->next;

    if (tmp == NULL)
    {
        return 0;
    }

    int count = 0;
    while (tmp)
    {
        tmp = tmp->next;
        count++;
    }
    return count;
}

Node* search(List head, const int id)
{

    if (head->next == NULL)
    {
        return NULL;
    }

    Node *tmp = head -> next;

    while (tmp)
    {
        if (tmp->d.id == id)
        {
            return tmp;
        }
        tmp = tmp->next;
    }

    return NULL;
}

void init_file(File *const f)
{
    strcpy(f->name, "");
    f->start_block = -1;
    f->end_block = -1;
    f->size = -1;
    f->indices = NULL;
    f->length = -1;
}

void init_dir(Directory *const d)
{
    d->size = 0;
    int i;
    for (i = 0; i < MAX; i++)
        init_file(&(d->f[i]));
}

void init_block(Block *const b)
{
    b->status = FREE;
    b->id = -1;
    b->next_file_blk = NULL;
}

void contiguous(File *const f, const int n_files, const int blk_size, const int num_blk)
{
    List list = createEmptyList();
    Block b;
    init_block(&b);
    Node *ptr, *tmp;
    int blocks_visited;
    int flag, id;
    int counter, blk_req;
    int start, end,i,j;
    for ( i = 0; i < num_blk; i++)
    {
        b.id = i;
        insertLast(list, b);
    }

    for (i = 0; i < n_files; i++)
    {
        blocks_visited = 0;

        flag = 0;

        blk_req = f[i].size / blk_size;

        if (f[i].size % blk_size)
        {
            blk_req++;
        }

        while (blocks_visited < num_blk && !flag)
        {
            id = rand() % num_blk;
            ptr = search(list, id);
            if (ptr->d.status != FREE)
            {
                blocks_visited++;
                continue;
            }

            counter = 0;

            start = ptr->d.id;

            tmp = ptr;

            while (tmp)
            {
                if (tmp->d.status == FREE)
                {
                    counter++;
                    if (counter == blk_req)
                    {
                        flag = 1;
                        break;
                    }
                }
                else
                {
                    break;
                }
                tmp = tmp->next;
            }

            if (flag)
            {
                f[i].start_block = start;
                f[i].length = blk_req;
                tmp = ptr;
                for (i = 0; i < blk_req; i++)
                {
                    tmp->d.status = 1;
                    tmp = tmp->next;
                }
            }
            else
            {
                blocks_visited++;
            }
        }
        if (!flag)
            printf(" Unable to allocate File : %s !! \n", f[i].name);
    }
     printf("\n----------------------------------------------------------------------\n");
    for (i = 0; i < n_files; i++)
    {
        if (f[i].length > 0)
        {
            printf(" |File name-> %-20s |Start-> %-5d |Length-> %-6d |\n", f[i].name, f[i].start_block, f[i].length);
        }
    }
    printf(" ------------------------------------------------------------------------\n");
}

void linked(File *const f, const int n_files, const int blk_size, const int num_blk)
{
    List list = createEmptyList();
    Block b;
    init_block(&b);
    Node *ptr, *tmp, *left, *right;
    int blocks_visited, flag, id, counter, blk_req,i,j;
    for (i = 0; i < num_blk; i++)
    {
        b.id = i;
        insertLast(list, b);
    }
    for (i = 0; i < n_files; i++)
    {
        counter = 0;
        blocks_visited = 0;
        flag = 0;
        blk_req = f[i].size / blk_size;
        if (f[i].size % blk_size)
        {
            blk_req++;
        }
        int *allocated = (int *)calloc(blk_req, sizeof(int));
        while (blocks_visited < num_blk && !flag)
        {
            id = rand() % num_blk;
            ptr = search(list, id);

            if (ptr->d.status != FREE)
            {
                blocks_visited++;
                continue;
            }
            ptr -> d.status = 1;
            allocated[counter++] = id;

            if (counter == blk_req)
                flag = 1;
        }
        if (!flag)
        {
            printf(" Unable To Allocate File : %s !! \n\n", f[i].name);
            for(i = 0; i < counter; i++)
            {
                ptr = search(list, allocated[i]);
                ptr -> d.status = FREE;
            }
            free(allocated);
        }
        else
        {

            f[i].start_block = allocated[0];
            f[i].end_block = allocated[blk_req - 1];
            f[i].length = blk_req;
            for (i = 0; i < blk_req - 1; i++)
            {

                left = search(list, allocated[i]);
                right = search(list, allocated[i + 1]);
                left->d.next_file_blk = &(right->d);
                left->d.status = 1;
            }
            right->d.next_file_blk = NULL;
            free(allocated);
        }
    }
     printf(" ---------------------------------------------------------------------\n");
    for (i = 0; i < n_files; i++)
    {
        if (f[i].end_block >= 0)
        {
            printf(" |File name->  %-20s |start->  %-2d      |End->  %-2d     |\n",
                   f[i].name, f[i].start_block, f[i].end_block);
        }
    }
    printf("\n --------------------------------------------------------------------\n");
     for (i = 0; i < n_files; i++)

        if (f[i].start_block >= 0)
        {
            printf("\n File Name : %s\n ",f[i].name);
            ptr = search(list, f[i].start_block);
            Block *b = &(ptr->d);
            while (b)
            {
                printf("%-2d ", b->id);
                b = b->next_file_blk;
            }
        }
}
void indexed(File *const f, const int n_files, const int blk_size, const int num_blk)
{
    List list = createEmptyList();
    Block b;
    init_block(&b);
    Node *ptr, *tmp;
    int blocks_visited, flag, id, counter, blk_req,i,j;
    int start, end;
    for (i = 0; i < num_blk; i++)
    {
        b.id = i;
        insertLast(list, b);
    }
    for ( i = 0; i < n_files; i++)
    {
        blocks_visited = 0;
        flag = 0;
        blk_req = f[i].size / blk_size;
        if (f[i].size % blk_size)
        {
            blk_req++;
        }
        f[i].indices = (int *)calloc(blk_req + 1, sizeof(int));
        f[i].length = blk_req;
        counter = 0;
        while (blocks_visited < num_blk && !flag)
        {
            id = rand() % num_blk;
            ptr = search(list, id);
            if (ptr->d.status == FREE)
            {
                f[i].indices[counter++] = id;
                if (counter == blk_req + 1)
                {
                    flag = 1;
                    break;
                }
            }
            else
            {
                blocks_visited++;
            }
        }
        if (!flag)
        {
            printf(" Unable to allocate memory for File : %s !! \n\n", f[i].name);
            free(f[i].indices);
            f[i].indices = NULL;
        }
    }
     printf(" --------------------------------------------------\n");
    for ( i = 0; i < n_files; i++)
    {
        if (f[i].indices)
        {
            printf(" |File name->v %-20s |Index-> %-2d      |\n", f[i].name, f[i].indices[0]);
        }
    }
    printf("\n ---------------------------------------------------\n");
    printf(" ----------------------------------------\n");
    printf(" |      File Name       | Blocks Indexed |\n");
    printf("------------------------------------------\n");
    for (i = 0; i < n_files; i++)
    {
        if (f[i].indices)
        {
            for ( j = 1; j <= f[i].length; j++)
            {
                printf(" |  %-20s |    %-2d       |\n", ((j > 1) ? "" : f[i].name), f[i].indices[j]);
            }
        }
        printf("\n------------------------------------------\n");
    }
}
int main()
{
    int mem_size;
    int blk_size;
    int num_blks;
    int num_file;
    int choice,i;
    File f[MAX];
    printf("\n\n File Allocation Techniques \n\n");
    printf(" Enter Memory Size :  ");
    scanf("%d", &mem_size);
    printf(" Enter Block Size : ");
    scanf("%d", &blk_size);
    num_blks = mem_size / blk_size;
    printf(" Enter Number Of Files :  ");
    scanf("%d", &num_file);
    getchar();
    for (i = 0; i < num_file; i++)
    {
        printf(" Enter the File Name :\n ");
        scanf("%[^\n]", f[i].name);
        printf(" Enter the File Size :\n ");
        scanf("%d", &f[i].size);
        getchar();
    }

    while (1)
    {
        printf("\n File Allocation Techniques \n");
        printf("\n Enter Your choice : 1- contiguous 2-Linked 3-Indexed 4-Exit\n ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1 :
                    {
                        printf("\n Contiguous allocation \n");
                        contiguous(f, num_file, blk_size, num_blks);
                        break;
                    }
            case 2 :
                    {
                        printf("\n Linked List Allocation \n");
                        linked(f, num_file, blk_size, num_blks);
                        break;
                    }

            case 3 :
                    {
                        printf("\n Indexed Allocation \n");
                        indexed(f, num_file, blk_size, num_blks);
                        break;
                    }
             case 4:
                        exit(0);

            default :
                    {
                        printf(" Invalid Input!! \n\n");
                    }
        }
    }
    return 0;
}
