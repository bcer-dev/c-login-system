#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct _user
{
    char *uname;
    char *pass;
};

typedef struct _user user;

#define MAX_USERS 10
user USERS[MAX_USERS];
int user_count = 0;

enum _menu_options
{
    REGISTER, LOGIN
};

typedef enum _menu_options menu_options;

user *match_login_info(user *u)
{
    for (int i = 0; i < user_count; i++)
    {
        if (!(strcmp(USERS[i].uname, u->uname) || strcmp(USERS[i].pass, u->pass)))
        {
            return &USERS[i];
        }
    }
    return NULL;
}

bool username_taken(user *u)
{
    for (int i = 0; i < user_count; i++)
    {
        if (!strcmp(USERS[i].uname, u->uname))
        {
            return true;
        }
    }
    return false;
}

static void read_from_user(char *out_str, int max_len)
{
    int len = 0;
    char next;
    while ((next = fgetc(stdin)) != '\n' && len < max_len)
    {
        out_str[len++] = next;
    }

    out_str[len] = '\0';
}

#define MAX_UNAME_LEN 25
#define MAX_PASS_LEN 15

bool login(user *current_user)
{
    user temp;
    // Memory leak
    temp.uname = calloc(MAX_UNAME_LEN + 1, sizeof(char));
    temp.pass = calloc(MAX_PASS_LEN + 1, sizeof(char));

    printf("Username: ");
    read_from_user(temp.uname, MAX_UNAME_LEN);

    printf("Password: ");
    read_from_user(temp.pass, MAX_PASS_LEN);

    user *match = match_login_info(&temp);

    if (match == NULL)
    {
        printf("\n");
        printf("\nIncorrect username or password\n\n");
        return false;
    }

    *current_user = *match;

    free(temp.uname);
    free(temp.pass);
    return true;
}

bool register_user()
{
    if (user_count == MAX_USERS)
    {
        printf("\nMaximum amount of users has been reached!\n\n");
        return false;
    }

    user temp;
    temp.uname = calloc(MAX_UNAME_LEN + 1, sizeof(char));
    temp.pass = calloc(MAX_PASS_LEN + 1, sizeof(char));

    printf("Username: ");
    read_from_user(temp.uname, MAX_UNAME_LEN);

    printf("Password: ");
    read_from_user(temp.pass, MAX_PASS_LEN);

    if (username_taken(&temp))
    {
        printf("\nUsername already taken.\n\n");
        return false;
    }

    USERS[user_count++] = temp;
    return true;
}


int main()
{
    user current_user;
    int selected_action;
    
    printf("### Login System ###\n\n");

    while (1)
    {
        printf("Would you like to: \n");
        printf("1 - Register\n");
        printf("2 - Log In\n");
        printf("\n> ");
        scanf("%d", &selected_action);
        fgetc(stdin); // Remove newline from buffer

        switch (selected_action - 1)
        {
        case REGISTER:
            if (register_user())
            {
                printf("\nUser created successfully.\n\n");
            }
            break;

        case LOGIN:
            if (login(&current_user))
            {
                printf("\nWelcome, %s! Logged in successfully!\n\n", current_user.uname);
                goto cleanup;
            }
            break;
        
        default:
            printf("Invalid option.\n");
            break;
        }
    }

cleanup:
    for (int i = 0; i < user_count; i++)
    {
        free(USERS[i].uname);
        free(USERS[i].pass);
    }

    return 0;
}