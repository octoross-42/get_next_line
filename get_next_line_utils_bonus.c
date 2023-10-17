/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:03:05 by octoross          #+#    #+#             */
/*   Updated: 2023/10/17 15:03:05 by octoross         ###   ########.fr       */
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
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	char	*line1;
// 	char	*line2;
// 	char	*line3;

// 	if (argc < 4)
// 		return (1);
// 	fd1 = open(argv[1], O_RDONLY);
// 	fd2 = open(argv[2], O_RDONLY);
// 	fd3 = open(argv[3], O_RDONLY);
// 	printf("1 %d 2 %d 3 %d\n", fd1, fd2, fd3);
// 	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
// 		return (1);
// 	line1 = get_next_line(fd1);
// 	line2 = get_next_line(fd2);
// 	line3 = get_next_line(fd3);
// 	while (line1 || line2 || line3)
// 	{
// 		if (line1)
// 		{
// 			printf("%s", line1);
// 			free(line1);
// 			line1 = get_next_line(fd1);
// 		}
// 		if (line2)
// 		{
// 			printf("%s", line2);
// 			free(line2);
// 			line2 = get_next_line(fd2);
// 		}
// 		if (line3)
// 		{
// 			printf("%s", line3);
// 			free(line3);
// 			line3 = get_next_line(fd3);
// 		}
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }
