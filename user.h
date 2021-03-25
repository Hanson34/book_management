#ifndef USER_GUARD__H
#define USER_GUARD__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    char username[20];
    char password[20];
}User;

User userlist[30];

//login function
User login();

//verify the username & password, identity as well
int verification(User v);

//save to txt
void save(User save);

//load from specfic file
void loaduser();

//register function
int registerUser();

#endif