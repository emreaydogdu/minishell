/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:10:13 by chbachir          #+#    #+#             */
/*   Updated: 2024/09/06 15:13:11 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env 	*next;
} 					t_env;

void	exec_echo(char **args)
{
	int arr_len;
	int counter;
	int i;

	counter = 0;
	while (args[counter] != NULL)
		counter++;
	i = 1;
	while (args[i] != NULL)
	{
		if (i < counter - 1)
			printf("%s ", args[i]);
		else
			printf("%s", args[i]);
		i++;
	}
}

void	exec_pwd()
{
	char *buffer;

	buffer = malloc(sizeof(char) * 4097);
	printf("%s\n", getcwd(buffer, 4097));
	free(buffer);
}

void	exec_cd(char **args)
{
	char *home = getenv("HOME");
	
	if (args[1] == NULL || args[1] == "~")
	{
		if(chdir(home) == 0)
			printf("%s\n", get_current_dir_name());
	}
	else if(chdir(args[1]) == 0)
		printf("%s\n", get_current_dir_name());
	
}

void	exec_env(char **env)
{
	int i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void	exec_export(char **args)
{
	
}

void	exec_builtin(char *cmd, char **args, char **env)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		exec_echo(args);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		exec_pwd();
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		exec_cd(args);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		exec_env(env);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		exec_export(args);
	/*else if (ft_strncmp(cmd, "unset", 5) == 0)
		exec_unset(args);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		exec_exit(); */
}

int is_builtin(char *cmd)
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

void	create_env_lst(t_env env, char **m_env)
{
	int i = 0;
	int j;
	while (m_env[i])
	{
		ft_split(m_env[i], '=');
	}
}

int main (int ac, char **av, char **env)
{
	t_env env;

	

	
	char *cmd = "export";
	char *args[] = {"export", "", NULL};
	
	if (is_builtin(cmd))
		exec_builtin(cmd, args, env);
	/* else
	{
		char *path = get_external_cmd_path(cmd);
		if (path)
			exec_external_cmd;(path, args, env);
		else
			printf("Command not found: %s\n", cmd); */
}



