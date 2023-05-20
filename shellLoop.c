#include "shell.h"

/**
* without_comment - function that deletes comments from the input
* @str: input string
* Return: input without comments
*/
char *without_comment(char *str)
{
int i, up_to;

up_to = 0;
for (i = 0; str[i]; i++)
{
if (str[i] == '#')
{
if (i == 0)
{
free(str);
return (NULL);
}

if (str[i - 1] == ' ' || str[i - 1] == '\t' || str[i - 1] == ';')
up_to = i;
}
}

if (up_to != 0)
{
str = _realloc(str, i, up_to + 1);
str[up_to] = '\0';
}

return (str);
}

/**
* shell_loop - Function that does a loop of shell
* @mydata: data relevant (av, input, args)
* Return: no return.
*/
void shell_loop(data_shell *mydata)
{
int loop, value;
char *input;

loop = 1;
while (loop == 1)
{
write(STDIN_FILENO, "^-^ ", 4);
input = read_line(&value);
if (value != -1)
{
input = without_comment(input);
if (input == NULL)
continue;

if (check_syntax_error(mydata, input) == 1)
{
mydata->status = 2;
free(input);
continue;
}
input = rep_var(input, mydata);
loop = split_commands(mydata, input);
mydata->counter += 1;
free(input);
}
else
{
loop = 0;
free(input);
}
}
}
