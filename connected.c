#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"
#include <ctype.h>

void flush_input_buffr()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void change_balance(char *line, int line_idx, char *balance, char *amount, int neg)
{
    if (balance == NULL)
    {
        printf("Failed to get balance.\n");
        return;
    }

    int balance_value = atoi(balance);
    int amount_value = atoi(amount) * neg;

    sprintf(balance, "%d", balance_value + amount_value);
    printf("Updated balance: %s\n", balance);

    int i = 11;
    while (line[i] != ' ')
        i++;
    strncpy(&line[i + 1], balance, sizeof(balance));
    overwrite_line(line_idx, line);

    free(balance);
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
    change_balance(line, line_idx, balance, amount, 1);
}

void give_money(int line_idx)
{
    char **list_id;
    char *line;
    char *owner_balance;
    int i = 1;
    int j = 0;
    printf("Which account do you wish to send money to ?\n");
    while (get_line(i))
        i++;

    list_id = malloc(sizeof(char *) * (i));
    if (!list_id)
        return;
    list_id[i - 1] = '\0';

    while (j < i - 1)
    {
        line = get_line(j + 1);
        list_id[j] = malloc(11);
        if (!list_id[j])
            return;
        strncpy(list_id[j], line, 10);
        list_id[j][10] = '\0';
        if (strncmp(line, get_line(line_idx), 10) != 0)
            printf("%s\n", list_id[j]);
        j++;
    }
    char choice[11];
    char *receiver_balance = NULL;
    while (!receiver_balance)
    {
        if (fgets(choice, 11, stdin) != NULL)
        {
            size_t len = strlen(choice);
            if (len > 0 && choice[len - 1] == '\n')
            {
                choice[len - 1] = '\0';
            }
            else
                flush_input_buffr(); // Clear remaining input buffer
        }
        j = 0;
        while (j < i - 1)
        {
            if (strncmp(choice, list_id[j], 10) == 0)
            {
                receiver_balance = get_balance(get_line(j + 1));
                break;
            }
            j++;
        }
        if (!receiver_balance)
            printf("Wrong input, please try again.\n");
    }
    
    owner_balance = get_balance(get_line(line_idx));
    if (!owner_balance)
        return;
    
    char amount[10];
    int over = 0;
    while (!over)
    {
        printf("%s%s%s\n","You currently have ", owner_balance, "$.\nHow much money do you wish to transfer ?");
        if (fgets(amount, 10, stdin) != NULL)
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
                    amount == NULL;
                    over = 0;
                    break ;
                }
                else
                    over = 1;
            }
            if (atoi(amount) > atoi(owner_balance) && over)
            {
                printf("You don't have enough money, please try again.\n");
                amount == NULL;
                over = 0;
            }
        }
    }
    
    change_balance(get_line(line_idx), line_idx, owner_balance, amount, -1);
    
    change_balance(get_line(j+1), j+1, receiver_balance, amount, 1);

    printf("Transaction succesfully done !\n");
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
            return;
        if (choice[0] == 'f')
            fill_account(line_idx);
        if (choice[0] == 's')
            give_money(line_idx);
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