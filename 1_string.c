#include "shell.h"

/**
* _strdup - that function duplicates a 
* string in the heap memory.
* @str: Type char pointer str
* Return: duplicated str
*/
char *_strdup(const char *str)
{
char *new;
size_t len;

len = _strlen(str);
new = malloc(sizeof(char) * (len + 1));
if (new == NULL)
return (NULL);
_memcpy(new, str, len + 1);
return (new);
}

/**
* _strlen - That function Returns
* the lenght of a string.
* @str: Type char pointer
* Return: Always 0.
*/
int _strlen(const char *str)
{
int len;

for (len = 0; str[len] != 0; len++)
{
}
return (len);
}

/**
* cmp_chars -that function is for
* compare chars of strings
* @str: input string.
* @delim: delimiter.
*
* Return: 1 if are equals, 0 if not.
*/
int cmp_chars(char str[], const char *delim)
{
unsigned int k,l,m;

for (k = 0, m = 0; str[k]; k++)
{
for (l = 0; delim[l]; l++)
{
if (str[k] == delim[l])
{
m++;
break;
}
}
}
if (k == m)
return (1);
return (0);
}

/**
* _strtok - function that splits a string by some delimiter.
* @str: input string.
* @delim: delimiter.
*
* Return: string splited.
*/
char *_strtok(char str[], const char *delim)
{
static char *splitted, *str_end;
char *str_start;
unsigned int k, bool;

if (str != NULL)
{
if (cmp_chars(str, delim))
return (NULL);
splitted = str; /*Store first address*/
k = _strlen(str);
str_end = &str[k]; /*Store last address*/
}
str_start = splitted;
if (str_start == str_end) /*Reaching the end*/
return (NULL);

for (bool = 0; *splitted; splitted++)
{
/*Breaking loop finding the next token*/
if (splitted != str_start)
if (*splitted && *(splitted - 1) == '\0')
break;
/*Replacing delimiter for null char*/
for (k = 0; delim[k]; k++)
{
if (*splitted == delim[k])
{
*splitted = '\0';
if (splitted == str_start)
str_start++;
break;
}
}
if (bool == 0 && *splitted) /*Str != Delim*/
bool = 1;
}
if (bool == 0) /*Str == Delim*/
return (NULL);
return (str_start);
}

/**
* _isdigit - That frunction defines if
* string passed is a number.
* @str: input string
* Return: 1 if string is a number. 0 in other case.
*/
int _isdigit(const char *str)
{
unsigned int k;

for (k = 0; str[k]; k++)
{
if (str[k] < 48 || str[k] > 57)
return (0);
}
return (1);
}
