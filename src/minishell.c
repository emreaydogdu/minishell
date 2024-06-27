/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaydogd <emaydogd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:02:35 by emaydogd          #+#    #+#             */
/*   Updated: 2024/06/27 15:00:12 by emaydogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void minishell()
{
	char *line = NULL;
	size_t len = 0;

	while (1) {
		printf("\033[36;1m%s\033[0m", "➜ minishell$ ");
		if (getline(&line, &len, stdin) == -1)
			break;
		printf("%s", line);
		line[ft_strlen(line)-1] = '\0';
		// ... parse & execute with var line
	}
	free(line);
}

int main() {
	minishell();
	return 0;
}
