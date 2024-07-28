#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IDENTIFIER_MAX_LENGTH 100
#define PASSWORD_MAX_LENGTH 100

int contains_credential(char *credentials[], char *identifier, int size) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(credentials[i], identifier) == 0) {
            return i; 
        }
    }
    return -1;
}

int connect() {
    char identifier[IDENTIFIER_MAX_LENGTH];
	char password[PASSWORD_MAX_LENGTH];
    char *credentials[8] = {
        "lFzXVo",
        "eMpKqTjUr",
        "rAeiPdX",
        "BjxQTuDfLm",
        "HqNpsZr",
        "TvNxPwGuHk",
        "XvKpLeF"
    };
	char *passwords[8] = {
        "password1",
        "password2",
        "password3",
        "password4",
        "password5",
        "password6",
        "password7",
        "examplePass"
    };

	int credentials_size = sizeof(credentials) / sizeof(credentials[0]);

    printf("Hello, please enter your credentials.\nIdentifier: ");
    if (fgets(identifier, IDENTIFIER_MAX_LENGTH, stdin) != NULL) {
        // Remove trailing newline character
        size_t len = strlen(identifier);
        if (len > 0 && identifier[len - 1] == '\n') {
            identifier[len - 1] = '\0';
        }
    }
	int index = contains_credential(credentials, identifier, credentials_size);
    while (index == -1) {
        printf("This identifier doesn't exist, please try again.\nIdentifier: ");
        if (fgets(identifier, IDENTIFIER_MAX_LENGTH, stdin) != NULL) {
            // Remove trailing newline character
            size_t len = strlen(identifier);
            if (len > 0 && identifier[len - 1] == '\n') {
                identifier[len - 1] = '\0';
            }
        }
		index = contains_credential(credentials, identifier, credentials_size);
    }

	printf("Password: ");
	if (fgets(password, IDENTIFIER_MAX_LENGTH, stdin) != NULL) {
    	// Remove trailing newline character
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    while (strcmp(passwords[index], password) != 0) {
        printf("Wrong password, please try again.\nPassword : ");
        if (fgets(password, PASSWORD_MAX_LENGTH, stdin) != NULL) {
            // Remove trailing newline character
            size_t len = strlen(password);
            if (len > 0 && password[len - 1] == '\n') {
                password[len - 1] = '\0';
            }
        }
    }
	printf("Successfully connected.");
    return 0;
}