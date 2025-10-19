#include "main.h"

/**
 * _is_number - checks if a string is a valid positive integer
 * @str: string to check
 *
 * Return: the converted number if valid, -1 if invalid
 */
int _is_number(char *str)
{
	int i = 0;
	int number = 0;

	if (str == NULL || *str == '\0')
		return (-1);

	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);

		number = number * 10 + (str[i] - '0');
		i++;
	}

	return (number);
}

