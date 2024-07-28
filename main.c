#include "utils.h"
#include <stdio.h>

int main()
{
    while (1)
    {
        if (welcome())
            if (connect())
                operations();
        else
            registr();
    }
}