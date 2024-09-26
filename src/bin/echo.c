/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:05:13 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/26 12:18:55 by chbachir         ###   ########.fr       */
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

char *remove_quotes(char *str)
{
    int len = ft_strlen(str);
    int start = 0;
    int end = len - 1;
    int opening_quotes = 0;
    int closing_quotes = 0;

    while (start < len && (str[start] == '"' || str[start] == '\''))
    {
        if (start + 1 < len && str[start] == str[start + 1])
            start += 2;
        else
            break;
        opening_quotes++;
    }

    while (end >= start && (str[end] == '"' || str[end] == '\''))
    {
        if (end - 1 >= start && str[end] == str[end - 1])
            end -= 2;
        else
            break;
        closing_quotes++;
    }

    if (opening_quotes == closing_quotes)
    {
        str[end + 1] = '\0';
        return (str + start);
    }

    return (str);
}

int	valid_quotes(char *str)
{
	int nb_single_quotes;
	int nb_double_quotes;

	nb_single_quotes = 0;
	nb_double_quotes = 0;
	printf("str valid quotes ? = [%s]\n", str);
	while (*str)
	{
		if (*str == '"')
			nb_double_quotes++;
		else if (*str == '\'')
			nb_single_quotes++;
		str++;
	}
	printf("single quotes = %d\n", nb_single_quotes);
	printf("double quotes %d\n", nb_double_quotes);
	if ((nb_single_quotes % 2) == 0 ||	(nb_double_quotes % 2) == 0)
		return (0);
	return (1);
}


void	exec_echo(t_shell *shell) // t_shell *shell, int out
{
	t_parser 	*parser;
	char		*content;
	parser = shell->parser;

	while (parser->args != NULL)
	{
		printf("(char *)parser->args->content = [%s]\n", (char *)parser->args->content);
		content = remove_quotes((char *)parser->args->content);
		/* if (valid_quotes((char *)parser->args->content))
		{
			content = remove_quotes((char *)parser->args->content);
			printf("content = [%s]\n", content);
		}
		else
		{
			error(shell, "bad syntax", NULL);
			return ;
		} */
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
		parser->args = parser->args->next;
	}
	if (parser->outfile != STDOUT_FILENO)
		close(parser->outfile);
	error(shell, NULL, NULL);
}

