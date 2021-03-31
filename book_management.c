#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "user.h"

// typedef struct {
// 	    unsigned int id; //Book ID
// 		char title[30]; //book title
// 		char authors[30]; //comma separated list of authors
// 		unsigned int year; // year of publication
// 		unsigned int copies; //number of copies the library has
// }Book;

// Book booklist[30];
// Book buf[30];

// typedef struct{
//     char username[20];
//     unsigned int id;
//     char title[30];
//     char authors[30];
// }Loan;

// Loan loanlist[30];
// Loan lbuf[30];

int bookID=0;
int loanID=0;

//saves the database of books in the specified file
void store_books(Book save)
{
    FILE *file=fopen("books.txt", "a+");
    fprintf(file, "%u,%s,%s,%u,%u", save.id, save.title, save.authors, save.year, save.copies);
    fprintf(file, "\n");
    fclose(file);
}

//loads the database of books from the specified file
//the file must have been generated by a previous call to store_books()
//returns 0 if books were loaded correctly, or an error code otherwise
void load_books()
{
    FILE *file=fopen("books.txt", "r");
    for(int i=0; i<30; i++)
    fscanf(file, "%u,%[^,],%[^,],%u,%u", &booklist[i].id, booklist[i].title, booklist[i].authors, &booklist[i].year, &booklist[i].copies);
    fclose(file);
}

//adds a book to the ones available to the library
//returns 1 if the book could be added, or an error code otherwise
int add_book(Book add)
{
    load_books();
    for(int i=0; i<30; i++)
    {
        //compare book add & existing titles
        if(strcmp(booklist[i].title, add.title)==0)
        {
            remove_book(add.title);
            store_books(add);
            printf("\nBook added\n");
            return 1;
        }
    }
    printf("\nBook added\n");
    store_books(add);
    //refresh array
    load_books();
    return 1;
}

//removes a book from the library
//returns 1 if the book could be successfully removed, or an error code otherwise.
int remove_book(const char *name)
{
    load_books();
    load_loan();
    for(int i=0; i<30; i++)
    {
        if(strcmp(loanlist[i].title, name)==0){
            printf("\nBook on loan\n");
            return 0;
        }
        //prevent condition that one author has many books
        if(strcmp(booklist[i].authors, name)==0||strcmp(booklist[i].title, name)==0)
        {
            //move all books one place forward to cover the deleted book
            for(int j=i; j<29; j++)
            buf[j]=booklist[j+1];
            printf("\nBook has been removed\n");
            //save into txt
            FILE *file=fopen("books.txt", "w+");
            for(int k=0; k<30; k++)
            {
                if(buf[k].id==0)
                break;
                fprintf(file, "%u,%s,%s,%u,%u", buf[k].id, buf[k].title, buf[k].authors, buf[k].year, buf[k].copies);
                fprintf(file, "\n");
            }
            fclose(file);
            return 1;
        }//if not found, nothing would be changed
        else
        buf[i]=booklist[i];
    }
    printf("\nNo such book\n");
    return 0;
}

//finds books with a given title.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
Book find_book_by_title (const char *title)
{
    //handle situation when no such book
    Book none;
    none.id = 0;
    load_books();
    for(int i=0; i<30; i++)
    {
        if(strcmp(booklist[i].title,title)==0)
        {
            printf("\nBook found\n");
            printf("ID\ttitle\tauthors\tyear\tcopies\n");
            printf("%u\t%s\t%s\t%u\t%u\n", booklist[i].id, booklist[i].title, booklist[i].authors, booklist[i].year, booklist[i].copies);
            // return the book in the list
            return booklist[i];
        }
    }
    printf("\nBook not found\n");
    return none;
}

//finds books with the given authors.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
Book find_book_by_author (const char *author)
{
    // char c[30];
    //handle situation when no such book
    Book none;
    none.id = 0;
    load_books();
    // strcpy(c, author);
    // for(int i=0; i<30; i++){
    //     printf("%c",c[i]);
    //     if(c[i]>='0'||c[i]<='9'){
    //         printf("\nInvalid input\n");
    //         return none;
    //     }
    // }
    for(int i=0; i<30; i++)
    {
        if(strcmp(booklist[i].authors,author)==0)
        {
            printf("\nBook found\n");
            printf("ID\ttitle\tauthors\tyear\tcopies\n");
            printf("%u\t%s\t%s\t%u\t%u\n", booklist[i].id, booklist[i].title, booklist[i].authors, booklist[i].year, booklist[i].copies);
            // return the book in the list
            return booklist[i];
        }
    }
    printf("\nBook not found\n");
    return none;
}

//finds books published in the given year.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
Book find_book_by_year (unsigned int year)
{
    //handle situation when no such book
    int a=0;
    Book none;
    none.id = 0;
    load_books();
    for(int i=0; i<30; i++)
    {
        if(booklist[i].year==year)
        {
            printf("\nBook found\n");
            printf("ID\ttitle\tauthors\tyear\tcopies\n");
            printf("%u\t%s\t%s\t%u\t%u\n", booklist[i].id, booklist[i].title, booklist[i].authors, booklist[i].year, booklist[i].copies);
            // return the book in the list
            return booklist[i];
            a=1;
        }
    }
    if(a==1)
    return none;
    printf("\nBook not found\n");
    return none;
}

