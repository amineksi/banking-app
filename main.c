#include "utils.h"

int main()
{
    char *credentials[8] = {
        "lFzXVo",
        "eMpKqTjUr",
        "rAeiPdX",
        "BjxQTuDfLm",
        "HqNpsZr",
        "TvNxPwGuHk",
        "XvKpLeF"
    };
	char *passwords[8] = {
        "password1",
        "password2",
        "password3",
        "password4",
        "password5",
        "password6",
        "password7",
        "examplePass"
    };
    while (1)
    {
        if (welcome())
            connect(credentials, passwords);
        else
            registr(credentials, passwords);
    }
}