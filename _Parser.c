#include "_Shell.h"

/**
 * curr_cmd - this determines if a file is an executable command
 *
 * @info: the info struct
 * @p: the path to the file
 *
 * Return: 1 if true, 0 if false
 */
int curr_cmd(_info_pass_t *info, char *p)
{
	struct stat fs;

	(void)info;
	if (!p || stat(p, &fs) != 0)
		return (0);

	if (S_ISREG(fs.st_mode) && (fs.st_mode & S_IXUSR))
	{
		return (1);
	}
	return (0);
}

/**
 * char_duplicate - duplicated chracters from a string within a range
 *
 * @path_str: the path string
 * @start_idx: starting index
 * @stop_idx: stopping index
 *
 * Return: pointer to new buffer
 */
char *char_duplicate(char *path_str, int start_idx, int stop_idx)
{
	static char buffer[1024];
	int i, j = 0;

	for (i = start_idx; i < stop_idx; i++)
		if (path_str[i] != ':')
			buffer[j++] = path_str[i];
	buffer[j] = '\0';
	return (buffer);
}

/**
 * _path_find - finds the specified command in the given path string
 *
 * @info: the info struct
 * @path_str: the path string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found, or NULL if not found
 */
char *_path_find(_info_pass_t *info, char *path_str, char *cmd)
{
	int i = 0, current = 0;
	char *p;

	if (!path_str)
		return (NULL);
	if ((str_len(cmd) > 2) && _start(cmd, "./"))
	{
		if (curr_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			p = char_duplicate(path_str, current, i);
			if (!*p)
				str_cat(p, cmd);
			else
			{
				str_cat(p, "/");
				str_cat(p, cmd);
			}
			if (curr_cmd(info, p))
				return (p);
			if (!path_str[i])
				break;
			current = i;
		}
		i++;
	}
	return (NULL);
}