//display all books in the terminal
void displayBooks()
{
    load_books();
    printf("\nID\ttitle\tauthors\tyear\tcopies\n");
    for(int i=0; i<30; i++){
        if(booklist[i].id==0)
        break;
        printf("%u\t%s\t%s\t%u\t%u\n", booklist[i].id, booklist[i].title, booklist[i].authors, booklist[i].year, booklist[i].copies);
    }
}

//loads the database of loan from the specified file
void load_loan()
{
    FILE *file=fopen("loan.txt", "r");
    for(int i=0; i<30; i++)
    fscanf(file, "%u,%[^,],%[^,],%s", &loanlist[i].id, loanlist[i].username, loanlist[i].title, loanlist[i].authors);
    fclose(file);
}

//refresh the loan & book database
void refresh(Book re)
{
    for(int i=0; i<30; i++)
    {
        //prevent condition that one author has many books
        if(strcmp(booklist[i].authors, re.authors)==0||strcmp(booklist[i].title, re.title)==0)
        {
            //move all books one place forward to cover the deleted book
            for(int j=i; j<29; j++)
            buf[j]=booklist[j+1];
            FILE *file=fopen("books.txt", "w+");
            for(int k=0; k<30; k++)
            {
                if(buf[k].id==0)
                break;
                fprintf(file, "%u,%s,%s,%u,%u", buf[k].id, buf[k].title, buf[k].authors, buf[k].year, buf[k].copies);
                fprintf(file, "\n");
            }
            fclose(file);
        }
        //if not found, nothing would be changed
        else
        buf[i]=booklist[i];
    }
    store_books(re);
    load_books();

}

//borrow the book from the database
int borrowBook(User borrow, const char *title)
{
    load_loan();
    int b;
    Book brow = find_book_by_title(title);
    //if no existing book on loan
    if(brow.id==0)
    return 0;
    for(int i=0; i<30; i++)
    {
        //prevent condition that one book is borrowed by many students
        if(strcmp(loanlist[i].username, borrow.username)==0 && strcmp(loanlist[i].title, title)==0)
        {
            printf("\nYou have already borrowed it\n");
            return 0;
        }
        if(strcmp(booklist[i].title,title)==0)
        //record the place where the book is
        b=i;
    }
    //write into a loan list
    strcpy(loanlist[loanID].username, borrow.username);
    loanlist[loanID].id=brow.id;
    strcpy(loanlist[loanID].title, brow.title);
    strcpy(loanlist[loanID].authors, brow.authors);
    //save it into txt
    FILE *brw = fopen("loan.txt", "a+");
    fprintf(brw, "%u,%s,%s,%s", loanlist[loanID].id, loanlist[loanID].username, loanlist[loanID].title, loanlist[loanID].authors);
    fprintf(brw, "\n");
    fclose(brw);
    booklist[b].copies = booklist[b].copies-1;
    //refresh list
    refresh(booklist[b]);
    printf("\nBook has been borrowed\n");
    return 1;
}

void displayLoan(User borrow){
    load_loan();
    printf("\nID\tusername\ttitle\tauthors\n");
    for(int i=0; i<30; i++){
        if(loanlist[i].id==0)
        break;
        if(loanlist[i].username==borrow.username)
        printf("%u\t%s\t%s\t%s\n", loanlist[i].id, loanlist[i].username, loanlist[i].title, loanlist[i].authors);
    }
}

//check if current user has loan
int loanCheck(User borrow){
    int c=0;
    for(int i=0; i<30; i++){
        if(strcmp(loanlist[i].username,borrow.username)==0)
        c +=1;
    }
    if(c==0){
        printf("\nNo borrowed book\n");
        return 0;
    }
}

//return the book from the database
int returnBook(User borrow, const char *title)
{
    int b=0;
    //refresh the loanlist
    load_books();
    load_loan();
    //record place
    for(int i=0; i<30; i++)
    if(strcmp(booklist[i].title,title)==0)
    b=i;
    //remove module
    for(int i=0; i<30; i++)
    {
        if(strcmp(booklist[i].title,title)==0)
        b=i;
        if(strcmp(loanlist[i].title, title)==0 && strcmp(loanlist[i].username, borrow.username)==0)
        {
            for(int j=i; j<29; j++)
            lbuf[j]=loanlist[j+1];
            printf("\nBook has been returned\n");
            FILE *file=fopen("loan.txt", "w+");
            for(int k=0; k<30; k++)
            {
                if(lbuf[k].id!=0)
                {
                    fprintf(file, "%u,%s,%s,%s", lbuf[k].id, lbuf[k].username, lbuf[k].title, lbuf[k].authors);
                    fprintf(file, "\n");
                }
            }
            fclose(file);
            return b;
        }
        else
        lbuf[i]=loanlist[i];
    }
    printf("\nNo such book\n");
    return 0;
}

//another refresh and verification when return
void returnRefresh(User borrow, const char *title)
{
    int i=0;
    //i = b if a book is returned
    i = returnBook(borrow, title);
    if(i!=0)
    {
        booklist[i].copies = booklist[i].copies+1;
        refresh(booklist[i]);
    }
}