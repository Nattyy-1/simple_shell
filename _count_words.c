#include "main.h"

/**
 * _count_words - counts the number of words in a given string
 * @str: the string we are counting the words of
 *
 * Return: the number of words the string holds
 */
int _count_words(char *str)
{
	int i = 0, in_word = 0, count = 0;

	if (str == NULL)
		return (count);

	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			in_word = 0;
		} else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		i++;
	}

	return (count);
}
