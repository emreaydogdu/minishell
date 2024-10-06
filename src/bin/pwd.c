/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:24:37 by emaydogd          #+#    #+#             */
/*   Updated: 2024/10/02 12:18:01 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pwd(t_shell *shell)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * 4097);
	printf("%s", getcwd(buffer, 4097));
	error(shell, NULL, NULL);
	free(buffer);
}
