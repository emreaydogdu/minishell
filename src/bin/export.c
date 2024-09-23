/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:32:10 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/23 14:18:02 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int is_valid_key(char *key)
{
	int i;

	i = 0;
	if (ft_isalpha(key[i]) == 0 && key[i] != '_')
		return (0);
	i++;
	while (key[i])
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	exec_export(t_shell *shell)
{
	int		i;
	int		j;
	char	*key;
	char	*val;

	i = 0;
	
	
	while(shell->parser->args)
	{
		j = 0;
		while (((char *)shell->parser->args->content)[j])
		{
			if (((char *)shell->parser->args->content)[j] == '=')
				break ;
			j++;
		}
		key = ft_substr(shell->parser->args->content, 0, j);
		if (is_valid_key(key) == 0)
		{
			error(shell, "export: `%s': not a valid identifier", (char *)shell->parser->args->content);
			break ;
		}
		val = ft_substr(shell->parser->args->content, j + 1, ft_strlen(shell->parser->args->content) - j + 1);
		env_push(&shell->env,key, val);
		shell->parser->args = shell->parser->args->next;
		error(shell, NULL, NULL);
	}
}

