/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaydogd <emaydogd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:16:34 by emaydogd          #+#    #+#             */
/*   Updated: 2024/09/01 17:26:53 by emaydogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void expander(t_shell *shell)
{
	int	i;
	char	*tmp;

	i = 0;
	while (shell->lexer[i].input)
	{
		if (shell->lexer[i].input[0] == '$')
		{
			int len = ft_strlen(shell->lexer[i].input);
			tmp = ft_substr(shell->lexer[i].input, 1, len -1 );
			char *env = getenv(tmp);
			shell->lexer[i].input = env;
		}
		i++;
	}
}