/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:16:34 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/23 13:49:38 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_single_quotes(char *input)
{
	int	first_quote;
	int	last_quote;
	int i = 0;
	
	while (input[i])
	{
		if(input[i] == '\'')
		{
			first_quote = i;
			break ;
		}
		i++;
	}
	while (input[i])
		i++;
	while (i >= 0)
	{
		if(input[i] == '\'')
		{
			last_quote = i;
			break ;
		}
		i--;
	}
	printf("%s\n", ft_substr(input, first_quote + 1, last_quote - first_quote - 1));
}

int	correct_single_quotes(char * input)
{
	int	nb_quotes;
	int	i;

	nb_quotes = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			nb_quotes++;
		i++;
	}
	if (nb_quotes >= 1 && (nb_quotes % 2) == 0)
	{
		write_single_quotes(input);
		return (1);
	}
	else if (nb_quotes >= 1 && (nb_quotes % 2) == 1)
	{
		printf("!!! Error missing quotes etc...\n");
		return (0);
	}
	return (0);
}

void	expander(t_shell *shell)
{
	t_lexer * lexer;
	int			i;
	int			j;
	int			single_quote;
	char		*key;
	char		*key_env;
	char		*start;
	char		*end;
	char		*dest;
	
	dest = NULL;
	lexer = shell->lexer;

	//correct_single_quotes(shell->cmdline); // Chakib : not supposed to write here, should be done in executer
	while (lexer)
	{
		i = 0;
		single_quote = 0;
		while (lexer->input[i])
		{
			if (lexer->input[i] == '\'')
				single_quote = !single_quote;
			if (lexer->input[i] == '$' && !single_quote)
			{
				start = ft_substr(lexer->input, 0,  i);
				j = i;
				while (lexer->input[j] != ' ' && lexer->input[j] != '"'  && lexer->input[j] != '\'' && lexer->input[j])
					j++;
				if (lexer->input[i + 1] == '?')
				{
					key_env = ft_itoa(shell->exit_status);
				}
				else
				{
					key = ft_substr(lexer->input, i + 1, j - i - 1);
					if (ft_strcmp(key, "") == 0)
					{
						i++;
						continue ;
					}
					key_env = getenv(key);
					if (key_env == NULL)
						key_env = "";
					free(key);
				}
				end = ft_substr(lexer->input,j, ft_strlen(lexer->input) - j + 1);
				dest = ft_calloc((ft_strlen(start) + ft_strlen(key_env) + ft_strlen(end) + 1), sizeof(char));
				if (!dest)
				 	return ;
				dest = ft_strcat(dest, start);
				dest = ft_strcat(dest, key_env);
				dest = ft_strcat(dest, end);
				lexer->input = ft_strdup(dest);
				free(start);
				free(key_env);
				free(end);
				free(dest);
				i = j;
			}
			i++;
		}
		//correct_single_quotes(lexer->input);
		//printf("1 == %s\n", lexer->input);
		lexer = lexer->next;
	}
}
