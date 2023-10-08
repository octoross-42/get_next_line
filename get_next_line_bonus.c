/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:57:47 by marvin            #+#    #+#             */
/*   Updated: 2023/10/08 11:57:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_clear_manager(t_list_manager **lm, t_list_manager *previous_manager, int fd)
{
	t_list_manager	*next_manager;
	t_list			*next;

	next_manager = (*lm)->next;
	while (next_manager && (!previous_manager || previous_manager->fd != fd))
	{
		if (next_manager->fd == fd)
		{
			next = next_manager->line;
			while (next)
			{
				if (next->content)
					free(next->content);
				next = next->next;
			}
			if (previous_manager)
				previous_manager->next = next_manager->next;
			else
				*lm = next_manager->next;
			free(next_manager);
		}
		previous_manager = next_manager;
		next_manager = next_manager->next;
	}
}

t_list	*ft_get_fd(t_list_manager **lm, int fd)
{
	t_list	*list;

	if (!lm || !(*lm))
	{
		*lm = (t_list_manager *)malloc(sizeof(t_list_manager));
		if (*(lm))
			return (NULL);
		(*lm)->line = NULL;
		(*lm)->next = NULL;
		(*lm)->fd = -1;
	}
	while (*lm)
	{
		if ((*lm)->fd == fd)
			return ((*lm)->line);
		*lm = (*lm)->next;
	}
	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (ft_clear_manager(lm, NULL, fd), NULL);
	list->content = NULL;
	list->eol = 0;
	list->len = 0;
	list->next = NULL;
	return (list);
}

void	ft_strfill(char **return_line, t_list **line, int size)
{
	t_list	*to_free;
	int	i;

	*return_line = (char *)malloc(sizeof(char) * (size + 1));
	if (!(*return_line))
		return ;
	(*return_line)[size] = '\0';
	size = 0;
	while (line && *line)
	{
		i = 0;
		while ((*line)->content[i] && ((*line)->eol < 0 || i <= (*line)->eol))
		{
			(*return_line)[size + i] = (*line)->content[i];
			i ++;
		}
		size += (*line)->len;
		if ((*line)->eol >= 0)
			return ;
		to_free = *line;
		*line = (*line)->next;
		free(to_free->content);
		free(to_free);
	}
}

char	*ft_list_to_str(t_list *l)
{
	char	*return_line;
	int		size;
	int		i;
	t_list	*next;

	size = (l->len) * (l->eol < 0) + l->eol * (l->eol >= 0) - l->start;
	next = l;
	while (next->eol < 0 && next->next)
	{
		size += next->len;
		next = next->next;
	}
	size += next->eol + 1;
	ft_strfill(&return_line, &l, size);
	if (!return_line)
		return (NULL);
	l->start += l->eol + 1;
	i = 0;
	while (l->content[i + l->start] && l->content[i + l->start] != '\n')
		i ++;
	l->eol = l->start + i;
	return (return_line);
}

int	ft_read_line(t_list_manager *manager, t_list *line, int fd)
{
	t_list	*next;
	int		i;

	if (line->eol >= 0)
		return (1);
	if (line->content)
		next = line->next;
	else
		next = line;
	while (next->eol < 0 && !next->eof)
	{
		next->content = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!(next->content))
			return (ft_clear_manager(&manager, NULL, fd), 1);
		next->content[BUFFER_SIZE] = '\0';
		next->start = 0;
		next->eof = 0;
		next->eol = -1;
		next->len = read(fd, next->content, O_RDONLY);
		if (next->len <= 0)
			return (ft_clear_manager(&manager, NULL, fd), 1);
		i = 0;
		if (next->len < BUFFER_SIZE)
			next->eof = 1;
		while (i < next->len && next->content[i] != '\n')
			i ++;
		if (i < next->len || i < BUFFER_SIZE)
			next->eol = i;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list_manager	*leftovers = NULL;
	t_list					*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (leftovers && fd >= 0)
			ft_clear_manager(&leftovers, NULL, fd);
		return (NULL);
	}
	line = ft_get_fd(&leftovers, fd);
	if (!line)
		return (NULL);
	if (ft_read_line(leftovers, line, fd))
		return (NULL);
	return (ft_list_to_str(line));
}

# include <stdio.h>

int	main(int argc, char **argv)
{
	int	fd;
	char	*line;

	fd = 0;
	if (argc > 1)
		fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}
