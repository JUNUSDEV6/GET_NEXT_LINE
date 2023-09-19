/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youneshanafi <youneshanafi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:45:56 by youneshanaf       #+#    #+#             */
/*   Updated: 2023/09/19 09:12:59 by youneshanaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10 
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}				t_list;

int		found_newline(t_list *list);
t_list	*find_last_node(t_list *list);
char	*get_line(t_list *list);
void	str_copy(t_list *list, char *str);
int		len_newline(t_list *list);
void	polish_list(t_list **list);
char	*get_next_line(int fd);
void	dealloc(t_list **list, t_list *clean_node, char *buff);
void	create_list(t_list **list, int fd);

#endif