#include "account.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 150 // Assuming each line will not exceed 150 characters
#define CHARS_TO_READ 10
#define DATABASE_FILE "accounts.txt"

void overwrite_line(int line_index, char *new_content) 
{
    FILE *file = fopen(DATABASE_FILE, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    line_index--;
    // Read the entire file into memory
    char **lines = NULL;
    size_t count = 0;
    char buffer[100];
    while (fgets(buffer, 100, file)) {
        lines = realloc(lines, sizeof(char*) * (count + 1));
        lines[count] = strdup(buffer);
        count++;
    }
    fclose(file);

    // Overwrite the specific line
    if (line_index >= 0 && line_index < count) {
        free(lines[line_index]);
        lines[line_index] = malloc(strlen(new_content) + 2); // +1 for '\n' and +1 for '\0'
        strcpy(lines[line_index], new_content);
        strcat(lines[line_index], "\n");
    } else {
        printf("Line index out of range\n");
    }

    // Write the content back to the file
    file = fopen(DATABASE_FILE, "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    for (size_t i = 0; i < count; i++) {
        fputs(lines[i], file);
        free(lines[i]);
    }
    free(lines);
    fclose(file);
}

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

char *get_line(int index)
{
	FILE *file = fopen(DATABASE_FILE, "r");
	if (!file)
	{
		perror("Error opening file");
		return NULL;
	}

	char line[MAX_LINE_LENGTH];
	int count = 1;
	char *result = NULL;

	while (fgets(line, sizeof(line), file))
	{
		// Remove newline character if present
		size_t len = strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';

		if (count == index)
		{
			result = malloc(len);
			if (result)
				strcpy(result, line);
			break;
		}
		count++;
	}
	fclose(file);
	return result;
}

char *get_balance(char *line)
{
    char *copy = strdup(line); // Make a copy of the line to avoid modifying the original string
    if (!copy)
    {
        perror("Error duplicating line");
        return NULL;
    }

    char *token = strtok(copy, " ");
    int token_count = 1;
    char *result = NULL;

    while (token != NULL)
    {
        if (token_count == 3)
        {
            result = malloc(strlen(token) + 1);  // Allocate memory for the third string
            if (result)
                strcpy(result, token);  // Copy the third string to the allocated memory
            break;
        }
        token = strtok(NULL, " ");
        token_count++;
    }

    free(copy); // Free the duplicated line

    return result;
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
	FILE *file = fopen(DATABASE_FILE, "r");
	if (!file)
	{
		perror("Error opening file");
		return 0;
	}

	char line[MAX_LINE_LENGTH];
	int count = 1;
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
		{
			int i = 11, len_pass = 0;
			while (line[i++] != ' ')
				len_pass++;

			char line_password[len_pass];
			strncpy(line_password, &line[11], len_pass);
			line_password[len_pass] = '\0';
			
			if (strncmp(password, line_password, len_pass) == 0)
			{
				fclose(file);
				return count;
			}
		}
		count++;
	}
	printf("Wrong identifier or username. Please try again.\n");
	fclose(file);
	return 0;
}