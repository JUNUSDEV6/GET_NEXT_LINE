/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youneshanafi <youneshanafi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:57:13 by yohanafi          #+#    #+#             */
/*   Updated: 2023/05/11 15:07:42 by youneshanaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*stock;
	char			*line;
	int				readed;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) <0)
		return (NULL);
	readed = 1;
	line = NULL;
	// 1. read from fd and add to linked list
	read_and_stock(fd, &stock, &readed);
	if (!stock)
		return (NULL);
	// 2. extract from stock to line
	extract_line(stock, &line);
	// 3. clean up stock
	clean_stock(&stock);
	return (line);
}

void	read_and_stock(int fd, t_list **stock, int *readed_ptr)
{
	char *buf;

	while (found_newline(*stock) || *readed_ptr != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		*readed_ptr = (int)read(fd, buf, BUFFER_SIZE);
		if ((!stock && *readed_ptr == 0) || *readed_ptr == -1)
			return (free(buf));
		buf[*readed_ptr] = '\0';
		add_to_stock(stock, buf, readed_ptr);
		free(buf);
	}
}

// addts the content of our buffer to your end of our stock

void	add_to_stock(t_list **stock, char *buf, int readed)
{
	int	i;
	t_list *last;
	t_list *new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) *(readed + 1));
	if (!new_node->content)
		return ;
	i = 0;
	while (buf[i] && i < readed)
	{
		new_node->content[i] = buf[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (!*stock)
		return (*stock = new_node);
	last = ft_lst_get_last(*stock);
	last->next = new_node;	
}
// extract all charactere from our stock and store them in out line;
// stopping afther the first \n it encounters 

void	extract_line(t_list *stock, char **line)
{
	int	i;
	int	j;

	if (!stock)
		return ;
	generate_line(line, stock);
	if (!*line)
		return ;
	while (stock)
	{
		i = 0;
		while (stock->content[i])
		{
			if (stock->content[i] == '\n')
			{
				(*line)[j++] = stock->content[i];
				break;
			}
			(*line)[j++] = stock->content[i++];
		}
		stock = stock->next;
	}
	(*line)[j] = '\0';
}

/* afther extracting the line that was read, we don't need those charactere anaymore
this fonction clear the stock so only the characters thathave not been returned at the end of get_next_line() remain in our static stock;
*/

void	clean_stock(t_list **stock)
{
	t_list *last;
	t_list *clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (!stock || !clean_node)
		return ;
	clean_node->next = NULL;
	last = ft_lst_get_last(*stock);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i) + 1));
	if (!clean_node->content)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_stock(*stock);
	*stock = clean_node;
}
int main()
{
	int		fd;
	char	*line;

	fd = open("test/simple");
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		printf("%s", line);
		free(line);
	}
}