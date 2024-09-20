/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:10:13 by chbachir          #+#    #+#             */
/*   Updated: 2024/09/20 19:11:33 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_path(t_parser *parser, char * cmd)
{
	char * cmd_path;
	char		*buffer;

	buffer = malloc(sizeof(char) * 100 + 1);
	cmd_path = get_external_cmd_path(cmd);
	if (parser->infile != STDIN_FILENO)
	{
		dup2(parser->infile, STDIN_FILENO);
	}
	exec_cmd(cmd_path, cmd);
}

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

void	exec_bin(t_shell *shell, char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		exec_echo(shell);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		exec_pwd(shell);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		exec_cd(shell);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		exec_export(shell);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		exec_unset(shell);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		exec_env(*shell);
	else if (ft_strncmp(cmd, "exit", 4) == 0 && (shell->cmdline[4] == '\0' || shell->cmdline[4] == ' '))
		exec_exit(shell);
	else
		exec_path(shell->parser, cmd);
}
