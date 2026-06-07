#include "main.h"

/**
 * own_environ - ensures environ is a heap copy this shell fully owns
 *
 * The initial environ array and its strings are owned by the C runtime,
 * so freeing them is undefined. On first call this deep-copies environ
 * (array plus every string) and points environ at the copy. Later calls
 * are no-ops. Once owned, setenv/unsetenv may freely free entries.
 *
 * Return: 0 on success, -1 on allocation failure
 */
int own_environ(void)
{
	static int owned;
	int count = 0, i;
	char **copy;

	if (owned)
		return (0);

	while (environ[count] != NULL)
		count++;

	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (-1);

	for (i = 0; i < count; i++)
	{
		copy[i] = strdup(environ[i]);
		if (!copy[i])
		{
			while (i-- > 0)
				free(copy[i]);
			free(copy);
			return (-1);
		}
	}
	copy[count] = NULL;
	environ = copy;
	owned = 1;
	return (0);
}
