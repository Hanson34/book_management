#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "interface.h"
#include "book_management.h"
#include "reglog.h"

void run_interface()
{
    int option;
    while(1)
    {
        printf("\n1.Login\n");
        printf("2.Register\n");
        printf("3.Exit\n");
        printf("Option:");
        scanf("%d", &option);
        info head = linkedList();
        if(option==1)
        {
            int op;
            login(head);
            op=login(head);
            if(op==1)
            {
                while(1)
                {
                    printf("\n(Administrator)\n");
                    printf("1.Display all books\n");
                    printf("2.Search a book\n");
                    printf("3.Add a book\n");
                    printf("4.Remove a book\n");
                    printf("5.Exit\n");
                    printf("Option:");
                    scanf("%d", &option);
                    if(option==1)
                    displayBooks();
                    else if(option==2)
                    {
                        BookArray *found = (BookArray *)malloc(sizeof(BookArray));
                        char name[20];
                        int year;
                        printf("\nSearch book by:\n");
                        printf("1.title\n2.author\n3.year\nOption:");
                        scanf("%d", &option);
                        if(option==1)
                        {
                            printf("\nEnter the title:");
                            scanf("%s", name);
                            found = find_book_by_title (name);
                            printf("\nID\ttitle\tauthors\tyear\tcopies\n");
                            printf("%d\t%s\t%s\t%d\t%d\n", found->array->id, found->array->title, found->array->authors, found->array->year, found->array->copies);
                        }
                        else if(option==2)
                        {
                            printf("\nEnter the author:");
                            scanf("%s", name);
                            found = find_book_by_author (name);
                            printf("\nID\ttitle\tauthors\tyear\tcopies\n");
                            printf("%d\t%s\t%s\t%d\t%d\n", found->array->id, found->array->title, found->array->authors, found->array->year, found->array->copies);
                        }
                        else if(option==3)
                        {
                            printf("\nEnter the year:");
                            scanf("%d", year);
                            found = find_book_by_year (year);
                            printf("\nID\ttitle\tauthors\tyear\tcopies\n");
                            printf("%d\t%s\t%s\t%d\t%d\n", found->array->id, found->array->title, found->array->authors, found->array->year, found->array->copies);
                        }
                        else
                        printf("\nNo such command\n");
                    }
                }
            }
            if(op==2)
            {
                while(1)
                {
                    printf("\n1.Display all books\n");
                    printf("2.Search a book\n");
                    printf("3.Borrow a book\n");
                    printf("4.Return a book\n");
                    printf("5.Exit\n");
                    printf("Option:");
                    scanf("%d", &option);
                }
            }
        }
        else if(option==2)
        registerUser(head);
        else if(option==3)
        {
            save(head);
            exit(0);
        }
    }
}