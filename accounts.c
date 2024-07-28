#include "account.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 150 // Assuming each line will not exceed 150 characters
#define CHARS_TO_READ 10
#define DATABASE_FILE "accounts.txt"

int verify_id(char *id)
{
	FILE *file = fopen(DATABASE_FILE, "r");
	if (!file)
	{
		perror("Error opening file");
		return 0;
	}

	char line[MAX_LINE_LENGTH];
	while (fgets(line, sizeof(line), file))
	{
		// Remove newline character if present
		size_t len = strlen(line);
		if (len > 0 && line[len - 1] == '\n')
		{
			line[len - 1] = '\0';
		}

		char first_10_chars[CHARS_TO_READ + 1];
		strncpy(first_10_chars, line, CHARS_TO_READ);
		first_10_chars[CHARS_TO_READ] = '\0'; // Ensure null-termination

		// Compare the input with the first 10 characters of the line
		if (strncmp(id, first_10_chars, CHARS_TO_READ) == 0)
			return 0;
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