#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define IDENTIFIER_MAX_LENGTH 10
#define PASSWORD_MAX_LENGTH 50

void    enter_indentifiers(char *identifier, char *password)
{
    printf("Please enter your credentials.\nIdentifier: ");
    if (fgets(identifier, IDENTIFIER_MAX_LENGTH, stdin) != NULL) {
        size_t len = strlen(identifier);
        if (len > 0 && identifier[len - 1] == '\n') {
            identifier[len - 1] = '\0';
        }
    }
    printf("Password: ");
	if (fgets(password, IDENTIFIER_MAX_LENGTH, stdin) != NULL) {
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }
}
int connect() {
    char identifier[IDENTIFIER_MAX_LENGTH];
	char password[PASSWORD_MAX_LENGTH];

    enter_indentifiers(identifier, password);
    while (!verify_account(identifier, password))
        enter_indentifiers(identifier, password);
	printf("Successfully connected.");
    return 0;
}