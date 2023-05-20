#include "shell.h"

/**
* swap_char - that function swaps | and & for non-printed chars
*@str: input string
* @bool: type of swap
* Return: swapped string
*/
char *swap_char(char *str, int bool)
{
int k;

if (bool == 0)
{
for (k = 0; str[k]; k++)
{
if (str[k] == '|')
{
if (str[k + 1] != '|')
str[k] = 16;
else
k++;
}

if (str[k] == '&')
{
if (str[k + 1] != '&')
str[k] = 12;
else
k++;
}
}
}
else
{
for (k = 0; str[k]; k++)
{
str[k] = (str[k] == 16 ? '|' : str[k]);
str[k] = (str[k] == 12 ? '&' : str[k]);
}
}
return (str);
}

/**
* add_nodes -That function is for  add
* separators and command lines in the lists
* @hs: head of separator list
* @hl: head of command lines list
* @str: input string
* Return: no return
*/
void add_nodes(sep_list **hs, line_list **hl, char *str)
{
int k;
char *line;

str = swap_char(str, 0);

for (k = 0; str[k]; k++)
{
if (str[k] == ';')
add_sep_node_end(hs, str[k]);

if (str[k] == '|' || str[k] == '&')
{
add_sep_node_end(hs, str[k]);
k++;
}
}

line = _strtok(str, ";|&");
do {
line = swap_char(line, 1);
add_line_node_end(hl, line);
line = _strtok(NULL, ";|&");
} while (line != NULL);

}

/**
* go_next - that function is for go
* to the next command line stored
* @ls: separator list
* @ll: command line list
* @mydata: data structure
* Return: no return
*/
void go_next(sep_list **ls, line_list **ll, data_shell *mydata)
{
int loop_sep;
sep_list *ls_s;
line_list *ls_l;

loop_sep = 1;
ls_s = *ls;
ls_l = *ll;

while (ls_s != NULL && loop_sep)
{
if (mydata->status == 0)
{
if (ls_s->separator == '&' || ls_s->separator == ';')
loop_sep = 0;
if (ls_s->separator == '|')
ls_l = ls_l->next, ls_s = ls_s->next;
}
else
{
if (ls_s->separator == '|' || ls_s->separator == ';')
loop_sep = 0;
if (ls_s->separator == '&')
ls_l = ls_l->next, ls_s = ls_s->next;
}
if (ls_s != NULL && !loop_sep)
ls_s = ls_s->next;
}

*ls = ls_s;
*ll = ls_l;
}

/**
* split_commands - That function is for split
* command lines according to
* the separators ;, | and &, and executes them
* @mydata: data structure
* @str: input string
* Return: 0 to exit, 1 to continue
*/
int split_commands(data_shell *mydata, char *str)
{

sep_list *hs, *ls;
line_list *hl, *ll;
int loop;

hs = NULL;
hl = NULL;

add_nodes(&hs, &hl, str);

ls = hs;
ll = hl;

while (ll != NULL)
{
mydata->input = ll->line;
mydata->args = split_line(mydata->input);
loop = exec_line(mydata);
free(mydata->args);

if (loop == 0)
break;

go_next(&ls, &ll, mydata);

if (ll != NULL)
ll = ll->next;
}

free_sep_list(&hs);
free_line_list(&hl);

if (loop == 0)
return (0);
return (1);
}

/**
* split_line - That function tokenizes the input string
* @str: input string.
* Return: string splitted.
*/
char **split_line(char *str)
{
size_t bsize;
size_t i;
char **tokens;
char *token;

bsize = TOK_BUFSIZE;
tokens = malloc(sizeof(char *) * (bsize));
if (tokens == NULL)
{
write(STDERR_FILENO, ": allocation error\n", 18);
exit(EXIT_FAILURE);
}

token = _strtok(str, TOK_DELIM);
tokens[0] = token;

for (i = 1; token != NULL; i++)
{
if (i == bsize)
{
bsize += TOK_BUFSIZE;
tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
if (tokens == NULL)
{
write(STDERR_FILENO, ": allocation error\n", 18);
exit(EXIT_FAILURE);
}
}
token = _strtok(NULL, TOK_DELIM);
tokens[i] = token;
}

return (tokens);
}
