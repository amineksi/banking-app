#include "account.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define DATABASE_FILE "accounts.db"

void add_account(char *id, char *password)
{
	Account account;
	strncpy(account.id, id, MAX_ID_LENGTH);
	strncpy(account.password, password, MAX_PASSWORD_LENGTH);

	FILE *file = fopen(DATABASE_FILE, "ab");
	if (!file)
	{
		write(2, "Error opening file\n", 19);
		return;
	}

	fwrite(&account, sizeof(Account), 1, file);
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