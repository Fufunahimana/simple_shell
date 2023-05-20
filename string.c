#include "shell.h"

/**
* _strcat - Function that concatenatse two strings
* @des_str: char pointer the desination of the copied string
* @s: const char pointer the source of string
* Return: the dest
*/
char *_strcat(char *des_str, const char *s)
{
int k;
int l;

for (k = 0; des_str[k] != '\0'; k++)
;

for (l = 0; s[l] != '\0'; l++)
{
des_str[k] = s[l];
k++;
}

des_str[k] = '\0';
return (des_str);
}
/**
* *_strcpy - Function that Copies the string pointed to by src.
* @des_str: Type char pointer the dest of the copied str
* @s: Type char pointer the source of str
* Return: the dest.
*/
char *_strcpy(char *des_str, char *s)
{

size_t p;

for (p = 0; s[p] != '\0'; p++)
{
des_str[p] = s[p];
}
des_str[p] = '\0';

return (des_str);
}
/**
* _strcmp - Function that is for  compare two strings.
* @str1: type string compared
* @str2: type string compared
* Return: Always 0.
*/
int _strcmp(char *str1, char *str2)
{
int k;

for (k = 0; str1[k] == str2[k] && str1[k]; k++)
;

if (str1[k] > str2[k])
return (1);
if (str1[k] < str2[k])
return (-1);
return (0);
}
/**
* _strchr -Function that is for locate a character in a string,
* @str: string.
* @charac: character.
* Return: the pointer to the first occurrence of the character c.
*/
char *_strchr(char *str, char charac)
{
unsigned int k = 0;

for (; *(str + k) != '\0'; k++)
if (*(str + k) == charac)
return (str + k);
if (*(str + k) == charac)
return (str + k);
return ('\0');
}
/**
* _strspn - Function that is for get the length of a prefix substring.
* @seg: initial segment.
* @acb: accepted bytes.
* Return: the number of accepted bytes.
*/
int _strspn(char *seg, char *acb)
{
int k, l, bool;

for (k = 0; *(seg + k) != '\0'; k++)
{
bool = 1;
for (l = 0; *(acb + l) != '\0'; l++)
{
if (*(seg + k) == *(acb + l))
{
bool = 0;
break;
}
}
if (bool == 1)
break;
}
return (k);
}
