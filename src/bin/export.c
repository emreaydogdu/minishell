/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:32:10 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/09 11:54:27 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_export(t_shell *shell, char **args)
{
	int i;
	char **res;

	

	i = 1;
	while(args[i])
	{
		res = ft_split(args[i], '=');
		env_push(&shell->env,res[0], res[1]);
		i++;
	}
	// use env_Push
}
