#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void flush_input_buffr()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void view_balance(int line_idx)
{
    char *line = get_line(line_idx);
    
    char *balance = get_balance(line);

    printf("%s%s%s\n", "You currently have ", balance,"$.");
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
        /*if (choice[0] == 'o')
            transactions(line_idx);*/
        if (choice[0] == 'b')
            view_balance(line_idx);
    }
}