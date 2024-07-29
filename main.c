#include "utils.h"
#include <stdio.h>

int main()
{
    while (1)
    {
        if (welcome())
        {
            int value = connect();
            if (value)
                operations(value);
        }
        else
            registr();
    }
}