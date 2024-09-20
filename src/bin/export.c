/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:32:10 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/20 18:02:07 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_export(t_shell *shell, t_parser *parser)
{
	int		i;
	int		j;
	char	*key;
	char	*val;

	i = 0;
	
	
	while(parser->args)
	{
		j = 0;
		while (((char *)parser->args->content)[j])
		{
			if (((char *)parser->args->content)[j] == '=')
				break ;
			j++;
		}
		key = ft_substr(parser->args->content, 0, j);
		val = ft_substr(parser->args->content, j + 1, ft_strlen(parser->args->content) - j + 1);
		env_push(&shell->env,key, val);
		parser->args = parser->args->next;
	}
}
