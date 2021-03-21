#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "reglog.h"

// typedef struct userinfo{
//     char name[20];
//     char username[20];
//     char password[20];
//     struct userinfo *next;
// } userinfo, *info;

//create a linked list for userinfo
info userLinkedlist()
{
    //head of linked list
    info infoHead = (info)malloc(sizeof(userinfo));
    infoHead->next = NULL;

    //open user.txt
    FILE *ut = fopen("user.txt", "r+");
    if(ut==NULL)    //handle situation when user.txt is damaged
    {
        printf("Userinfo list not found\n");
        exit(-1);
    }

    //obtain head node
    info oper = infoHead;
    while(1)
    {
        info buf = (info)malloc(sizeof(userinfo));
        if(!buf)
        exit(-1);
        //scan info
        //check whether there is no info behind
        if(fscanf(ut,"%s%s%s",buf->name,buf->username,buf->password) != 3)
        {
            free(buf);
            break;
        }
        oper->next = buf;
        oper = buf;
        oper->next = NULL;
    }
    return infoHead;
}

//login function
int login(info head)
{
    if(head->next == NULL)
    {
        printf("No existing users\n");
        getchar();
        return 0;
    }
    char name[20], username[20], password[20];
    printf("Username:");
    scanf("%s",username);
    printf("Password:");
    scanf("%s",password);
    info buf = head->next;
    while(buf)
    {
        //check the username and password
        if(strcmp(buf->username,"admin")==0 && strcmp(buf->password,"admin")==0)
        {
            printf("Welcome admin\n");
            getchar();
            return 1;
        }
        if(strcmp(buf->username,username)==0 && strcmp(buf->password,password)==0)
        {
            printf("Welcome to the library\n");
            getchar();
            return 2;
        }
        buf = buf->next;
    }
    printf("User not found\n");
    getchar();
    return 0;
}

//register function
int registerUser(info head)
{
    info buf = head->next;
    //check whether there has existing users
    if(!buf)
    {
        buf = (info)malloc(sizeof(userinfo));
        head->next = buf;
    }
    else
    {
        while(buf->next)
        buf = buf->next;
        info last = (info)malloc(sizeof(userinfo));
        buf->next = last;
        buf = last;
    }
    printf("Student name:");
    scanf("%s",buf->name);
    printf("Username:");
    scanf("%s",buf->username);
    printf("Password:");
    scanf("%s",buf->password);
    buf->next = NULL;
}

//save to txt
void save(info head)
{
    FILE *us = fopen("user.txt", "a+");
    info buf = head->next;
    if(buf==NULL)
    return;
    while(buf)
    {
        fprintf(us, buf->name);
        fprintf(us, "\t");
        fprintf(us, buf->username);
        fprintf(us, "\t");
        fprintf(us, buf->password);
        fprintf(us, "\n");
    }
}
