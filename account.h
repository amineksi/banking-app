#ifndef ACCOUNT_H
#define ACCOUNT_H

#define MAX_ID_LENGTH 11
#define MAX_PASSWORD_LENGTH 50


typedef struct {
    char id[MAX_ID_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int balance;
} Account;

void add_account(char *id, char *password);
int verify_account(char *id, char *password);
int	verify_id(char *id);

#endif