#include "shell.h"

/**
* cd_dot -Function that  changes to
* the parent directory.
*@mydata: data relevant (environ)
*
* Return: no return
*/
void cd_dot(data_shell *mydata)
{
char pwd[PATH_MAX];
char *dir, *cp_pwd, *cp_strtok_pwd;

getcwd(pwd, sizeof(pwd));
cp_pwd = _strdup(pwd);
set_env("OLDPWD", cp_pwd, mydata);
dir = mydata->args[1];
if (_strcmp(".", dir) == 0)
{
set_env("PWD", cp_pwd, mydata);
free(cp_pwd);
return;
}
if (_strcmp("/", cp_pwd) == 0)
{
free(cp_pwd);
return;
}
cp_strtok_pwd = cp_pwd;
rev_string(cp_strtok_pwd);
cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
if (cp_strtok_pwd != NULL)
{
cp_strtok_pwd = _strtok(NULL, "\0");

if (cp_strtok_pwd != NULL)
rev_string(cp_strtok_pwd);
}
if (cp_strtok_pwd != NULL)
{
chdir(cp_strtok_pwd);
set_env("PWD", cp_strtok_pwd, mydata);
}
else
{
chdir("/");
set_env("PWD", "/", mydata);
}
mydata->status = 0;
free(cp_pwd);
}

/**
* cd_to - Function Thatchanges to a
* directory given by the user
* @mydata: data relevant (directories)
* Return: no return
*/
void cd_to(data_shell *mydata)
{
char pwd[PATH_MAX];
char *dir, *cp_pwd, *cp_dir;

getcwd(pwd, sizeof(pwd));

dir = mydata->args[1];
if (chdir(dir) == -1)
{
get_error(mydata, 2);
return;
}

cp_pwd = _strdup(pwd);
set_env("OLDPWD", cp_pwd, mydata);

cp_dir = _strdup(dir);
set_env("PWD", cp_dir, mydata);

free(cp_pwd);
free(cp_dir);

mydata->status = 0;

chdir(dir);
}

/**
* cd_previous -That function changes to the previous directory
* @mydata: data relevant (environ)
* Return: no return
*/
void cd_previous(data_shell *mydata)
{
char pwd[PATH_MAX];
char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

getcwd(pwd, sizeof(pwd));
cp_pwd = _strdup(pwd);

p_oldpwd = _getenv("OLDPWD", mydata->_environ);

if (p_oldpwd == NULL)
cp_oldpwd = cp_pwd;
else
cp_oldpwd = _strdup(p_oldpwd);

set_env("OLDPWD", cp_pwd, mydata);

if (chdir(cp_oldpwd) == -1)
set_env("PWD", cp_pwd, mydata);
else
set_env("PWD", cp_oldpwd, mydata);

p_pwd = _getenv("PWD", mydata->_environ);

write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
write(STDOUT_FILENO, "\n", 1);

free(cp_pwd);
if (p_oldpwd)
free(cp_oldpwd);

mydata->status = 0;

chdir(p_pwd);
}

/**
* cd_to_home - That function changes to home directory
*
* @mydata: data relevant (environ)
* Return: no return
*/
void cd_to_home(data_shell *mydata)
{
char *p_pwd, *home;
char pwd[PATH_MAX];

getcwd(pwd, sizeof(pwd));
p_pwd = _strdup(pwd);

home = _getenv("HOME", mydata->_environ);

if (home == NULL)
{
set_env("OLDPWD", p_pwd, mydata);
free(p_pwd);
return;
}

if (chdir(home) == -1)
{
get_error(mydata, 2);
free(p_pwd);
return;
}

set_env("OLDPWD", p_pwd, mydata);
set_env("PWD", home, mydata);
free(p_pwd);
mydata->status = 0;
}