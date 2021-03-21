#ifndef REGLOG_GUARD__H
#define REGLOG_GUARD__H

#include <stdio.h>

typedef struct userinfo{
    char name[20];
    char username[20];
    char password[20];
    struct userinfo *next;
} userinfo, *info;

info userLinkedlist();
int login(info head);
int registerUser(info head);
void save(info head);

#endif