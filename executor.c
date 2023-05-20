#include "shell.h"

/**
* is_cdir - That function checks ":"
* if is in the current directory.
* @p: type char pointer char.
* @index: type int pointer of index.
* Return: 1 if the path is searchable in the cd, 0 otherwise.
*/
int is_cdir(char *p, int *index)
{
if (p[*index] == ':')
return (1);

while (p[*index] != ':' && p[*index])
{
*index += 1;
}

if (p[*index])
*index += 1;

return (0);
}

/**
* _which - Function that locates a command
* @cmd: command name
* @_environ: environment variable
* Return: location of the command.
*/
char *_which(char *cmd, char **_environ)
{
char *p, *ptr_path, *token_path, *dir;
int len_dir, len_cmd, i;
struct stat st;

p = _getenv("PATH", _environ);
if (p)
{
ptr_path = _strdup(p);
len_cmd = _strlen(cmd);
token_path = _strtok(ptr_path, ":");
i = 0;
while (token_path != NULL)
{
if (is_cdir(p, &i))
if (stat(cmd, &st) == 0)
return (cmd);
len_dir = _strlen(token_path);
dir = malloc(len_dir + len_cmd + 2);
_strcpy(dir, token_path);
_strcat(dir, "/");
_strcat(dir, cmd);
_strcat(dir, "\0");
if (stat(dir, &st) == 0)
{
free(ptr_path);
return (dir);
}
free(dir);
token_path = _strtok(NULL, ":");
}
free(ptr_path);
if (stat(cmd, &st) == 0)
return (cmd);
return (NULL);
}
if (cmd[0] == '/')
if (stat(cmd, &st) == 0)
return (cmd);
return (NULL);
}

/**
* is_executable - Function that determinesi
* f is an executable.
* @mydata: data structure
* Return: 0 if is not an executable, other number if it does
*/
int is_executable(data_shell *mydata)
{
struct stat st;
int k;
char *input;

input = mydata->args[0];
for (k = 0; input[k]; k++)
{
if (input[k] == '.')
{
if (input[k + 1] == '.')
return (0);
if (input[k + 1] == '/')
continue;
else
break;
}
else if (input[k] == '/' && k != 0)
{
if (input[k + 1] == '.')
continue;
k++;
break;
}
else
break;
}
if (k == 0)
return (0);

if (stat(input + k, &st) == 0)
{
return (k);
}
get_error(mydata, 127);
return (-1);
}

/**
* check_error_cmd - function that verifies
* if user has permissions to access
* @dd: destination directory
* @mydata: data structure
* Return: 1 if there is an error, 0 if not
*/
int check_error_cmd(char *dd, data_shell *mydata)
{
if (dd == NULL)
{
get_error(mydata, 127);
return (1);
}

if (_strcmp(mydata->args[0], dd) != 0)
{
if (access(dd, X_OK) == -1)
{
get_error(mydata, 126);
free(dd);
return (1);
}
free(dd);
}
else
{
if (access(mydata->args[0], X_OK) == -1)
{
get_error(mydata, 126);
return (1);
}
}

return (0);
}

/**
* cmd_exec -Function for executes command lines
* @mydata: data relevant (args and input)
* Return: 1 on success.
*/
int cmd_exec(data_shell *mydata)
{
pid_t pd;
pid_t wpd;
int state;
int exec;
char *dir;
(void) wpd;

exec = is_executable(mydata);
if (exec == -1)
return (1);
if (exec == 0)
{
dir = _which(mydata->args[0], mydata->_environ);
if (check_error_cmd(dir, mydata) == 1)
return (1);
}

pd = fork();
if (pd == 0)
{
if (exec == 0)
dir = _which(mydata->args[0], mydata->_environ);
else
dir = mydata->args[0];
execve(dir + exec, mydata->args, mydata->_environ);
}
else if (pd < 0)
{
perror(mydata->av[0]);
return (1);
}
else
{
do {
wpd = waitpid(pd, &state, WUNTRACED);
} while (!WIFEXITED(state) && !WIFSIGNALED(state));
}

mydata->status = state / 256;
return (1);
}
