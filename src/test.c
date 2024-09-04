/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:45:30 by chbachir          #+#    #+#             */
/*   Updated: 2024/09/04 15:22:03 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "minishell.h"
#include "../libft/libft.h"

#define MAX_PATH_LENGTH 1024

char* find_ls_path(char * cmd)
{
    static char ls_path[MAX_PATH_LENGTH];
    int dir_length;
    char* current_dir;

    if (getenv("PATH") == NULL)
        return NULL;
	current_dir = getenv("PATH");
    while (*current_dir != '\0')
	{
        dir_length = 0;
        while (current_dir[dir_length] != ':' && current_dir[dir_length] != '\0')
            dir_length++;
        if (dir_length + 4 < MAX_PATH_LENGTH)
		{
            ft_strncpy(ls_path, current_dir, dir_length);
            ls_path[dir_length] = '/';
            ft_strcpy(ls_path + dir_length + 1, cmd);
            if (access(ls_path, X_OK) == 0)
                return ls_path;
        }
        current_dir += dir_length;
        if (*current_dir == ':')
            current_dir++;
    }
    return NULL;
}

int main() {
	char *cmd = "export";
    char* ls_path = find_ls_path(cmd);
    if (ls_path) {
        printf("Path of ls: %s\n", ls_path);
    } else {
        printf("ls not found in PATH\n");
    }
    return 0;
}
