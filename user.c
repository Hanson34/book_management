#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"

// typedef struct {
//     char name[20];
//     char username[20];
//     char password[20];
// }User;

// User list[30];

User login()
{
    char name[20], username[20], password[20];
    printf("\nUsername:");
    scanf("%s",username);
    printf("Password:");
    scanf("%s",password);
    User login;
    strcpy(login.username, username);
    strcpy(login.password, password);
    return login;
}

int verification(User v)
{
    loaduser();
    for(int i=0; i<30; i++)
    {
        //check the username and password
        if(strcmp(v.username, "admin")==0 && strcmp(v.password, "admin")==0)
        {
            printf("\nWelcome admin\n");
            getchar();
            return 1;
        }
        if(strcmp(userlist[i].username, v.username)==0 && strcmp(userlist[i].password, v.password)==0)
        {
            printf("\nWelcome to the library\n");
            getchar();
            return 2;
        }
    }
    printf("\nLogin failed\n");
    getchar();
    return 0;
}

void saveuser(User save)
{
    FILE *file = fopen("user.txt", "a+");
    fprintf(file, "%s\t%s\t%s", save.name, save.username, save.password);
    fprintf(file, "\n");
    fclose(file);
}

void loaduser()
{
    FILE *file = fopen("user.txt", "r+");
    for(int i=0; i<30; i++)
    fscanf(file, "%s\t%s\t%s\n", userlist[i].name, userlist[i].username, userlist[i].password);
    fclose(file);
}

int registerUser()
{
    loaduser();
    char name[20], username[20], password[20];
    User regi;
    printf("\nStudent name:");
    scanf("%s",name);
    getchar();
    strcpy(regi.name, name);
    for(int i=0; i<30; i++)
    {
        if(strcmp(userlist[i].name, name)==0)
        {
            printf("\nStudent exists\n");
            return 0;
        }
    }
    printf("Username:");
    scanf("%s",username);
    getchar();
    strcpy(regi.username, username);
    for(int i=0; i<30; i++)
    {
        if(strcmp(userlist[i].username, username)==0)
        {
            printf("\nStudent exists\n");
            return 0;
        }
    }
    printf("Password:");
    scanf("%s",password);
    getchar();
    strcpy(regi.password, password);
    saveuser(regi);
    printf("\nSuccessful registration\n");
    getchar();
    return 1;
}
