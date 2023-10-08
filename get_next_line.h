/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:45:17 by octoross          #+#    #+#             */
/*   Updated: 2023/10/08 12:03:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
	int				eof;
}		t_list;

char	*get_next_line(int fd);
void	ft_lstadd_back(t_list **lst, t_list *new);

void	ft_lstdelone(t_list *lst, void (*del)(void *));
int		ft_lstsize(t_list *lst);
char	*ft_lstclear(t_list **lst, void (*del)(void *));

int		ft_append(char *str, char *to_add);
char	*ft_strdup(char *str);
int		find_eol(char *str);

t_list	*ft_lstnew(void);

#endif