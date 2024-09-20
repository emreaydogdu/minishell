/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:24:37 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/20 19:16:55 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pwd(t_shell *shell)
{
	char	*buffer;
	if (ft_strncmp(shell->cmdline, "pwd", ft_strlen(shell->cmdline)) != 0)
	{
		printf("pwd: too many arguments\n");
		shell->exit_status = 1;
		return ;
	}

	buffer = malloc(sizeof(char) * 4097);
	printf("%s\n", getcwd(buffer, 4097));
	free(buffer);
}
