#include "main.h"

/**
 * _strcmp - compares and checks if two strings are the same
 * @str1: the first string
 * @str2: the second string
 *
 * Return: 0 if the two strings are the same, otherwise 1
 */
int _strcmp(char *str1, char *str2)
{
	int i;

	int str1_len = _strlen(str1);
	int str2_len = _strlen(str2);

	if (str1 == NULL || str2 == NULL)
		return (1);

	if (str1_len != str2_len)
		return (1);

	for (i = 0; str1[i] != '\0'; i++)
	{
		if (str1[i] != str2[i])
			return (1);
	}

	return (0);
}
