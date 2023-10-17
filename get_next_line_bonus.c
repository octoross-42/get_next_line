/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:03:17 by octoross          #+#    #+#             */
/*   Updated: 2023/10/17 15:03:17 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_fm	*ft_get_fd(t_fm **leftovers, int fd, t_fm *previous, t_fm *current)
{
	t_fm	*fm;

	if (current && current->fd == fd)
		return (current);
	if (current)
		return (ft_get_fd(leftovers, fd, current, current->next));
	fm = (t_fm *)malloc(sizeof(t_fm));
	if (!fm)
		return (NULL);
	fm->size = 0;
	fm->fd = fd;
	fm->next = NULL;
	fm->line = (t_list **)malloc(sizeof(t_list *));
	if (!(fm->line))
		return (free(fm), NULL);
	*(fm->line) = NULL;
	if (previous)
		previous->next = fm;
	else
		*leftovers = fm;
	return (fm);
}

t_list	*ft_read_line(int fd, t_fm *fm)
{
	t_list	*line;
	int		i;

	line = (t_list *)malloc(sizeof(t_list));
	if (!line)
		return (NULL);
	line->content = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!(line->content))
		return (free(line), NULL);
	line->start = 0;
	line->len = read(fd, line->content, BUFFER_SIZE);
	if (line->len <= 0)
		return (free(line->content), free(line), NULL);
	i = line->len;
	while (i <= BUFFER_SIZE)
		line->content[i ++] = '\0';
	i = 0;
	while (i < line->len && line->content[i] != '\n')
		i ++;
	line->eof = (line->len < BUFFER_SIZE);
	line->eol = -1 + (i + 1) * (i < line->len);
	line->next = NULL;
	fm->size += (line->eol + 1) * (line->eol >= 0)
		+ line->len * (line->eol < 0);
	return (line);
}

int	ft_read(t_fm *fm, t_list **line, int fd)
{
	t_list	*next;

	if (!(*line))
		*line = ft_read_line(fd, fm);
	if (!(*line))
		return (1);
	next = *line;
	while (next->eol < 0 && !(next->eof))
	{
		next->next = ft_read_line(fd, fm);
		if (!(next->next))
			next->eof = 1;
		else
			next = next->next;
	}
	return (0);
}

char	*ft_lst_to_str(t_fm *fm, t_list **l)
{
	char	*return_line;
	int		i;
	int		j;
	int		eol_reached;

	return_line = (char *)malloc(sizeof(char) * (fm->size + 1));
	if (!return_line)
		return (NULL);
	return_line[fm->size] = '\0';
	i = 0;
	eol_reached = 0;
	while (!eol_reached)
	{
		j = (*l)->start;
		while (j <= (*l)->eol || (((*l)->eol < 0) && j < (*l)->len))
			return_line[i ++] = (*l)->content[j ++];
		(*l)->start = j;
		while (j < (*l)->len && (*l)->content[j] != '\n')
			j ++;
		eol_reached = ((*l)->eol >= 0 || (*l)->eof);
		fm->size = (j + (j < (*l)->len) - (*l)->start) * ((*l)->eol >= 0);
		(*l)->eol = -1 + (j + 1) * (j < (*l)->len);
		ft_clean_and_next_lst(l);
	}
	return (return_line);
}

char	*get_next_line(int fd)
{
	static t_fm	*leftovers = NULL;
	t_fm		*fm;
	char		*return_line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (ft_clear_manager(&leftovers, fd, NULL, leftovers), NULL);
	fm = ft_get_fd(&leftovers, fd, NULL, leftovers);
	if (!fm)
		return (ft_clear_manager(&leftovers, -1, NULL, leftovers), NULL);
	if (ft_read(fm, fm->line, fd))
		return (ft_clear_manager(&leftovers, fd, NULL, leftovers), NULL);
	return_line = ft_lst_to_str(fm, fm->line);
	if (!return_line)
		return (ft_clear_manager(&leftovers, fd, NULL, leftovers), NULL);
	return (return_line);
}
