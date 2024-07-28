#ifndef ACCOUNT_H
#define ACCOUNT_H

#define MAX_ID_LENGTH 10
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char id[MAX_ID_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} Account;

void add_account(char *id, char *password);
int verify_account(char *id, char *password);
#endif