/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:39:27 by octoross          #+#    #+#             */
/*   Updated: 2023/06/08 17:58:24 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew()
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->content = (char *)malloc(sizeof(char) * (BUFFER_SIZE));
	if (!new->content)
		return (0);
	new->content[BUFFER_SIZE - 1] = '\0';
	new->next = 0;
	return (new);
}
