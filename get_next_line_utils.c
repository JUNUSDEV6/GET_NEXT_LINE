/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:57:20 by yohanafi          #+#    #+#             */
/*   Updated: 2023/05/26 12:05:30 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// look for a newline charactere in the given linked list
int	found_newline(t_list *stock)
{
	int		i;
	t_list	*current;

	if (!stock)
		return (0);
	current = ft_lst_get_last(stock);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*ft_lst_get_last(t_list *stock)
{
	t_list	*current;

	current = stock;
	while (current && current->next)
		current = current->next;
	return (current);
}

//calculates the number of chars in the lines including the \n 
//and then convert the size into malloc
void	generate_line(char **line, t_list *stock)
{
	int	i;
	int	len;

	len = 0;
	while (stock)
	{
		i = 0;
		while (stock->content[i])
		{
			if (stock->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stock = stock->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	free_stock(t_list *stock)
{
	t_list	*current;
	t_list	*next;

	current = stock;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
