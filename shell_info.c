#include "shell.h"

/**
 * init_info - initialize the info structure
 * @info: address of the info_t structure
 */
void init_info(info_t *info)
{
	info->command_line = NULL;
	info->command_args = NULL;
	info->executable_path = NULL;
	info->num_args = (0);
}

/**
 * fill_info - populate the info structure with data
 * @info: address of the info_t structure
 * @args: command arguments
 */
void fill_info(info_t *info, char **args)
{
	int i = 0;

	info->program_name = args[0];
	if (info->command_line)
	{
		info->command_args = tokenize(info->command_line, " \t");
		if (!info->command_args)
		{
			info->command_args = malloc(sizeof(char *) * 2);
			if (info->command_args)
			{
				info->command_args[0] = _strdup(info->command_line);
				info->command_args[1] = NULL;
			}
		}

		for (i = 0; info->command_args && info->command_args[i]; i++)
		;
		info->num_args = i;

		replace_aliases(info);
		replace_variables(info);
	}
}

/**
 * cleanup_info - free memory used by the info structure
 * @info: address of the info_t structure
 * @all: true if freeing all fields
 */
void cleanup_info(info_t *info, int all)
{
	free_tokens(info->command_args);
	info->command_args = NULL;
	info->executable_path = NULL;
	if (all)
	{
		if (!info->command_buffer)
			free(info->command_line);
		if (info->environment)
			free_list(&(info->environment));
		if (info->history_list)
			free_list(&(info->history_list));
		if (info->alias_list)
			free_list(&(info->alias_list));
		free_tokens(info->environ);
		info->environ = NULL;
		free(info->command_buffer);
		if (info->read_fd > 2)
			close(info->read_fd);
		_putchar(FLUSH_BUFFER);
	}
}
