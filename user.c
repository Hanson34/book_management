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

//login function
User login()
{
    char name[20], username[20], password[20];
    printf("\nUsername:");
    scanf("%s",username);
    printf("Password:");
    scanf("%s",password);
    //create a user to store string
    User login;
    strcpy(login.username, username);
    strcpy(login.password, password);
    //return the User to veri module
    return login;
}

//verify the username & password, identity as well
int verification(User v)
{
    //loan the userlist
    loaduser();
    for(int i=0; i<30; i++)
    {
        //check the username and password
        if(strcmp(v.username, "admin")==0 && strcmp(v.password, "admin")==0)
        {
            printf("\nWelcome admin\n");
            getchar();
            //1 when admin
            return 1;
        }
        if(strcmp(userlist[i].username, v.username)==0 && strcmp(userlist[i].password, v.password)==0)
        {
            printf("\nWelcome to the library\n");
            getchar();
            //2 when student
            return 2;
        }
    }
    printf("\nLogin failed\n");
    getchar();
    return 0;
}

//save to txt
void saveuser(User save)
{
    FILE *file = fopen("user.txt", "a+");
    fprintf(file, "%s\t%s\t%s", save.name, save.username, save.password);
    fprintf(file, "\n");
    fclose(file);
}

//load from specfic file
void loaduser()
{
    FILE *file = fopen("user.txt", "r+");
    for(int i=0; i<30; i++)
    fscanf(file, "%s\t%s\t%s\n", userlist[i].name, userlist[i].username, userlist[i].password);
    fclose(file);
}

//register function
int registerUser()
{
    //load the userlist
    loaduser();
    char name[20], username[20], password[20];
    //a user for string
    User regi;
    printf("\nStudent name:");
    scanf("%s",name);
    getchar();
    strcpy(regi.name, name);
    // check if exists in the list
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
    //save it into the txt
    saveuser(regi);
    printf("\nSuccessful registration\n");
    return 1;
}
