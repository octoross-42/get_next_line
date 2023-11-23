/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:03:26 by octoross          #+#    #+#             */
/*   Updated: 2023/10/17 15:03:26 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H

# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

typedef struct s_list
{
	char			*content;
	int				eof;
	int				eol;
	int				len;
	int				start;
	struct s_list	*next;
}		t_list;

typedef struct s_manager
{
	int					fd;
	int					size;
	t_list				**line;
	struct s_manager	*next;
}		t_fm;

void	ft_clear_manager(t_fm **fm, int fd, t_fm *previous, t_fm *current);
void	ft_clean_and_next_lst(t_list **line);

char	*get_next_line(int fd);

#endif