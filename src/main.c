#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct user
{
    char *uname;
    char *pass;
};

typedef struct user user;

/*
    "
    Hello World!\n
    Username Password\n
    First last\n
    "

    while not eof
        while c not \n
            add c to str
            strcmp str, username
*/

char *load_users()
{
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL)
    {
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    int fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *str = malloc(sizeof(char) * fsize + 1);
    if (str == NULL)
    {
        return NULL;
    }

    int len = 0;
    char buffer;
    while (fread(&buffer, sizeof(char), 1, fp))
    {
        str[len++] = buffer;
    }

    fclose(fp);
    
    str[len] = '\0';
    return str;
}

/*
    for every line
        lstart = line[0]
        while line[lend] != '\n'
            lend++
*/

bool user_registered(user *u, char *file_data)
{
    int line_start = 0;
    int line_end = 0;
}

void login(user *current_user)
{
    char *name = malloc(sizeof(char) * 120);
    char *pass = malloc(sizeof(char) * 120);
    scanf("%s", name);
    scanf("%s", pass);


}

/*
    extract:
        read name
        read pass
    to:
        Read()
*/

/*
    Login()
        read name
        read pass

        if not name.registered then
            echo "User doesn't exist!"
            return -1

        current_user = user(name, pass)
*/

/*
    Register()
        read name
        read pass

        if name.registered then
            echo "Username already in use."
            return -1
        
        current_user = user(name, pass)
*/

/*
    SaveUser(name, pass)
        open file
        file.write name + " " + pass
*/

/*
    LoadUsers()
        str = file.read() >> heap
        return str
*/

int main()
{
    char *users = load_users();
    if (users == NULL)
    {
        fprintf(stderr, "Failed to load users.\n");
        return -1;
    }

    printf("%s\n", users);
    return 0;
}