/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:27:29 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/09 14:07:30 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	strcounter(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '"' && s[i] != '\0')
				i++;
		}

		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'' && s[i] != '\0')
				i++;
		}
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			count++;
		}
	}
	return (count);
}

static void	fillarr2(char **arr, size_t len_arr, char const *s, char c)
{
	size_t	i;
	size_t	len_word;
	size_t	in_quotes;

	in_quotes = 0;
	i = 0;
	while (i < len_arr)
	{
		len_word = 0;
		while (*s == c && *s != 0 && !in_quotes)
			s++;
		if (*s == '"' && in_quotes == 0)
		{
			in_quotes = 1;
			len_word++;
		}
		if (*s == '\'' && in_quotes == 0)
		{
			in_quotes = 2;
			len_word++;
		}
		while ((s[len_word] != c || in_quotes) && s[len_word] != '\0')
		{
			if (s[len_word] == '"' && in_quotes == 1)
				in_quotes = 0;
			if (s[len_word] == '\'' && in_quotes == 2)
				in_quotes = 0;
			len_word++;
		}
		arr[i] = ft_substr(s, 0, len_word);
		s += len_word;
		while (*s == c && !in_quotes && *s != 0)
			s++;
		i++;
	}
	arr[i] = 0;
}


char	**ft_split(char const *s, char c)
{
	size_t	len_arr;
	char	**arr;

	if (!s)
		return (0);
	len_arr = strcounter(s, c);
	arr = malloc(sizeof(char *) * (len_arr + 1));
	if (!arr)
		return (NULL);
	fillarr2(arr, len_arr, s, c);
	return (arr);
}
