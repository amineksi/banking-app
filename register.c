#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void generateIdentifier(char *str, int length)
{
	char charset[] = "0123456789";

    for (int i = 0; i < 10; i++) {
        int key = rand() % (sizeof(charset) - 1);
        str[i] = charset[key];
    }
    str[10] = '\0';
}

int generatePassword(char *password, int length) {
    char confirmPassword[MAX_PASSWORD_LENGTH + 1];

    printf("Enter your password: ");
    if (fgets(password, MAX_PASSWORD_LENGTH + 1, stdin) != NULL) {
        int len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    printf("Confirm your password: ");
    if (fgets(confirmPassword, MAX_PASSWORD_LENGTH + 1, stdin) != NULL) {
        int len = strlen(confirmPassword);
        if (len > 0 && confirmPassword[len - 1] == '\n') {
            confirmPassword[len - 1] = '\0';
        }
    }

    if (strcmp(password, confirmPassword) == 0)
        return 1;

    return 0;
}

void create_new_acc()
{
	char identifier[11];
	char password[MAX_PASSWORD_LENGTH + 1];
	
	generateIdentifier(identifier, MAX_ID_LENGTH);
	
	while (!verify_id(identifier))
		generateIdentifier(identifier, MAX_ID_LENGTH);
	
	printf("%s%s\n", "Your identifier is : ",identifier);

	while (!generatePassword(password, MAX_PASSWORD_LENGTH))
		printf("Passwords don't match.\n");

	add_account(identifier, password);

}

void registr()
{
	char choice[3];
	printf("Are you sure you want to create a new account? (y/n)\n");
	fgets(choice, sizeof(choice), stdin);
	while (choice[0] != 'y' && choice[0] != 'n')
	{
		printf("Wrong value. n to leave, y to register.");
		fgets(choice, sizeof(choice), stdin);
	}

	if (choice[0] == 'y')
		create_new_acc();
}