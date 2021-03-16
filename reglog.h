#ifndef _REGLOG_H_
#define _REGLOG_H_

#include <stdio.h>

typedef struct userinfo{
    char name[20];
    char username[20];
    char password[20];
    struct userinfo *next;
} userinfo, *info;

info Linkedlist();
int login(info head);
int registerUser(info head);
void save(info head);

#endif