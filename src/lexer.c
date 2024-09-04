/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:54:47 by chbachir          #+#    #+#             */
/*   Updated: 2024/09/04 10:55:08 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_lexer(t_shell shell)
{
	const char *enum_dict[] = { "ARG", "PIPE", "TOKEN_REDIR_APPEND", "TOKEN_REDIR_HEREDOC", "TOKEN_REDIR_OUT", "TOKEN_REDIR_IN"};
	if (shell.lexer == NULL)
		printf("Lexer is empty\n");
	while (shell.lexer != NULL)
	{
		printf("%20s - type: %6s  pos: %zu\n", shell.lexer->input, enum_dict[shell.lexer->type], shell.lexer->pos);
		shell.lexer = shell.lexer->next;
	}
}

int	push(t_lexer **lexer, char *input, t_token_type type, size_t pos)
{
	t_lexer* token = malloc(sizeof(t_lexer));
	if (!token)
		return (0);
	// Assign data to the new TOKEN
	token->input = input;
	token->type = type;
	token->pos = pos;
	token->next = NULL;
	// If the linked list is empty, then make the new node as head
	if (*lexer == NULL)
	{
		*lexer = token;
		return (1);
	}
	// Else traverse till the last node
	t_lexer* last = *lexer;

	while (last->next != NULL)
		last = last->next;
	// Change the next of last node
	last->next = token;
	return (1);
}

void decode_lexer(char **str, t_shell *shell)
{
	size_t i = 0;
	size_t pos = 0;
	shell->lexer = NULL;
	while (str[i] != NULL)
	{
		if (ft_strncmp(str[i], "|", 1) == 0)
			push(&shell->lexer, "|", TOKEN_PIPE, pos);
		else if (ft_strncmp(str[i], "<<", 2) == 0)
			push(&shell->lexer, "<<", TOKEN_REDIR_APPEND, pos);
		else if (ft_strncmp(str[i], ">>", 2) == 0)
			push(&shell->lexer, ">>", TOKEN_REDIR_HEREDOC, pos);
		else if (ft_strncmp(str[i], "<", 1) == 0)
			push(&shell->lexer, "<", TOKEN_REDIR_OUT, pos);
		else if (ft_strncmp(str[i], ">", 1) == 0)
			push(&shell->lexer, ">", TOKEN_REDIR_IN, pos);
		else
			push(&shell->lexer, str[i], TOKEN_ARG, pos);
		pos++;
		i++;
	}
}

void print_cmd(t_mini *cmd)
{
	int i = 0;

	printf("		infile: %d\n", cmd->infile);
	printf("		outfile: %d\n", cmd->outfile);
	printf("		full_path: %s\n", cmd->full_path ? cmd->full_path : "NULL (because command is a builtin)");
	if (cmd->full_cmd)
	{
		while (cmd->full_cmd)
		{
			printf("		Arg[%d]: %s\n", i, (char *)cmd->full_cmd->content);
			i++;
			cmd->full_cmd = cmd->full_cmd->next;
		}
	}
	else
		printf("  No command arguments.\n");

}

void print_cmdtable(t_prompt *prompt)
{
	t_list *current_node = prompt->cmds;
	int cmd_num = 1;

	printf("Command Table:\n");
	while (current_node)
	{
		t_mini *cmd = (t_mini *)current_node->content;
		printf("\n	Command %d:\n", cmd_num++);
		print_cmd(cmd);
		current_node = current_node->next;
	}
}

t_lexer		*init_lexer(t_shell shell)
{
	char **str = ft_split(shell.cmdline, ' ');
	decode_lexer(str, &shell);
	expander(&shell);
	print_lexer(shell);


	t_prompt prompt;
	prompt.cmds = NULL;
	prompt.envp = NULL;
	prompt.pid = getpid();
	parse_tokens(shell.lexer, &prompt);
	print_cmdtable(&prompt);
	return (NULL);
}
