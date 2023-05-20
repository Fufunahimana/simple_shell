#include "shell.h"

/**
* error_env - that function shows an error
* message for env in get_env.
* @mydata: data relevant (counter, arguments)
* Return: error message.
*/
char *error_env(data_shell *mydata)
{
int length;
char *error;
char *ver_str;
char *msg;

ver_str = aux_itoa(mydata->counter);
msg = ": Unable to add/remove from environment\n";
length = _strlen(mydata->av[0]) + _strlen(ver_str);
length += _strlen(mydata->args[0]) + _strlen(msg) + 4;
error = malloc(sizeof(char) * (length + 1));
if (error == 0)
{
free(error);
free(ver_str);
return (NULL);
}

_strcpy(error, mydata->av[0]);
_strcat(error, ": ");
_strcat(error, ver_str);
_strcat(error, ": ");
_strcat(error, mydata->args[0]);
_strcat(error, msg);
_strcat(error, "\0");
free(ver_str);

return (error);
}
/**
* error_path_126 - That function shows an error
* message for path and failure denied permission.
* @mydata: data relevant (counter, arguments).
*
* Return: The error string.
*/
char *error_path_126(data_shell *mydata)
{
int length;
char *ver_str;
char *error;

ver_str = aux_itoa(mydata->counter);
length = _strlen(mydata->av[0]) + _strlen(ver_str);
length += _strlen(mydata->args[0]) + 24;
error = malloc(sizeof(char) * (length + 1));
if (error == 0)
{
free(error);
free(ver_str);
return (NULL);
}
_strcpy(error, mydata->av[0]);
_strcat(error, ": ");
_strcat(error, ver_str);
_strcat(error, ": ");
_strcat(error, mydata->args[0]);
_strcat(error, ": Permission denied\n");
_strcat(error, "\0");
free(ver_str);
return (error);
}
