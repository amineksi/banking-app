#ifndef UTILS_H
#define UTILS_H

#include "account.h"
#include <stddef.h>

// Declare all functions used across multiple files
void enter_identifiers(char *identifier, char *password);
int connect();

int	generateIdentifier(char *str, size_t length);
void	create_new_acc();
void	registr();

int welcome();
void add_account(char *id, char *password);
int verify_account(char *id, char *password);

#endif // UTILS_H
