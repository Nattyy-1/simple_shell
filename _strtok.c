#include "main.h"

/**
 * is_delim - checks whether a character is one of the delimiters
 * @c: the character to test
 * @delim: the set of delimiter characters
 *
 * Return: 1 if @c is a delimiter, otherwise 0
 */
int is_delim(char c, const char *delim)
{
	int i;

	for (i = 0; delim[i] != '\0'; i++)
	{
		if (c == delim[i])
			return (1);
	}
	return (0);
}

/**
 * _strtok - returns a token from a string based on a delimiter
 * @str: the string to tokenize, or NULL to continue the previous string
 * @delim: the characters used as delimiters
 *
 * The returned token points INTO @str (the delimiter is overwritten with
 * '\0'); it is not a new allocation and must never be free()d. Uses static
 * state, so it is not reentrant: do not interleave two tokenizations.
 *
 * Return: the token extracted or NULL if there are no more tokens
 */
char *_strtok(char *str, const char *delim)
{
	static char *current;
	char *start;

	if (str != NULL)
		current = str;
	if (current == NULL)
		return (NULL);

	while (*current && is_delim(*current, delim))
		current++;

	if (*current == '\0')
		return (NULL);

	start = current;
	while (*current)
	{
		if (is_delim(*current, delim))
		{
			*current = '\0';
			current++;
			break;
		}
		current++;
	}
	return (start);
}
