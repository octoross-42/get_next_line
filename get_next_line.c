/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:44:08 by octoross          #+#    #+#             */
/*   Updated: 2023/06/10 03:41:38 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free_and_null(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
	return (NULL);
}

int	ft_found_eol(char **leftover,
	t_list *next, t_list **to_return)
{
	int		eol_index;

	eol_index = 0;
	while (next->content[eol_index])
	{
		if (next->content[eol_index] == '\n')
			break ;
		eol_index ++;
	}
	if (!(next->content[eol_index]))
		return (0);
	if (eol_index + 1 == BUFFER_SIZE)
		ft_free_and_null(leftover);
	else
	{
		free(*leftover);
		*leftover = ft_strdup(&(next->content[eol_index + 1]));
		if (!(*leftover))
		{
			ft_lstclear(to_return, free);
			return (1);
		}
		next->content[eol_index + 1] = '\0';
	}
	return (1);
}

t_list	*ft_read_line(int fd, t_list *to_return,
	t_list *next, char **leftover)
{
	while (read(fd, next->content, BUFFER_SIZE) > 0)
	{
		if (ft_found_eol(leftover, next, &to_return))
			return (to_return);
		next->next = ft_lstnew();
		if (!(next->next))
		{
			ft_lstclear(&to_return, free);
			return (NULL);
		}
		next = next->next;
	}
	to_return->eof = 1;
	if (*leftover)
		free(*leftover);
	*leftover = NULL;
	if (to_return->content && to_return->content[0])
		return (to_return);
	ft_lstclear(&to_return, free);
	return (NULL);
}

char	*line_of_lst(t_list *lst)
{
	int		size;
	char	*line;
	int		i;
	t_list	*head;

	if (!lst)
		return (NULL);
	head = lst;
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
		lst = lst->next;
	}
	ft_lstclear(&head, free);
	return (line);
}

char	*get_next_line(int fd)
{
	t_list		*lst;
	char		*line;
	static char	*leftover = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free_and_null(&leftover));
	lst = ft_lstnew();
	if (!lst)
		return (ft_free_and_null(&leftover));
	if (leftover)
	{
		ft_append(lst->content, leftover);
		if (ft_found_eol(&leftover, lst, &lst))
			return (line_of_lst(lst));
		lst->next = ft_lstnew();
		if (!lst->next)
			return (ft_lstclear(&lst, free));
		lst = ft_read_line(fd, lst, lst->next, &leftover);
	}
	else
		lst = ft_read_line(fd, lst, lst, &leftover);
	line = line_of_lst(lst);
	return (line);
}
