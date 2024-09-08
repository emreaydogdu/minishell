/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaydogd <emaydogd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:27:23 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/08 21:28:21 by emaydogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cd(char **args)
{
	char	*home;

	home = getenv("HOME");
	if (args[1] == NULL || args[1] == "~")
	{
		if (chdir(home) == 0)
			printf("%s\n", ".");
	}
	else if (chdir(args[1]) == 0)
		printf("%s\n", ".");
}
