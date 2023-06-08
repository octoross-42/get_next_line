/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:32:42 by octoross          #+#    #+#             */
/*   Updated: 2023/06/07 21:17:02 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	if (!lst)
		return (-1);
	size = 0;
	while (lst)
	{
		size += ft_strlen(lst->content);
		lst = lst->next;
	}
	return (size);
}
