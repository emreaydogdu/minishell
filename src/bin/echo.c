/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaydogd <emaydogd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:05:13 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/08 21:08:54 by emaydogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_echo(char **args)
{
	int	i;
	int	counter;

	counter = 0;
	while (args[counter] != NULL)
		counter++;
	i = 0;
	while (args[++i] != NULL)
	{
		printf("%s", args[i]);
		if (i < counter - 1)
			printf(" ");
	}
}
