/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:13:24 by octoross          #+#    #+#             */
/*   Updated: 2023/06/07 21:14:34 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (*lst)
	{
		if ((*lst)->next)
		{
			ft_lstclear(&(*lst)->next, del);
			free((*lst)->next);
		}
		ft_lstdelone(*lst, del);
	}
	*lst = 0;
	return (NULL);
}
