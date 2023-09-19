/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youneshanafi <youneshanafi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:02:01 by youneshanaf       #+#    #+#             */
/*   Updated: 2023/09/19 11:15:46 by youneshanaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void    polish_list(t_list **list)
{
	t_list  *last_node;
	t_list  *clean_node;
	int     i;
	int     j;
	char    *buff;
	
	buff = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (buff == NULL || clean_node == NULL)
		return;
	last_node = find_last_node(*list);
	i = 0;
	j = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		++i;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		buff[j++] = last_node->str_buf[i];
	buff[j] = '\0';
	clean_node->str_buf = buff;
	clean_node->next = NULL;
	dealloc(list, clean_node, buff);
}

char    *get_line(t_list *list)
{
	int     len_str;
	char    *next_str;
	
	if (list == NULL)
		return (NULL);
	len_str = len_newline(list);
	next_str = malloc(len_str + 1);
	if (next_str == NULL)
		return (NULL);
	str_copy(list, next_str);
	return (next_str);
}

void    add(t_list **list, char *buff)
{
	t_list  *new_node;
	t_list  *last_node;
	
	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buff;
	new_node->next = NULL;
}

void    create_list(t_list **list, int fd)
{
	int     cnt_chr;
	char    *buff;
	
	while (!found_newline(*list))
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (buff == NULL)
			return ;
		cnt_chr = read(fd, buff, BUFFER_SIZE);
		if (!cnt_chr)
		{
			free(buff);
			return ;
		}
		buff[cnt_chr] = '\0';
		add(list, buff);
	}
}

char    *get_next_line(int fd)
{
	static t_list   *list = NULL;
	char            *next_line;
	
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = get_line(list);
	polish_list(&list);
	return(next_line);
	
}
