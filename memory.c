#include "shell.h"

/**
* _memcpy - that function is for copies 
* information between void pointers.
* @dp: destination pointer.
* @sp: source pointer.
* @size: size of the new pointer.
*
* Return: no return.
*/
void _memcpy(void *dp, const void *sp, unsigned int size)
{
char *char_ptr = (char *)sp;
char *char_newptr = (char *)dp;
unsigned int k;

for (k = 0; k < size; k++)
char_newptr[k] = char_ptr[k];
}

/**
* _realloc - That function reallocates a memory block.
* @p: pointer to the memory previously allocated.
* @o_s: size, in bytes, of the allocated space of ptr.
* @n_s: new size, in bytes, of the new memory block.
*Return: p.
* if n_s == o_s, returns ptr without changes.
* if malloc fails, returns NULL.
*/
void *_realloc(void *p, unsigned int o_s, unsigned int n_s)
{
void *newptr;

if (p == NULL)
return (malloc(n_s));

if (n_s == 0)
{
free(p);
return (NULL);
}

if (n_s == o_s)
return (p);

newptr = malloc(n_s);
if (newptr == NULL)
return (NULL);

if (n_s < o_s)
_memcpy(newptr, p, n_s);
else
_memcpy(newptr, p, o_s);

free(p);
return (newptr);
}

/**
* _reallocdp - That function reallocates
* a memory block of a double pointer.
* @p: double pointer to the memory previously allocated.
* @o_s: size, in bytes, of the allocated space of ptr.
* @n_s: new size, in bytes, of the new memory block.
* Return: p.
* if n_s == 0_s, returns ptr without changes.
* if malloc fails, returns NULL.
*/
char **_reallocdp(char **p, unsigned int o_s, unsigned int n_s)
{
char **newptr;
unsigned int k;

if (p == NULL)
return (malloc(sizeof(char *) * n_s));

if (n_s == o_s)
return (p);

newptr = malloc(sizeof(char *) * n_s);
if (newptr == NULL)
return (NULL);

for (k = 0; k < o_s; k++)
newptr[k] = p[k];

free(p);

return (newptr);
}
