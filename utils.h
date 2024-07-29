#ifndef UTILS_H
#define UTILS_H

#include "account.h"
#include <stddef.h>

// Declare all functions used across multiple files
void enter_identifiers(char *identifier, char *password);
int connect();

void	generateIdentifier(char *str, int length);
void	create_new_acc();
void	registr();
char *get_line(int index);
char *get_balance(char *line);


int welcome();
void add_account(char *id, char *password);
int verify_account(char *id, char *password);

int operations();

#endif // UTILS_H
