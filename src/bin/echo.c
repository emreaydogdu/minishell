/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:05:13 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/28 10:34:26 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* void	remove_inside_double_quotes(char* str) {
    int i = 0;
    int j = 0;
    
    while (str[i] != '\0')
	{
        if (str[i] == '"' && str[i + 1] == '"')
            i+=2;
        str[j] = str[i];
        i++;
        j++;
    }
    str[j] = '\0';
} */

/* char	*remove_quotes(char *str)
{
	int len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"') || 
		(str[0] == '\'' && str[len - 1] == '\'')))
	{
		str[len - 1] = '\0';
		return (str + 1);
	}
	remove_inside_double_quotes(str);
	return (str);
} */

char *remove_quotes(char *str) {
    int len = strlen(str);
    int i, j;

    // Remove matching quotes from the start and end
    int start = 0;
    int end = len - 1;
    // Count leading quotes
    while (start < len && (str[start] == '"' || str[start] == '\'')) {
        start++;
    }
    // Count trailing quotes
    while (end >= 0 && (str[end] == '"' || str[end] == '\'')) {
        end--;
    }
    // Calculate the number of complete pairs of quotes
    int pairs;
    if (start < len - end - 1) {
        pairs = start;
    } else {
        pairs = len - end - 1;
    }
    // Adjust start and end based on complete pairs of quotes
    if (pairs > 0) {
        start = pairs;
        end = len - pairs - 1;
    } else {
        start = 0;
        end = len - 1;
    }
    // Remove matching quotes inside the string
    i = start;
    j = start;
    
    while (i <= end) {
        if ((str[i] == '"' || str[i] == '\'') && i + 1 <= end && str[i] == str[i + 1]) {
            // Skip over matched pair of quotes
            i += 2;
        } else {
            // Copy non-quote character or unmatched quote
            str[j++] = str[i++];
        }
    }
    // Null-terminate the resulting string
    str[j] = '\0';
    return str + start;
}

int	valid_quotes(char *str)
{
	int nb_single_quotes;
	int nb_double_quotes;

	nb_single_quotes = 0;
	nb_double_quotes = 0;
	while (*str)
	{
		if (*str == '"')
			nb_double_quotes++;
		else if (*str == '\'')
			nb_single_quotes++;
		str++;
	}
	if ((nb_single_quotes % 2) == 0 && (nb_double_quotes % 2) == 0)
		return (1);
	return (0);
}


void	exec_echo(t_shell *shell) // t_shell *shell, int out
{
	t_parser 	*parser;
	char		*content;
	parser = shell->parser;

	while (parser->args != NULL)
	{
		//printf("(char *)parser->args->content = [%s]\n", (char *)parser->args->content);
		content = remove_quotes((char *)parser->args->content);
		printf("content = [[%s]]\n", content);
		if (valid_quotes((content)))
		{
			if (parser->outfile != STDOUT_FILENO)
			{
				write(parser->outfile, content, ft_strlen(content));
				if (parser->args->next)
					write(parser->outfile, " ", 1);
			}
			else
			{
				printf("%s", content);
				if (parser->args->next)
					printf(" ");
			}
		}
		else
		{
			error(shell, "bad syntax", NULL);
			return ;
		}
		parser->args = parser->args->next;
	}
	if (parser->outfile != STDOUT_FILENO)
		close(parser->outfile);
	error(shell, NULL, NULL);
}

