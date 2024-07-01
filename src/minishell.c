/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaydogd <emaydogd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:02:35 by emaydogd          #+#    #+#             */
/*   Updated: 2024/07/01 13:07:05 by emaydogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>

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
	char *buf;

	while (1) {
		printf("\033[36;1m%s\033[0m", "➜ minishell$ ");
		buf = readline("");
		if (!buf)
			return ;
		buf[ft_strlen(buf)] = '\0';
		printf("line: %s\n", buf);
		// ... parse & execute with var line
	}
}

int main() {
	minishell();
	return 0;
}
