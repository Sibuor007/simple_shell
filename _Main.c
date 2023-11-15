#include "_Shell.h"

/**
 * main - entry point for the shell
 *
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	_info_pass_t info[] = { INIT_INFO };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			:  "r" (fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				puts_(argv[0]);
				puts_(": 0: Can't open ");
				puts_(argv[1]);
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
	_h_shell(info, argv);

	return (EXIT_SUCCESS);
}
