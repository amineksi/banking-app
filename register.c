#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IDENTIFIER_MAX_LENGTH 100

int	generateIdentifier(char **credentials, char *str, size_t length)
{
	char	charset[] = "0123456789";

	for (size_t i = 0; i < length; i++)
	{
		int key = rand() % sizeof(charset) - 1;
		str[i] = charset[key];
	}
	str[length] = '\0';
}

void	create_new_acc(char **credentials, char **passwords)
{
	char	identifier[10];

	generateIdentifier(credentials, identifier, 10);
	while (contains_credential(credentials, identifier) != -1)
		generateIdentifier(credentials, identifier, 10);
	printf("%s", identifier);
}

void	registr(char **credentials, char **passwords)
{
	char	choice[3];
	printf("Are you sure you want to create a new account? (Enter 1 if yes, else 0.)\n");
	fgets(choice, sizeof(choice), stdin);
	while (choice[0] != '0' && choice[0] != '1')
	{
		printf("Wrong value. 0 to leave, 1 to register.");
		fgets(choice, sizeof(choice), stdin);
	}

	if (choice[0] == '1')
		create_new_acc(credentials, passwords);
}