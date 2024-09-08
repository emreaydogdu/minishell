/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:10:13 by chbachir          #+#    #+#             */
/*   Updated: 2024/09/08 22:53:56 by emaydogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_bin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	else
		return (0);
}

void	exec_bin(char *cmd, char **args, char **env)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		exec_echo(args);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		exec_pwd();
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		exec_cd(args);
	/*else if (ft_strncmp(cmd, "env", 3) == 0)
		exec_env(env);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		exec_export(args);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		exec_unset(args);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		exec_exit(); */
}
