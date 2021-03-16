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
    printf("1.Login\n");
    printf("2.Register\n");
    printf("3.Exit\n");
    printf("Option:");
    scanf("%d", &option);
    info head = linkedList();
    while(1)
    {
        if(option==1)
        {
            login(head);
        }
        else if(option==2)
        registerUser(head);
        else if(option==3)
        {
            save(head);
            return 0;
        }
        else
        return 0;
    }
}