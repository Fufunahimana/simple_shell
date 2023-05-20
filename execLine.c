#include "shell.h"

/**
* exec_line - Function that finds builtins and commands
* @mydata: data relevant (args)
* Return: 1 on success.
*/
int exec_line(data_shell *mydata)
{
int (*builtin)(data_shell *mydata);

if (mydata->args[0] == NULL)
return (1);

builtin = get_builtin(mydata->args[0]);

if (builtin != NULL)
return (builtin(mydata));

return (cmd_exec(mydata));
}
