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

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
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

typedef struct s_list_manager
{
	int						fd;
	t_list					*line;
	struct s_list_manager	*next;
}		t_list_manager;

#endif