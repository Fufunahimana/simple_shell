#include "shell.h"

/**
* check_env - That function checks if
* the typed variable is an env variable
* @head: head of linked list
* @str: input string
* @mydata: data structure
* Return: no return
*/
void check_env(r_var **head, char *str, data_shell *mydata)
{
int row, chr, j, lval;
char **_envr;

_envr = mydata->_environ;
for (row = 0; _envr[row]; row++)
{
for (j = 1, chr = 0; _envr[row][chr]; chr++)
{
if (_envr[row][chr] == '=')
{
lval = _strlen(_envr[row] + chr + 1);
add_rvar_node(head, j, _envr[row] + chr + 1, lval);
return;
}

if (str[j] == _envr[row][chr])
j++;
else
break;
}
}

for (j = 0; str[j]; j++)
{
if (str[j] == ' ' || str[j] == '\t' || str[j] == ';' || str[j] == '\n')
break;
}

add_rvar_node(head, j, NULL, 0);
}

/**
* check_vars -function that checks if the typed variable is $$ or $?
* @head: head of the linked list
* @str: input string
* @st: last status of the Shell
* @mydata: data structure
* Return: no return
*/
int check_vars(r_var **head, char *str, char *st, data_shell *mydata)
{
int i, lst, lpd;

lst = _strlen(st);
lpd = _strlen(mydata->pid);

for (i = 0; str[i]; i++)
{
if (str[i] == '$')
{
if (str[i + 1] == '?')
add_rvar_node(head, 2, st, lst), i++;
else if (str[i + 1] == '$')
add_rvar_node(head, 2, mydata->pid, lpd), i++;
else if (str[i + 1] == '\n')
add_rvar_node(head, 0, NULL, 0);
else if (str[i + 1] == '\0')
add_rvar_node(head, 0, NULL, 0);
else if (str[i + 1] == ' ')
add_rvar_node(head, 0, NULL, 0);
else if (str[i + 1] == '\t')
add_rvar_node(head, 0, NULL, 0);
else if (str[i + 1] == ';')
add_rvar_node(head, 0, NULL, 0);
else
check_env(head, str + i, mydata);
}
}

return (i);
}

/**
* replaced_input - Function for replace string into variables
*
* @head: head of the linked list
* @str: input string
* @ni: new input string (replaced)
* @nl: new length
* Return: replaced string
*/
char *replaced_input(r_var **head, char *str, char *ni, int nl)
{
r_var *indx;
int i, j, k;

indx = *head;
for (j = i = 0; i < nl; i++)
{
if (str[j] == '$')
{
if (!(indx->len_var) && !(indx->len_val))
{
ni[i] = str[j];
j++;
}
else if (indx->len_var && !(indx->len_val))
{
for (k = 0; k < indx->len_var; k++)
j++;
i--;
}
else
{
for (k = 0; k < indx->len_val; k++)
{
ni[i] = indx->val[k];
i++;
}
j += (indx->len_var);
i--;
}
indx = indx->next;
}
else
{
ni[i] = str[j];
j++;
}
}

return (ni);
}

/**
* rep_var -that functio is for call a functions
* that replace string into vars.
* @str: input string
* @mydata: data structure
* Return: replaced string
*/
char *rep_var(char *str, data_shell *mydata)
{
r_var *head, *indx;
char *status, *ni;
int olen, nl;

status = aux_itoa(mydata->status);
head = NULL;

olen = check_vars(&head, str, status, mydata);

if (head == NULL)
{
free(status);
return (str);
}

indx = head;
nl = 0;

while (indx != NULL)
{
nl += (indx->len_val - indx->len_var);
indx = indx->next;
}

nl += olen;

ni = malloc(sizeof(char) * (nl + 1));
ni[nl] = '\0';

ni = replaced_input(&head, str, ni, nl);

free(str);
free(status);
free_rvar_list(&head);

return (ni);
}

