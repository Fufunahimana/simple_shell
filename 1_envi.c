#include "shell.h"

/**
* copy_info - That function is for  copy
* info to create a new env or alias
* @n: name (env or alias)
* @v: value (env or alias)
*
* Return: new env or alias.
*/
char *copy_info(char *n, char *v)
{
char *new;
int len_name, len_value, len;

len_name = _strlen(n);
len_value = _strlen(v);
len = len_name + len_value + 2;
new = malloc(sizeof(char) * (len));
_strcpy(new, n);
_strcat(new, "=");
_strcat(new, v);
_strcat(new, "\0");

return (new);
}

/**
* set_env - That function sets an environment variable.
* @n: name of the environment variable
* @v: value of the environment variable
* @mydata: data structure (environ)
* Return: no return
*/
void set_env(char *n, char *v, data_shell *mydata)
{
int k;
char *var_env, *name_env;

for (k = 0; mydata->_environ[k]; k++)
{
var_env = _strdup(mydata->_environ[k]);
name_env = _strtok(var_env, "=");
if (_strcmp(name_env, n) == 0)
{
free(mydata->_environ[k]);
mydata->_environ[k] = copy_info(name_env, v);
free(var_env);
return;
}
free(var_env);
}

mydata->_environ = _reallocdp(mydata->_environ, k, sizeof(char *) * (k + 2));
mydata->_environ[k] = copy_info(n, v);
mydata->_environ[k + 1] = NULL;
}

/**
* _setenv - That function  is for compare
* env variables names with the name passed.
* @mydata: data relevant (env name and env value)
*
* Return: 1 on success.
*/
int _setenv(data_shell *mydata)
{

if (mydata->args[1] == NULL || mydata->args[2] == NULL)
{
get_error(mydata, -1);
return (1);
}

set_env(mydata->args[1], mydata->args[2], mydata);

return (1);
}

/**
* _unsetenv - That function is for delete
* a environment variable
*
* @mydata: data relevant (env name)
*
* Return: 1 on success.
*/
int _unsetenv(data_shell *mydata)
{
char **realloc_environ;
char *var_env, *name_env;
int a, b, c;

if (mydata->args[1] == NULL)
{
get_error(mydata, -1);
return (1);
}
c = -1;
for (a = 0; mydata->_environ[a]; a++)
{
var_env = _strdup(mydata->_environ[a]);
name_env = _strtok(var_env, "=");
if (_strcmp(name_env, mydata->args[1]) == 0)
{
c = a;
}
free(var_env);
}
if (c == -1)
{
get_error(mydata, -1);
return (1);
}
realloc_environ = malloc(sizeof(char *) * (a));
for (a = b = 0; mydata->_environ[a]; a++)
{
if (a != c)
{
realloc_environ[b] = mydata->_environ[a];
b++;
}
}
realloc_environ[b] = NULL;
free(mydata->_environ[c]);
free(mydata->_environ);
mydata->_environ = realloc_environ;
return (1);
}
