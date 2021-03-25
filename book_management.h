
#ifndef BOOK_MANAGEMENT_GUARD__H 
#define BOOK_MANAGEMENT_GUARD__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"

/*You can extend the structs (Book and BookArray) defined in this head file;
  However, you may not change the function prototypes. 
  You are also free to add additional head files and data structures as needed. 
*/


typedef struct {
	    unsigned int id; //Book ID
		char title[30]; //book title
		char authors[30]; //comma separated list of authors
		unsigned int year; // year of publication
		unsigned int copies; //number of copies the library has
}Book;

Book booklist[30];
Book buf[30];

typedef struct{
    char username[20];
    unsigned int id;
    char title[30];
    char authors[30];
}Loan;

Loan loanlist[30];
Loan lbuf[30];

//saves the database of books in the specified file
void store_books(Book save);

//loads the database of books from the specified file
void load_books();

//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
int add_book(Book add);

//removes a book from the library
//returns 1 if the book could be successfully removed, or an error code otherwise
int remove_book(const char *name);

//finds books with a given title
Book find_book_by_title (const char *title);

//finds books with the given authors
Book find_book_by_author (const char *author);

//finds books published in the given year
Book find_book_by_year (unsigned int year);

//display all books in the terminal
void displayBooks();

//loads the database of loan from the specified file
void load_loan();

//refresh the loan & book database
void refresh(Book re);

//borrow the book from the database
int borrowBook(User borrow, const char *title);

//returnthe book from the database
int returnBook(User borrow, const char *title);

//another refresh and verification when return
void returnRefresh(User borrow, const char *title);

#endif
