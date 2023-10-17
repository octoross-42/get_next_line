/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:03:36 by octoross          #+#    #+#             */
/*   Updated: 2023/10/17 15:03:38 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (*lst)
	{
		if ((*lst)->next)
		{
			ft_lstclear(&(*lst)->next, del);
			free((*lst)->next);
		}
		del((*lst)->content);
		free(*lst);
	}
	*lst = 0;
	return (NULL);
}

t_list	*ft_lstnew(void)
{
	t_list	*new;
	int		i;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->content = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!new->content)
		return (0);
	i = 0;
	while (i < BUFFER_SIZE + 1)
		new->content[i++] = '\0';
	new->next = 0;
	new->eof = 0;
	return (new);
}

int	ft_lstsize(t_list *lst)
{
	int	size;
	int	len;

	if (!lst)
		return (-1);
	size = 0;
	while (lst)
	{
		len = 0;
		while (lst->content[len])
			len ++;
		size += len;
		lst = lst->next;
	}
	return (size);
}

int	ft_append(char *str, char *to_add)
{
	int	i;

	if (!str || !to_add)
		return (-1);
	i = 0;
	while (to_add[i])
	{
		str[i] = to_add[i];
		i ++;
	}
	str[i] = '\0';
	return (i);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*dup;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
		i ++;
	dup = (char *)malloc(sizeof(char) * (i + 1));
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
