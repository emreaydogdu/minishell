/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:32:10 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/09 13:30:06 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_export(t_shell *shell, char **args)
{
	int		i;
	int		j;
	char	*key;
	char	*val;

	i = 1;
	while(args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '=')
				break ;
			j++;
		}
		key = ft_substr(args[i], 0, j);
		val = ft_substr(args[i], j + 1, ft_strlen(args[i]) - j + 1);
		env_push(&shell->env,key, val);
		i++;
	}
}
