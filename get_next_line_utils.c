/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:33:07 by octoross          #+#    #+#             */
/*   Updated: 2023/11/23 15:57:19 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_clear_leftovers(t_list **leftovers)
{
	t_list	*next;
	t_list	*to_free;

	if (!(*leftovers))
		return ;
	next = *leftovers;
	while (next)
	{
		if (next->content)
			free(next->content);
		to_free = next;
		next = next->next;
		free(to_free);
	}
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

// # include <stdio.h>
// # include <fcntl.h>

// int	main(int argc, char **argv)
// {
// 	int	fd;
// 	char	*line;

// 	fd = 0;
// 	if (argc > 1)
// 		fd = open(argv[1], O_RDONLY);
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
