/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaydogd <emaydogd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:31:20 by emaydogd          #+#    #+#             */
/*   Updated: 2024/06/29 16:31:20 by emaydogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "execute.h"
#include <stdio.h>

int execute_echo(char **args)
{
	int i = 1;

	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
	return (0);
}
