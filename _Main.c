#include "_Shell.h"

/**
 * main - entry point for the shell
 *
 * @_argc: argument count
 * @_argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int _argc, char **_argv)
{
	_info_pass_t info[] = {
		{NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, 0, 0, NULL, 0, 0, 0}
	};
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			:  "r" (fd));

	if (_argc == 2)
	{
		fd = open(_argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				puts_(_argv[0]);
				puts_(": 0: Can't open ");
				puts_(_argv[1]);
				putchar_('\n');
				putchar_(FLUSH_BUFFER);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->_input_read = fd;
	}
	env_populate(info);
	history_read(info);
	hsh(info, _argv);

	return (EXIT_SUCCESS);
}
