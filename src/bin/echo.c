/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:05:13 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/25 21:56:26 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_inside_double_quotes(char* str) {
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
}

char	*remove_quotes(char *str)
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
}

int	valid_quotes(char *str)
{
	int nb_single_quotes;
	int nb_double_quotes;
	int i;

	nb_single_quotes = 0;
	nb_double_quotes = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			nb_double_quotes++;
		if (str[i] == '\'')
			nb_single_quotes++;
		i++;
	}
	if ((nb_single_quotes % 2) == 0 ||	(nb_double_quotes % 2) == 0)
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
		content = remove_quotes((char *)parser->args->content);
		if (valid_quotes(content))
		{
			printf("never");
			error(shell, "bad syntax", NULL);
			return ;
		}
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

