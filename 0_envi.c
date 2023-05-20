#include "shell.h"

/**
* cmp_env_name - Function that compares
* env variables names with the name passed.
* @e: name of the environment variable
* @n: name passed
*
* Return: 0 if are not equal. Another value if they are.
*/
int cmp_env_name(const char *e, const char *n)
{
int k;

for (k = 0; e[k] != '='; k++)
{
if (e[k] != n[k])
{
return (0);
}
}

return (k + 1);
}

/**
* _getenv - get an environment variable
* @n: name of the environment variable
* @_environ: environment variable
*
* Return: value of the environment variable if is found.
* In other case, returns NULL.
*/
char *_getenv(const char *n, char **_environ)
{
char *ptr_env;
int k, mov;

/* Initialize ptr_env value */
ptr_env = NULL;
mov = 0;
/* Compare all environment variables */
/* environ is declared in the header file */
for (k = 0; _environ[k]; k++)
{
/* If name and env are equal */
mov = cmp_env_name(_environ[k], n);
if (mov)
{
ptr_env = _environ[k];
break;
}
}

return (ptr_env + mov);
}

/**
* _env - prints the evironment variables
*
* @mydata: data relevant.
* Return: 1 on success.
*/
int _env(data_shell *mydata)
{
int k, l;

for (k = 0; mydata->_environ[k]; k++)
{

for (l = 0; mydata->_environ[k][l]; l++)
;

write(STDOUT_FILENO, mydata->_environ[k], l);
write(STDOUT_FILENO, "\n", 1);
}
mydata->status = 0;

return (1);
}
