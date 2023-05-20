#include "shell.h"

/**
* get_error - Function that calls the error
* according the builtin, syntax or permission
* @mydata: data structure that contains arguments
* @e: error value
* Return: error
*/
int get_error(data_shell *mydata, int e)
{
char *error;

switch (e)
{
case -1:
error = error_env(mydata);
break;
case 126:
error = error_path_126(mydata);
break;
case 127:
error = error_not_found(mydata);
break;
case 2:
if (_strcmp("exit", mydata->args[0]) == 0)
error = error_exit_shell(mydata);
else if (_strcmp("cd", mydata->args[0]) == 0)
error = error_get_cd(mydata);
break;
}

if (error)
{
write(STDERR_FILENO, error, _strlen(error));
free(error);
}

mydata->status = e;
return (e);
}
