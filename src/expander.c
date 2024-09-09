/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:16:34 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/09 15:52:33 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_shell *shell)
{
	t_lexer * lexer;
	int			i;
	int			j;
	char		*key;
	char		*start;
	char		*end;
	char		*dest;
	
	dest = NULL;
	lexer = shell->lexer;
	while (lexer)
	{
		i = 0;
		while (lexer->input[i])
		{
			if (lexer->input[i] == '$')
			{	
				start = ft_substr(lexer->input, 0,  i);
				j = i;
				while (lexer->input[j] != ' ' && lexer->input[j] != '"'  && lexer->input[j] != '\'' && lexer->input[j])
					j++;
				key = ft_substr(lexer->input, i + 1, j - i - 1);
				end = ft_substr(lexer->input,j, ft_strlen(lexer->input) - j + 1);
				
				// todo: check if arg is existing or not. reproduce bash behavior.
				key = getenv(key);
				dest = malloc(sizeof(char) * (ft_strlen(start) + ft_strlen(key) + ft_strlen(end) + 1));
				if (!dest)
					return ;
				dest[0] = '\0';
				dest = ft_strcat(dest, start);
				dest = ft_strcat(dest, key);
				dest = ft_strcat(dest, end);
				lexer->input = dest;
				i = j;
			}
			i++;
		}
		lexer = lexer->next;
	}
}
