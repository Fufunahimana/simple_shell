#include "shell.h"

/**
* get_len - Function fot Get the lenght of a number.
* @number: type int number.
* Return: Lenght of a number.
*/
int get_len(int number)
{
unsigned int n1;
int lenght = 1;

if (number < 0)
{
lenght++;
n1 = number * -1;
}
else
{
n1 = number;
}
while (n1 > 9)
{
lenght++;
n1 = n1 / 10;
}

return (lenght);
}
/**
* aux_itoa - function is for convert  int to string.
* @number: type int number
* Return: String.
*/
char *aux_itoa(int number)
{
unsigned int n1;
int lenght = get_len(number);
char *buffer;

buffer = malloc(sizeof(char) * (lenght + 1));
if (buffer == 0)
return (NULL);

*(buffer + lenght) = '\0';

if (number < 0)
{
n1 = number * -1;
buffer[0] = '-';
}
else
{
n1 = number;
}

lenght--;
do {
*(buffer + lenght) = (n1 % 10) + '0';
n1 = n1 / 10;
lenght--;
}
while (n1 > 0)
;
return (buffer);
}

/**
* _atoi - function that converts a string to an integer.
* @str: input string.
* Return: integer.
*/
int _atoi(char *str)
{
unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

while (*(str + count) != '\0')
{
if (size > 0 && (*(str + count) < '0' || *(str + count) > '9'))
break;

if (*(str + count) == '-')
pn *= -1;

if ((*(str + count) >= '0') && (*(str + count) <= '9'))
{
if (size > 0)
m *= 10;
size++;
}
count++;
}

for (i = count - size; i < count; i++)
{
oi = oi + ((*(str + i) - 48) * m);
m /= 10;
}
return (oi *pn);
}
