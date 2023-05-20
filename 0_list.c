#include "shell.h"

/**
* add_sep_node_end -That function adds
* a separator found at the endof a sep_list.
* @h: head of the linked list.
* @s: separator found (; | &).
* Return: address of the head.
*/
sep_list *add_sep_node_end(sep_list **h, char s)
{
sep_list *new, *temp;

new = malloc(sizeof(sep_list));
if (new == NULL)
return (NULL);

new->separator = s;
new->next = NULL;
temp = *h;

if (temp == NULL)
{
*h = new;
}
else
{
while (temp->next != NULL)
temp = temp->next;
temp->next = new;
}

return (*h);
}

/**
* free_sep_list - That function frees a sep_list
* @h: head of the linked list.
* Return: no return.
*/
void free_sep_list(sep_list **h)
{
sep_list *temp;
sep_list *curr;

if (h != NULL)
{
curr = *h;
while ((temp = curr) != NULL)
{
curr = curr->next;
free(temp);
}
*h = NULL;
}
}

/**
* add_line_node_end -That function adds 
* a command line at the endof a line_list.
* @h: head of the linked list.
* @l: command line.
* Return: address of the head.
*/
line_list *add_line_node_end(line_list **h, char *l)
{
line_list *new, *temp;

new = malloc(sizeof(line_list));
if (new == NULL)
return (NULL);

new->line = l;
new->next = NULL;
temp = *h;

if (temp == NULL)
{
*h = new;
}
else
{
while (temp->next != NULL)
temp = temp->next;
temp->next = new;
}

return (*h);
}

/**
* free_line_list - That function frees a line_list
* @h: head of the linked list.
* Return: no return.
*/
void free_line_list(line_list **h)
{
line_list *temp;
line_list *curr;

if (h != NULL)
{
curr = *h;
while ((temp = curr) != NULL)
{
curr = curr->next;
free(temp);
}
*h = NULL;
}
}
