/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:57:44 by marvin            #+#    #+#             */
/*   Updated: 2023/10/08 11:57:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_clear_manager(t_fm **fm, int fd, t_fm *previous, t_fm *current)
{
	t_list	*next;
	t_list	*to_free;

	if (!current)
		return ;
	if (fd < 0 || current->fd == fd)
	{
		next = *(current->line);
		while (next)
		{
			if (next->content)
				free(next->content);
			to_free = next;
			next = next->next;
			free(to_free);
		}
		free(current->line);
		if (previous)
			previous->next = current->next;
		else
			*fm = current->next;
		free(current);
	}
	else if (current->next)
		ft_clear_manager(fm, fd, current, current->next);
}

void	ft_clean_and_next_lst(t_list **line)
{
	t_list	*to_free;

	if ((*line)->start >= (*line)->len)
	{
		to_free = *line;
		*line = (*line)->next;
		free(to_free->content);
		free(to_free);
	}
}

// void	print_state(t_fm *lm)
// {
// 	t_list	*l;

// 	printf("\nstate :\n");
// 	while (lm)
// 	{
// 		printf("\nfd = %d size %d\n\n", lm->fd, lm->size);
// 		l = *(lm->line);
// 		while (l)
// 		{
// 			printf("'%s'\tstart : %d, eol : %d len %d eof : %d\n",
// 				l->content, l->start, l->eol, l->len, l->eof);
// 			l = l->next;
// 		}
// 		lm = lm->next;
// 	}
// }

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;

// 	fd = 0;
// 	if (argc < 2)
// 		return (1);
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }
