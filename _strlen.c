#include "main.h"

/**
 * _strlen - counts the number of characters in a given string
 * @str: the string to be checked
 *
 * Return: the number of characters present in the string
 */
int _strlen(char *str)
{
	int count = 0;

	if (str == NULL)
		return (count);

	while (str[count])
		count++;

	return (count);
}
