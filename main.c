#include "shell.h"

/**
 * free_data - Function that frees data structure
 * @mydata: data structure
 * Return: no return
 */
void free_data(data_shell *mydata)
{
	unsigned int k;

	for (k = 0; mydata->_environ[k]; k++)
	{
		free(mydata->_environ[k]);
	}

	free(mydata->_environ);
	free(mydata->pid);
}

/**
 * set_data - This function is for Initialize data structure
 *@mydata: data structure
 * @av: argument vector
 * Return: no return
 */
void set_data(data_shell *mydata, char **av)
{
	unsigned int k;

	mydata->av = av;
	mydata->input = NULL;
	mydata->args = NULL;
	mydata->status = 0;
	mydata->counter = 1;

	for (k = 0; environ[k]; k++)
		;

	mydata->_environ = malloc(sizeof(char *) * (k + 1));

	for (k = 0; environ[k]; k++)
	{
		mydata->_environ[k] = _strdup(environ[k]);
	}

	mydata->_environ[k] = NULL;
	mydata->pid = aux_itoa(getpid());
}

/**
 * main - Function that entry point
 *@ac: argument count
 * @av: argument vector
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell mydata;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&mydata, av);
	shell_loop(&mydata);
	free_data(&mydata);
	if (mydata.status < 0)
		return (255);
	return (mydata.status);
}
