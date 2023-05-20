#include "shell.h"

/**
* add_rvar_node - that function if for
* add a variable at the end of a r_var list.
* @head: head of the linked list.
* @lvar: length of the variable.
* @val: value of the variable.
* @lval: length of the value.
* Return: address of the head.
*/
r_var *add_rvar_node(r_var **h, int lvar, char *val, int lval)
{
r_var *new, *temp;

new = malloc(sizeof(r_var));
if (new == NULL)
return (NULL);

new->len_var = lvar;
new->val = val;
new->len_val = lval;

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
* free_rvar_list - function that frees a r_var list
* @h: head of the linked list.
* Return: no return.
*/
void free_rvar_list(r_var **h)
{
r_var *temp;
r_var *curr;

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
