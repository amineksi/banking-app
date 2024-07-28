#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IDENTIFIER_MAX_LENGTH 100
#define PASSWORD_MAX_LENGTH 100

int contains_credential(char **credentials, char *identifier) {
    int i = 0;
    while (credentials[i]){
        if (strcmp(credentials[i], identifier) == 0) {
            return i; 
        }
        i+=1;
    }
    return -1;
}

int connect(char **credentials, char **passwords) {
    char identifier[IDENTIFIER_MAX_LENGTH];
	char password[PASSWORD_MAX_LENGTH];

    printf("Please enter your credentials.\nIdentifier: ");
    if (fgets(identifier, IDENTIFIER_MAX_LENGTH, stdin) != NULL) {
        size_t len = strlen(identifier);
        if (len > 0 && identifier[len - 1] == '\n') {
            identifier[len - 1] = '\0';
        }
    }
	int index = contains_credential(credentials, identifier);
    while (index == -1) {
        printf("This identifier doesn't exist, please try again.\nIdentifier: ");
        if (fgets(identifier, IDENTIFIER_MAX_LENGTH, stdin) != NULL) {
            size_t len = strlen(identifier);
            if (len > 0 && identifier[len - 1] == '\n') {
                identifier[len - 1] = '\0';
            }
        }
		index = contains_credential(credentials, identifier);
    }

	printf("Password: ");
	if (fgets(password, IDENTIFIER_MAX_LENGTH, stdin) != NULL) {
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    while (strcmp(passwords[index], password) != 0) {
        printf("Wrong password, please try again.\nPassword : ");
        if (fgets(password, PASSWORD_MAX_LENGTH, stdin) != NULL) {
            size_t len = strlen(password);
            if (len > 0 && password[len - 1] == '\n') {
                password[len - 1] = '\0';
            }
        }
    }
	printf("Successfully connected.");
    return 0;
}