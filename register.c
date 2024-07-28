#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define IDENTIFIER_MAX_LENGTH 10
#define PASSWORD_MAX_LENGTH 50

int generateIdentifier(char *str, size_t length)
{
	char charset[] = "0123456789";

	for (size_t i = 0; i < 10; i++)
	{
		int key = rand() % sizeof(charset);
		str[i] = charset[key];
	}
	str[length] = '\0';
}

int generatePassword(char *password, size_t length)
{
	char *confirmPassword;

	printf("Enter your password : ");
	if (fgets(password, PASSWORD_MAX_LENGTH, stdin) != NULL) {
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

	printf("Confirm your password : ");
	if (fgets(confirmPassword, PASSWORD_MAX_LENGTH, stdin) != NULL) {
        size_t len = strlen(confirmPassword);
        if (len > 0 && confirmPassword[len - 1] == '\n') {
            confirmPassword[len - 1] = '\0';
        }
    }
	if (strncmp(password, confirmPassword, PASSWORD_MAX_LENGTH) == 0)
		return 1;
	return 0;
}

void create_new_acc()
{
	char identifier[IDENTIFIER_MAX_LENGTH + 1];
	char password[PASSWORD_MAX_LENGTH + 1];
	generateIdentifier(identifier, 11);
	
	printf("%s\n", identifier);

	while (!verify_id(identifier))
		generateIdentifier(identifier, 11);
	
	printf("%s%s\n", "Your identifier is : ",identifier);
	while (!generatePassword(password, PASSWORD_MAX_LENGTH + 1))
		printf("Passwords don't match.\n");
	add_account(identifier, password);

}

void registr()
{
	char choice[3];
	printf("Are you sure you want to create a new account? (Enter 1 if yes, else 0.)\n");
	fgets(choice, sizeof(choice), stdin);
	while (choice[0] != '0' && choice[0] != '1')
	{
		printf("Wrong value. 0 to leave, 1 to register.");
		fgets(choice, sizeof(choice), stdin);
	}

	if (choice[0] == '1')
		create_new_acc();
}