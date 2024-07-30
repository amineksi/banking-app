#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include <ctype.h>

void flush_input_buffr()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void fill_account(int line_idx)
{
    char amount[10];
    char *line;
    char *balance;

    printf("How much money do you wish to add to your account?\n");

    if (fgets(amount, sizeof(amount), stdin) != NULL)
    {
        size_t len = strlen(amount);
        if (len > 0 && amount[len - 1] == '\n')
            amount[len - 1] = '\0';
        else
            flush_input_buffr();

        for (size_t i = 0; i < strlen(amount); i++)
        {
            if (!isdigit(amount[i]))
            {
                printf("Invalid input. Please enter a numeric value.\n");
                return;
            }
        }
    }
    else
    {
        printf("Failed to read input.\n");
        return;
    }
    
    line = get_line(line_idx);
    balance = get_balance(line);

    if (balance == NULL)
    {
        printf("Failed to get balance.\n");
        return;
    }

    int balance_value = atoi(balance);
    int amount_value = atoi(amount);

    sprintf(balance, "%d", balance_value + amount_value);
    printf("Updated balance: %s\n", balance);

    int i = 11;
    while (line[i] != ' ')
        i++;
    strncpy(&line[i + 1], balance, sizeof(balance));
    overwrite_line(line_idx, line);

    free(balance);
}

void transactions(int line_idx)
{
    char choice[2];
    while (1)
    {
        printf("Do you wish to fill your account or send money to other accounts? (d to discard, f to fill, s to send)\n");
        if (fgets(choice, 2, stdin) != NULL)
        {
            size_t len = strlen(choice);
            if (len > 0 && choice[len - 1] == '\n')
            {
                choice[len - 1] = '\0';
            }
            else
                flush_input_buffr(); // Clear remaining input buffer
        }
        if (choice[0] == 'd')
            return ;
        if (choice[0] == 'f')
            fill_account(line_idx);
        /*if (choice[0] == 's')
            transactions(line_idx);*/
    }
}

void view_balance(int line_idx)
{
    char *line = get_line(line_idx);

    char *balance = get_balance(line);

    printf("%s%s%s\n", "You currently have ", balance, "$.");
}
int operations(int line_idx)
{
    char choice[2];
    while (1)
    {
        printf("What do you wish to do ? (l to logout, b to view your balance, o to make an operation.)\n");
        if (fgets(choice, 2, stdin) != NULL)
        {
            size_t len = strlen(choice);
            if (len > 0 && choice[len - 1] == '\n')
            {
                choice[len - 1] = '\0';
            }
            else
                flush_input_buffr(); // Clear remaining input buffer
        }
        if (choice[0] == 'l')
        {
            printf("Successfully logged out.\n");
            return 1;
        }
        if (choice[0] == 'b')
            view_balance(line_idx);
        if (choice[0] == 'o')
            transactions(line_idx);
    }
}