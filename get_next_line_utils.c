/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:45:15 by octoross          #+#    #+#             */
/*   Updated: 2023/06/08 19:04:40 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_append(char *str, char *to_add)
{
	int	i;

	i = 0;
	while (to_add[i])
	{
		str[i] = to_add[i];
		i ++;
	}
	return (i);
}

int	find_eol(char *str)
{
	int	i;
	
	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i ++;
	}
	return (-1);
}

char	*strdup(char *str)
{
	int		i;
	char	*dup;

	i = 0;
	while (str[i])
		i ++;
	dup = (char *)malloc(sizeof(char) * i);
	if (!dup)
		return (NULL);
	dup[i] = '\0';
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i ++;
	}
	return (dup);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len ++;
	return (len);
}
