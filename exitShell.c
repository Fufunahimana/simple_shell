#include "shell.h"

/**
* exit_shell -Function that exits the shell
* @mydata: data relevant (status and args)
* Return: 0 on success.
*/
int exit_shell(data_shell *mydata)
{
unsigned int ustatus;
int is_digit;
int str_len;
int big_number;

if (mydata->args[1] != NULL)
{
ustatus = _atoi(mydata->args[1]);
is_digit = _isdigit(mydata->args[1]);
str_len = _strlen(mydata->args[1]);
big_number = ustatus > (unsigned int)INT_MAX;
if (!is_digit || str_len > 10 || big_number)
{
get_error(mydata, 2);
mydata->status = 2;
return (1);
}
mydata->status = (ustatus % 256);
}
return (0);
}
