#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interface.h"
#include "book_management.h"
#include "user.h"

//return a newly allocated string
static char *ask(const char *question) {

	printf("%s",question);

	const int size_step = 2;
	char *answer = malloc(size_step);
	answer[0] = 0; //now it's a string of length 0.

	//read until a new line in blocks of size_step  bytes at at time
	char *next_chunk = answer;
	int iteration = 0;
	do {
		answer = realloc(answer, size_step + iteration*size_step);
		next_chunk = answer + strlen(answer); //answer may have moved.
		fgets(next_chunk, size_step, stdin);

		next_chunk = answer + strlen(answer); //take the new read into account
		++iteration;
	} while (* (next_chunk-1) != '\n');

	*(next_chunk-1) = 0; //truncate the string eliminating the new line.

	return answer;
}

void run_interface()
{
    int option, num;
    // loop when not enter 3
    while(1)
    {
        char *answer = ask("\n1.Login\n2.Register\n3.Exit\nOption: ");
        option = atoi(answer);
        free(answer);
        if(option==1)
        {
            //user & book for storing infomation
            User oper;
            Book found;
            oper=login();
            int v = verification(oper);
            //admin
            if(v==1)
            {
                while(1)
                {
                    printf("\n(Administrator)\n");
                    printf("1.Display all books\n");
                    printf("2.Search a book\n");
                    printf("3.Add a book\n");
                    printf("4.Remove a book\n");
                    printf("5.Exit\n");
                    answer = ask("Option: ");
                    option = atoi(answer);
                    free(answer);
                    if(option==1)
                    displayBooks();
                    else if(option==2)
                    {
                        answer = ask("\nSearch book by:\n1.title\n2.author\n3.year\nOption: ");
                        option = atoi(answer);
                        free(answer);
                        if(option==1)
                        {
                            answer = ask("\nEnter the title: ");
                            found = find_book_by_title (answer);
                            free(answer);
                            // printf("\nID\ttitle\tauthors\tyear\tcopies\n");
                            // printf("%d\t%s\t%s\t%d\t%d\n", found.id, found.title, found.authors, found.year, found.copies);
                        }
                        else if(option==2)
                        {
                            answer = ask("\nEnter the authors: ");
                            found = find_book_by_title (answer);
                            free(answer);
                            // printf("\nID\ttitle\tauthors\tyear\tcopies\n");
                            // printf("%d\t%s\t%s\t%d\t%d\n", found.id, found.title, found.authors, found.year, found.copies);
                        }
                        else if(option==3)
                        {
                            answer = ask("\nEnter the year: ");
                            num = atoi(answer);
                            free(answer);
                            found = find_book_by_year (num);
                            // printf("\nID\ttitle\tauthors\tyear\tcopies\n");
                            // printf("%d\t%s\t%s\t%d\t%d\n", found.id, found.title, found.authors, found.year, found.copies);
                        }
                        else
                        printf("\nNo such command\n");
                    }
                    else if(option==3)
                    {
                        Book add;
                        answer = ask("Book id: ");
                        num = atoi(answer);
                        add.id = num;
                        answer = ask("\nBook title: ");
                        strcpy(add.title, answer);
                        free(answer);
                        answer = ask("Book authors: ");
                        strcpy(add.authors, answer);
                        free(answer);
                        answer = ask("Book year: ");
                        num = atoi(answer);
                        add.year = num;
                        free(answer);
                        answer = ask("Book copies: ");
                        num = atoi(answer);
                        add.copies = num;
                        free(answer);
                        add_book(add);
                    }
                    else if(option==4)
                    {
                        answer = ask("\nEnter the title or authors of the book you would like to remove: ");
                        remove_book(answer);
                        free(answer);
                    }
                    else if(option==5)
                    break;
                    else
                    printf("\nNo such command\n");
                }
            }
            //student
            if(v==2)
            {
                while(1)
                {
                    printf("\n1.Display all books\n");
                    printf("2.Search a book\n");
                    printf("3.Borrow a book\n");
                    printf("4.Return a book\n");
                    printf("5.Exit\n");
                    answer = ask("Option: ");
                    option = atoi(answer);
                    free(answer);
                    if(option==1)
                    displayBooks();
                    else if(option==2)
                    {
                        answer = ask("\nSearch book by:\n1.title\n2.author\n3.year\nOption: ");
                        option = atoi(answer);
                        free(answer);
                        if(option==1)
                        {
                            answer = ask("\nEnter the title: ");
                            found = find_book_by_title (answer);
                            free(answer);
                            // printf("\nID\ttitle\tauthors\tyear\tcopies\n");
                            // printf("%d\t%s\t%s\t%d\t%d\n", found.id, found.title, found.authors, found.year, found.copies);
                        }
                        else if(option==2)
                        {
                            answer = ask("\nEnter the authors: ");
                            found = find_book_by_title (answer);
                            free(answer);
                            // printf("\nID\ttitle\tauthors\tyear\tcopies\n");
                            // printf("%d\t%s\t%s\t%d\t%d\n", found.id, found.title, found.authors, found.year, found.copies);
                        }
                        else if(option==3)
                        {
                            answer = ask("\nEnter the year: ");
                            num = atoi(answer);
                            free(answer);
                            found = find_book_by_year (num);
                            // printf("\nID\ttitle\tauthors\tyear\tcopies\n");
                            // printf("%d\t%s\t%s\t%d\t%d\n", found.id, found.title, found.authors, found.year, found.copies);
                        }
                        else
                        printf("\nNo such command\n");
                    }
                    else if(option==3)
                    {
                        answer = ask("\nEnter the title of the book you would like to borrow: ");
                        borrowBook(oper, answer);
                        free(answer);
                    }
                    else if(option==4)
                    {
                        answer = ask("\nEnter the title of the book you would like to return: ");
                        returnRefresh(oper, answer);
                        free(answer);
                    }
                    else if(option==5)
                    break;
                    else
                    printf("\nNo such command\n");
                }
            }
        }
        //register module
        else if(option==2)
        registerUser();
        //exit
        else if(option==3)
        exit(0);
        else
        printf("\nNo such command\n");
    }
}