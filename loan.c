#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "loan.h"
#include "book_management.h"
#include "reglog.h"

// typedef struct loan{
//     char *username;
//     unsigned int id;
//     char *title;
//     char *authors
// }loan;

int borrowBook(info stu, const char *title)
{
    BookArray *brow = find_book_by_title(title);
    if(brow==NULL)
    return 0;
    FILE *brw = fopen("loan.txt", "a+");
    fprintf(brw, stu->username);
    fprintf(brw, "\t");
    fprintf(brw, brow->array->id);
    fprintf(brw, "\t");
    fprintf(brw, brow->array->title);
    fprintf(brw, "\t");
    fprintf(brw, brow->array->authors);
    fprintf(brw, "\t");
    brow->array->copies = brow->array->copies-1;
    return 1;
}

int returnBook(info stu)
{

}