/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:49:46 by octoross          #+#    #+#             */
/*   Updated: 2023/06/08 18:16:32 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int	fd;
	char	*line;

	if (argc > 1)
	{
		if (argv[1][0] == '0' && argv[1][1] == '\0')
			get_next_line(0);
		else
		{
			fd = open(argv[1], O_RDONLY);
			line = get_next_line(fd);
			while (line)
			{
				printf("%s", line);
				line = get_next_line(fd);
			}
			free(line);
			close(fd);
		}
	}
	return (0);
}
