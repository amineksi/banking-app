#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define IDENTIFIER_MAX_LENGTH 10
#define PASSWORD_MAX_LENGTH 50

void flush_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void enter_indentifiers(char *identifier, char *password)
{
    printf("Please enter your credentials.\nIdentifier: ");
    if (fgets(identifier, IDENTIFIER_MAX_LENGTH + 1, stdin) != NULL)
    {
        size_t len = strlen(identifier);
        if (len > 0 && identifier[len - 1] == '\n')
        {
            identifier[len - 1] = '\0';
        }
        else
            flush_input_buffer(); // Clear remaining input buffer
    }
    printf("Password: ");
    if (fgets(password, PASSWORD_MAX_LENGTH + 1, stdin) != NULL)
    {
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n')
        {
            password[len - 1] = '\0';
        }
        else
            flush_input_buffer(); // Clear remaining input buffer
    }
}

int connect()
{
    char identifier[IDENTIFIER_MAX_LENGTH + 1];
    char password[PASSWORD_MAX_LENGTH + 1];

    enter_indentifiers(identifier, password);
    while (!verify_account(identifier, password))
        enter_indentifiers(identifier, password);
    printf("Successfully connected.\n");
    return 0;
}