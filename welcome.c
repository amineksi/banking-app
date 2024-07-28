#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	welcome()
{
	char choice[3];
	printf("Welcome to our bank.\nType 0 to create a new account.\nType 1 to connect to an existing account\n");
	fgets(choice, sizeof(choice), stdin);
	while (choice[0] != '0' && choice[0] != '1')
	{
		printf("Wrong value. 0 to register, 1 to connect.");
		fgets(choice, sizeof(choice), stdin);
	}
	return (choice[0] - '0');
}