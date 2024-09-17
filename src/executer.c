/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:10:13 by chbachir          #+#    #+#             */
/*   Updated: 2024/09/17 14:00:32 by chbachir         ###   ########.fr       */
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
		read(parser->infile, buffer, 100);
		printf("Buffer in exectur.c %s\n", buffer);
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

void	exec_bin(t_shell *shell, char *cmd, char **args)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		exec_echo(shell->parser);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		exec_pwd();
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		exec_cd(args);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		exec_export(shell, args);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		exec_unset(shell, args);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		exec_env(shell);
	else if (ft_strncmp(cmd, "exit", 4) == 0 && (shell->cmdline[4] == '\0' || shell->cmdline[4] == ' '))
		exec_exit(shell);
	else
		exec_path(shell->parser, cmd);
}
