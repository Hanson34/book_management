#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "interface.h"
#include "book_management.h"
#include "reglog.h"

run_interface()
{
    int option;
    while(1)
    {
        printf("1.Login\n");
        printf("2.Register\n");
        printf("3.Exit\n");
        printf("Option:");
        scanf("%d", &option);
        info head = linkedList();
        if(option==1)
        {
            login(head);
            if(login(head)==1)
            {
                while(1)
                {
                    printf("");
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