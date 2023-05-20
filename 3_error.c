#include "shell.h"

/**
* repeated_char - That function is counts
* the repetitions of a char
* @str: input string
* @i: index
* Return: repetitions
*/
int repeated_char(char *str, int i)
{
if (*(str - 1) == *str)
return (repeated_char(str - 1, i + 1));

return (i);
}

/**
* error_sep_op - That function finds syntax errors
* @str: input string
* @i: index
* @last: last char read
* Return: index of error. 0 when there are no
* errors
*/
int error_sep_op(char *str, int i, char last)
{
int count;

count = 0;
if (*str == '\0')
return (0);

if (*str == ' ' || *str == '\t')
return (error_sep_op(str + 1, i + 1, last));

if (*str == ';')
if (last == '|' || last == '&' || last == ';')
return (i);

if (*str == '|')
{
if (last == ';' || last == '&')
return (i);

if (last == '|')
{
count = repeated_char(str, 0);
if (count == 0 || count > 1)
return (i);
}
}

if (*str == '&')
{
if (last == ';' || last == '|')
return (i);

if (last == '&')
{
count = repeated_char(str, 0);
if (count == 0 || count > 1)
return (i);
}
}

return (error_sep_op(str + 1, i + 1, *str));
}

/**
* first_char - that function is for
* find index of the first char
* @str: input string
* @i: index
* Return: 1 if there is an error. 0 in other case.
*/
int first_char(char *str, int *i)
{

for (*i = 0; str[*i]; *i += 1)
{
if (str[*i] == ' ' || str[*i] == '\t')
continue;

if (str[*i] == ';' || str[*i] == '|' || str[*i] == '&')
return (-1);

break;
}

return (0);
}

/**
* print_syntax_error - That function is for print
* when a syntax error is found.
* @mydata: data structure
* @str: input string
* @index: index of the error
* @bool: to control msg error
* Return: no return
*/
void print_syntax_error(data_shell *mydata, char *str, int index, int bool)
{
char *msg, *msg2, *msg3, *error, *counter;
int length;

if (str[index] == ';')
{
if (bool == 0)
msg = (str[index + 1] == ';' ? ";;" : ";");
else
msg = (str[index - 1] == ';' ? ";;" : ";");
}

if (str[index] == '|')
msg = (str[index + 1] == '|' ? "||" : "|");

if (str[index] == '&')
msg = (str[index + 1] == '&' ? "&&" : "&");

msg2 = ": Syntax error: \"";
msg3 = "\" unexpected\n";
counter = aux_itoa(mydata->counter);
length = _strlen(mydata->av[0]) + _strlen(counter);
length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

error = malloc(sizeof(char) * (length + 1));
if (error == 0)
{
free(counter);
return;
}
_strcpy(error,mydata->av[0]);
_strcat(error, ": ");
_strcat(error, counter);
_strcat(error, msg2);
_strcat(error, msg);
_strcat(error, msg3);
_strcat(error, "\0");

write(STDERR_FILENO, error, length);
free(error);
free(counter);
}

/**
* check_syntax_error - this function is an intermediate for
* to find and print a syntax error.
*
* @mydata: data structure
* @str: input string
* Return: 1 if there is an error. 0 in other case
*/
int check_syntax_error(data_shell *mydata, char *str)
{
int begin = 0;
int f_char = 0;
int i = 0;

f_char = first_char(str, &begin);
if (f_char == -1)
{
print_syntax_error(mydata, str, begin, 0);
return (1);
}

i = error_sep_op(str + begin, 0, *(str + begin));
if (i != 0)
{
print_syntax_error(mydata, str, begin + i, 1);
return (1);
}

return (0);
}
