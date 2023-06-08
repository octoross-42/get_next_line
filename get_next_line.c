/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:44:08 by octoross          #+#    #+#             */
/*   Updated: 2023/06/08 19:06:43 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_read_line(int fd, char *sol)
{
	t_list	*new;
	t_list	*head;
	int		i;
	int		something;

	head = ft_lstnew();
	something = 0;
	if (!head)
		return (NULL);
	new = head;
	if (sol)
	{
		printf("sol : %s\n", sol);
		new->content = sol;
		sol = NULL;
		new->next = ft_lstnew();
		if (!new->next)
			return (ft_lstclear(&head, free));
		new = new->next;
	}
	while (read(fd, new->content, BUFFER_SIZE) > 0)
	{
		something = 1;
		i = find_eol(new->content);
		if (i >= 0)
		{
			sol = strdup(&(new->content[i + 1]));
			if (!sol)
				return (ft_lstclear(&head, free));
			new->content[i + 1] = '\0';
			return (head);
		}
		else
		{
			new->next = ft_lstnew();
			if (!(new->next))
				return (ft_lstclear(&head, free));
			new = new->next;
		}
	}
	if (something)
		return (head);
	return (ft_lstclear(&head, free));
}

char	*line_of_lst(t_list *lst)
{
	int		size;
	char	*line;
	int		i;

	if (!lst)
		return (NULL);
	size = ft_lstsize(lst);
	if (size < 0)
		return (NULL);
	line = (char *)malloc(sizeof(char) * (size + 1));
	if (!line)
		return (NULL);
	line[size] = '\0';
	i = 0;
	while (lst)
	{
		i += ft_append(&line[i], lst->content);
		lst  = lst->next;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	t_list		*lst_line;
	char		*line;
	static char	*sol = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	lst_line = ft_read_line(fd, sol);
	line = line_of_lst(lst_line);
	ft_lstclear(&lst_line, free);
	return (line);
}
