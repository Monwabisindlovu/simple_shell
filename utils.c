#include "shell.h"

/**
 * exiting - Exits the shell
 * @info: Pointer to the info structure
 *
 * Return: Exits with a given exit status=
 *(0) if info->argv[0] != "exit"
 */
int exiting(info_t *info)
{
	int exit_code;

	if (info->argv[1])
	{
		exit_code = string_to_int(info->argv[1]);
		if (exit_code == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}

		info->err_num = exit_code;
		return (-2);
	}

	info->err_num = -1;
	return (-2);
}

/**
 * change_directory - changes the current working directory of the process
 * @info: Parameter struct containing potential arguments.
 *
 * Return: Always (0)
 */
int change_directory(info_t *info)
{
	char *current_path, *new_path, buffer[1024];
	int chdir_result;

	current_path = getcwd(buffer, 1024);
	if (!current_path)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->arguments[1])
	{
		new_path = _getenv(info, "HOME=");
		if (!new_path)
			chdir_result = chdir((new_path = _getenv(info, "PWD=")) ? new_path : "/");
		else
			chdir_result = chdir(new_path);
	}
	else if (_strcmp(info->arguments[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_path);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		chdir_result = chdir((new_path = _getenv(info, "OLDPWD=")) ? new_path : "/");
	}
	else
		chdir_result = chdir(info->arguments[1]);
	if (chdir_result == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->arguments[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * display_help - displays information about shell commands
 * @info: Parameter struct containing potential arguments.
 *
 * Return: Always (0)
 */
int display_help(info_t *info)
{
	char **arg_array;

	arg_array = info->arguments;
	_puts("Help command works. Functionality not yet implemented \n");
	if (0)
		_puts(*arg_array);  /*this is a temporary unused attribute workaround */
	return (0);
}
