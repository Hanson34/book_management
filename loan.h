#ifndef LOAN_GUARD__H 
#define LOAN_GUARD__H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct loan{
    char *username;
    unsigned int id;
    char *title;
    char *authors;
}loan;

int borrowBook(info stu, const char *title);
int returnBook(info stu);

#endif