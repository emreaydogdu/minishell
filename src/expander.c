/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:16:34 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/30 15:38:48 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	write_single_quotes(char *input)
{
	int	first_quote;
	int	last_quote;
	int i = 0;
	
	while (input[i])
	{
		if(input[i] == '\'')
		{
			first_quote = i;
			break ;
		}
		i++;
	}
	while (input[i])
		i++;
	while (i >= 0)
	{
		if(input[i] == '\'')
		{
			last_quote = i;
			break ;
		}
		i--;
	}
	printf("%s\n", ft_substr(input, first_quote + 1, last_quote - first_quote - 1));
} */

/* int	correct_single_quotes(char * input)
{
	int	nb_quotes;
	int	i;

	nb_quotes = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			nb_quotes++;
		i++;
	}
	if (nb_quotes >= 1 && (nb_quotes % 2) == 0)
	{
		write_single_quotes(input);
		return (1);
	}
	else if (nb_quotes >= 1 && (nb_quotes % 2) == 1)
	{
		printf("!!! Error missing quotes etc...\n");
		return (0);
	}
	return (0);
} */

void expander(t_shell *shell)
{
    t_lexer *lexer;
    int i;
    int j;
    int single_quote;
    char *key;
    char *key_env;
    char *start;
    char *end;
    char *dest;

    dest = NULL;
    lexer = shell->lexer;

    while (lexer)
    {
        i = 0;
        single_quote = 0;

        while (lexer->input[i])
        {
            if (lexer->input[i] == '\'')
                single_quote = !single_quote;

            if (lexer->input[i] == '$' && !single_quote)
            {
                // Handle special variable '$?'
                if (lexer->input[i + 1] == '?')
                {
                    key_env = ft_itoa(shell->exit_status);
                    if (!key_env)
                        return ; // Handle memory allocation failure

                    // Set j to skip '$?'
                    j = i + 2;
                }
                else
                {
                    // Find the end of the environment variable name
                    j = i + 1;
                    while (lexer->input[j] && lexer->input[j] != ' ' &&
                           lexer->input[j] != '"' && lexer->input[j] != '\'' &&
                           ( (lexer->input[j] >= 'A' && lexer->input[j] <= 'Z') ||
                             (lexer->input[j] >= 'a' && lexer->input[j] <= 'z') ||
                             (lexer->input[j] >= '0' && lexer->input[j] <= '9') ||
                             lexer->input[j] == '_'))
                        j++;

                    // Extract the key name
                    key = ft_substr(lexer->input, i + 1, j - i - 1);
                    if (!key)
                        return ; // Handle memory allocation failure

                    if (ft_strcmp(key, "") == 0)
                    {
                        // If the key is empty, skip the '$' symbol
                        free(key);
                        i++;
                        continue ;
                    }

                    // Retrieve the environment variable value
                    key_env = ft_getenv(shell, key);
                    if (key_env == NULL)
                        key_env = "";
                    free(key);
                }

                // Extract the parts before and after the variable
                start = ft_substr(lexer->input, 0, i);
                if (!start)
                    return ; // Handle memory allocation failure

                end = ft_substr(lexer->input, j, strlen(lexer->input) - j);
                if (!end)
                {
                    free(start);
                    return ; // Handle memory allocation failure
                }

                // Allocate memory for the new string
                dest = ft_calloc(strlen(start) + strlen(key_env) + strlen(end) + 1, sizeof(char));
                if (!dest)
                {
                    free(start);
                    free(end);
                    return ; // Handle memory allocation failure
                }

                // Concatenate start, key_env, and end to form the new string
                ft_strcat(dest, start);
                ft_strcat(dest, key_env);
                ft_strcat(dest, end);

                // Update lexer->input with the new string
                free(lexer->input);
                lexer->input = ft_strdup(dest);
                if (!lexer->input)
                {
                    free(start);
                    free(end);
                    free(dest);
                    return ; // Handle memory allocation failure
                }

                // Free temporary strings
                free(start);
                free(end);
                free(dest);

                // Move the index to continue parsing after the replaced variable
                i += strlen(key_env);
            }
            else
            {
                i++;
            }
        }

        lexer = lexer->next;
    }
}


/* void	expander(t_shell *shell)
{
	t_lexer * lexer;
	int			i;
	int			j;
	int			single_quote;
	char		*key;
	char		*key_env;
	char		*start;
	char		*end;
	char		*dest;
	
	dest = NULL;
	lexer = shell->lexer;

	//correct_single_quotes(shell->cmdline); // Chakib : not supposed to write here, should be done in executer
	while (lexer)
	{
		i = 0;
		single_quote = 0;
		while (lexer->input[i])
		{
			if (lexer->input[i] == '\'')
				single_quote = !single_quote;
			if (lexer->input[i] == '$' && !single_quote)
			{
				start = ft_substr(lexer->input, 0,  i);
				j = i;
				while (lexer->input[j] != ' ' && lexer->input[j] != '"'  && lexer->input[j] != '\'' && lexer->input[j])
					j++;
				if (lexer->input[i + 1] == '?')
				{
					key_env = ft_itoa(shell->exit_status);
				}
				else
				{
					key = ft_substr(lexer->input, i + 1, j - i - 1);
					if (ft_strcmp(key, "") == 0)
					{
						i++;
						continue ;
					}
					key_env = ft_getenv(shell, key);
					if (key_env == NULL)
						key_env = "";
					free(key);
				}
				end = ft_substr(lexer->input,j, ft_strlen(lexer->input) - j + 1);
				dest = ft_calloc((ft_strlen(start) + ft_strlen(key_env) + ft_strlen(end) + 1), sizeof(char));
				if (!dest)
				 	return ;
				dest = ft_strcat(dest, start);
				dest = ft_strcat(dest, key_env);
				dest = ft_strcat(dest, end);
				lexer->input = ft_strdup(dest);

				free(start);
				//free(key_env); // Chakib : ATTENTION with SEGFAULT
				free(end);
				free(dest);
				i = j;
			}
			i++;
		}
		lexer = lexer->next;
	}
} */
