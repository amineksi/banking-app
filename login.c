#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define IDENTIFIER_MAX_LENGTH 10
#define PASSWORD_MAX_LENGTH 50

void flush_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int enter_indentifiers(char *identifier, char *password)
{
    char choice[2];
    while (choice[0] != 'y' && choice[0] != 'n')
    {
        printf("Do you wish to log in ? (y/n) : ");
        if (fgets(choice, 2, stdin) != NULL)
        {
            size_t len = strlen(choice);
            if (len > 0 && choice[len - 1] == '\n')
                choice[len - 1] = '\0';
            else
                flush_input_buffer(); // Clear remaining input buffer
        }
    }
    if (choice[0] == 'n')
        return 0;
    printf("\nPlease enter your credentials.\nIdentifier: ");
    if (fgets(identifier, IDENTIFIER_MAX_LENGTH + 1, stdin) != NULL)
    {
        size_t len = strlen(identifier);
        if (len > 0 && identifier[len - 1] == '\n')
            identifier[len - 1] = '\0';
        else
            flush_input_buffer(); // Clear remaining input buffer
    }
    printf("Password: ");
    if (fgets(password, PASSWORD_MAX_LENGTH + 1, stdin) != NULL)
    {
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n')
            password[len - 1] = '\0';
        else
            flush_input_buffer(); // Clear remaining input buffer
    }
}

int connect()
{
    char identifier[IDENTIFIER_MAX_LENGTH + 1];
    char password[PASSWORD_MAX_LENGTH + 1];
    
    int choice = enter_indentifiers(identifier, password);
    int check = verify_account(identifier, password);
    while (choice && !check)
    {
        choice = enter_indentifiers(identifier, password);
        check = verify_account(identifier, password);
    }
    return check;
}