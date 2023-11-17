#include "_Shell.h"

/**
 * get_env_rn - gets the environment variable array
 *
 * Return: pointer to the environment variable array
 */

static char **_env_rn;

char **get_env_rn(void)
{
	return (_env_rn);
}
