/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 12:11:45 by marvin            #+#    #+#             */
/*   Updated: 2023/10/08 12:11:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H

# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

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
t_list	*ft_read_line(int fd, t_fm *fm);
int		ft_read(t_fm *fm, t_list **line, int fd);
t_fm	*ft_get_fd(t_fm **leftovers, int fd, t_fm *previous, t_fm *current);
char	*ft_lst_to_str(t_fm *fm, t_list **line);
char	*get_next_line(int fd);

#endif