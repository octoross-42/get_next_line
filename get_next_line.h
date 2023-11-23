/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:03:48 by octoross          #+#    #+#             */
/*   Updated: 2023/11/23 15:05:42 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
	int				eof;
}		t_list;

int		ft_lstsize(t_list *lst);
char	*ft_lstclear(t_list **lst, void (*del)(void *));
t_list	*ft_lstnew(void);
char	*ft_strdup(char *str);
int		ft_append(char *str, char *to_add);

char	*get_next_line(int fd);

#endif