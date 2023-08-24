#include "shell.h"

/**
 * shell_loop - main shell loop
 * @info: the info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_loop(info_t *info, char **av)
{
	ssize_t r = 0;
	int br = 0, bt_ret = 0;

	while (r != -1 && bt_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			bt_ret = find_builtin(info);
			if (bt_ret == -1)
				find_command(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (bt_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (bt_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the info struct
 *
 * Return: (-1) if builtin not found,
 * (0) if builtin executed successfully,
 * (1) if builtin found but not successful,
 * (2) if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int i, bt_ret = -1;
	builtin_table bt[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; bt[i].type; i++)
		if (_strcmp(info->argv[0], bt[i].type) == 0)
		{
			info->line_count++;
			bt_ret = bt[i].func(info);
			break;
		}
	return (bt_ret);
}

/**
 * find_command - finds a command in PATH
 * @info: the info struct
 *
 * Return: void (nothing)
 */
void find_command(info_t *info)
{
	char *p = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->lc_flag == 1)
	{
		info->line_count++;
		info->lc_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	p = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (p)
	{
		info->path = p;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a process to run a command
 * @info: the info struct
 *
 * Return: void (nothing)
 */
void fork_cmd(info_t *info)
{
	pid_t c_pid;

	c_pid = fork();
	if (c_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (c_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
