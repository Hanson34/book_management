#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "book_management.h"

// typedef struct _Book {
// 	    unsigned int id; //Book ID
// 		char *title; //book title
// 		char *authors; //comma separated list of authors
// 		unsigned int year; // year of publication
// 		unsigned int copies; //number of copies the library has
// }Book;

// typedef struct _BookArray {
// 	 Book* array; // pointer to array (or linked list) of struct Book.
// 	 unsigned int length; // number of elements in the (Book*) array 
//   struct _BookArray *next;
// }BookArray;

BookArray* LinkedList()
{
    //head of linked list
    BookArray *bookHead = (BookArray *)malloc(sizeof(BookArray));
    bookHead->next = NULL;

    //open books.txt
    FILE *ut = fopen("books.txt", "r+");
    if(ut==NULL)    //handle situation when books.txt is damaged
    {
        printf("Book list not found\n");
        exit(-1);
    }

    //obtain head node
    BookArray *oper = bookHead;
    while(1)
    {
        BookArray *buf = (BookArray *)malloc(sizeof(BookArray));
        if(!buf)
        exit(-1);
        //scan info
        //check whether there is no info behind
        if(fscanf(ut,"%d%s%s%d%d",buf->array->id,buf->array->title,buf->array->authors,buf->array->year,buf->array->copies) != 5)
        {
            free(buf);
            break;
        }
        oper->next = buf;
        oper = buf;
        oper->next = NULL;
    }
    return bookHead;
}


//saves the database of books in the specified file
//returns 0 if books were stored correctly, or an error code otherwise
int store_books(FILE *file)
{
    if(file==NULL)
    return 1;
    file=fopen("books.txt", "a+");
    BookArray *head = LinkedList();
    BookArray *buf = head->next;
    if(buf==NULL)
    return 1;
    while(buf)
    {
        fprintf(file, buf->array->id);
        fprintf(file, "\t");
        fprintf(file, buf->array->title);
        fprintf(file, "\t");
        fprintf(file, buf->array->authors);
        fprintf(file, "\t");
        fprintf(file, buf->array->year);
        fprintf(file, "\t");
        fprintf(file, buf->array->copies);
        fprintf(file, "\n");
    }
    return 0;
}

//loads the database of books from the specified file
//the file must have been generated by a previous call to store_books()
//returns 0 if books were loaded correctly, or an error code otherwise
int load_books(FILE *file)
{
    LinkedList();
    return 0;
}

//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
int add_book(Book book)
{
    BookArray *head = LinkedList();
    BookArray *buf = head->next;
    //check whether there has existing books
    if(!buf)
    {
        buf = (BookArray *)malloc(sizeof(BookArray));
        head->next = buf;
    }
    else
    {
        while(buf->next)
        buf = buf->next;
        BookArray *last = (BookArray *)malloc(sizeof(BookArray));
        buf->next = last;
        buf = last;
    }
    printf("Book id:");
    scanf("%d",buf->array->id);
    printf("Book title:");
    scanf("%s",buf->array->title);
    printf("Book authors:");
    scanf("%s",buf->array->authors);
    printf("Book year:");
    scanf("%d",buf->array->year);
    printf("Book copies:");
    scanf("%d",buf->array->copies);
    buf->next=NULL;
}

//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(Book book);

//finds books with a given title.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
BookArray find_book_by_title (const char *title);

//finds books with the given authors.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
BookArray find_book_by_author (const char *author);

//finds books published in the given year.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the 
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
BookArray find_book_by_year (unsigned int year);