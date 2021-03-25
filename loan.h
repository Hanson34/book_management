#ifndef LOAN_GUARD__H 
#define LOAN_GUARD__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "user.h"

typedef struct{
    char username[20];
    unsigned int id;
    char title[30];
    char authors[30];
}Loan;

Loan loanlist[30];

int borrowBook(User borrow, const char *title);
int returnBook(const char *title);

#endif