/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:32:10 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/20 19:47:12 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		val = ft_substr(shell->parser->args->content, j + 1, ft_strlen(shell->parser->args->content) - j + 1);
		env_push(&shell->env,key, val);
		shell->parser->args = shell->parser->args->next;
	}
}
