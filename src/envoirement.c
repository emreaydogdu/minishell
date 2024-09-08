/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envoirement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaydogd <emaydogd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:39:05 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/08 22:49:22 by emaydogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_push(t_env **env, char *key, char *value)
{
	t_env	*last;
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (0);
	node->key = key;
	node->value = value;
	node->next = NULL;
	if (*env == NULL)
		return (*env = node, 1);
	last = *env;
	while (last->next != NULL)
		last = last->next;
	return (last->next = node, 1);
}

void	init_env(t_shell *shell, char **env)
{
	int		i;
	char	**res;

	i = 0;
	while (env[i])
	{
		// TODO concatenate all string after first "="
		res = ft_split(env[i], '=');
		env_push(&shell->env, res[0], res[1]);
		i++;
	}
}
