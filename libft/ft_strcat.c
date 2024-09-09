/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbachir <chbachir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:14:23 by chbachir          #+#    #+#             */
/*   Updated: 2024/09/09 15:15:22 by chbachir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strcat(char *dest, const char *src)
{
    char *ptr = dest;

    // Move ptr to the end of dest string
    while (*ptr != '\0')
        ptr++;

    // Copy characters from src to dest
    while (*src != '\0')
    {
        *ptr = *src;
        ptr++;
        src++;
    }

    // Add null terminator to the concatenated string
    *ptr = '\0';
    return dest;
}
