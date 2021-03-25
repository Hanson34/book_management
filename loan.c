#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "loan.h"
#include "book_management.h"
#include "user.h"

// typedef struct{
//     char username[20];
//     unsigned int id;
//     char title[30];
//     char authors[30];
// }Loan;

// Loan loanlist[30];

int loanID = 0;

int borrowBook(User borrow, const char *title)
{
    Book brow = find_book_by_title(title);
    if(brow.id==0)
    {
        printf("\nNo such book\n");
        return 0;
    }
    for(int i=0; i<30; i++)
    {
        if(strcmp(loanlist[i].username, borrow.username)==0 && strcmp(loanlist[i].title, title)==0)
        {
            printf("\nYou have already borrowed it\n");
            return 0;
        }
    }
    strcpy(loanlist[loanID].username, borrow.username);
    loanlist[loanID].id=brow.id;
    strcpy(loanlist[loanID].title, brow.title);
    strcpy(loanlist[loanID].authors, brow.authors);
    // printf("%s,%u,%s,%s",loanlist[loanID].username,loanlist[loanID].id,loanlist[loanID].title,loanlist[loanID].authors);
    FILE *brw = fopen("loan.txt", "a+");
    fprintf(brw, "%s,%u,%s,%s", loanlist[loanID].username, loanlist[loanID].id, loanlist[loanID].title, loanlist[loanID].authors);
    fprintf(brw, "\n");
    fclose(brw);
    brow.copies = brow.copies-1;
    printf("\nBook has been borrowed\n");
    return 1;
}

int returnBook(const char *title)
{
    for(int i=0; i<30; i++)
    {
        if(strcmp(loanlist[i].title, title)==0)
        {
            for(int j=i; j<29; j++)
            {
                strcpy(loanlist[j].username, loanlist[j+1].username);
                loanlist[j].id=loanlist[j+1].id;
                strcpy(loanlist[j].title, loanlist[j+1].title);
                strcpy(loanlist[j].authors, loanlist[j+1].authors);
            }
            for(int k=0; k<30; k++)
            {
                FILE *brw = fopen("loan.txt", "w+");
                fprintf(brw, "%s,%u,%s,%s", loanlist[k].username, loanlist[k].id, loanlist[k].title, loanlist[k].authors);
                fprintf(brw, "\n");
                fclose(brw);
            }
            printf("\nBook has been removed\n");
            return 1;
        }
        else
        {
            printf("\nNo such book\n");
            return 0;
        }
    }
}