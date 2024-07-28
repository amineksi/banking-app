#include "account.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#define DATABASE_FILE "accounts.txt"

int verify_id(char *id)
{
	Account account;

	FILE *file = fopen(DATABASE_FILE, "ab");
	if (!file)
	{
		write(2, "Error opening file\n", 19);
		return 0;
	}
	while (fread(&account, sizeof(Account), 1, file))
	{
		if (strncmp(account.id, id, MAX_ID_LENGTH) == 0)
		{
			fclose(file);
			return 0;
		}
	}
	fclose(file);
	return 1;
}

void add_account(char *id, char *password)
{
	Account account;

	// Copy the id and password, ensuring null-termination
	strncpy(account.id, id, MAX_ID_LENGTH - 1);
	account.id[MAX_ID_LENGTH - 1] = '\0';
	strncpy(account.password, password, MAX_PASSWORD_LENGTH - 1);
	account.password[MAX_PASSWORD_LENGTH - 1] = '\0';
	account.balance = 0;

	FILE *file = fopen(DATABASE_FILE, "a");
	if (!file)
	{
		perror("Error opening file");
		return;
	}

	// Write the account data as a single line: "id password\n"
	fprintf(file, "%s %s %d\n", account.id, account.password, account.balance);

	fclose(file);
	printf("Account added successfully.\n");
}

int verify_account(char *id, char *password)
{
	Account account;

	FILE *file = fopen(DATABASE_FILE, "rb");
	if (!file)
	{
		write(2, "Error opening file\n", 19);
		return 0;
	}

	while (fread(&account, sizeof(Account), 1, file))
	{
		if (strncmp(account.id, id, MAX_ID_LENGTH) == 0 &&
			strncmp(account.password, password, MAX_PASSWORD_LENGTH) == 0)
			fclose(file);
		return 1;
	}
	fclose(file);
	printf("Wrong username or password.\n");
	return 0;
}