/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_tetriminos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:41:01 by raho              #+#    #+#             */
/*   Updated: 2022/02/11 15:16:42 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/* Creates new struct element for a new tetrimino piece and allocates memory
** for 'char **tetrimino' inside the struct. In case of an error, free the
** already allocated memory and exit with error codes.
*/

static t_tlist	*new_tetrimino(t_tlist *head)
{
	t_tlist	*new;

	new = malloc(sizeof(t_tlist));
	if (new == NULL)
	{
		free_list(head);
		exit (3);
	}
	new->tetrimino = (char **)malloc(sizeof(char *) * (4 + 1));
	if (new->tetrimino == NULL)
	{
		free(new);
		free_list(head);
		exit (4);
	}
	new->tetrimino[4] = NULL;
	new->next = NULL;
	return (new);
}

/* Reads the tetriminos from the file one line at a time using get_next_line.
** Saves the complete tetriminos to their own structs in 4 line cycles.
** Forms a linked list from the structs and sends the head of the list forward.
*/

static int	read1(int fd, t_tlist *temp, int index)
{
	char	line[6];
	size_t	len;
	int		gnl;

	gnl = 0;
	ft_bzero(line, 6);
	gnl = (int)read(fd, &line, 5);
	temp->tetrimino[index] = ft_strdup(line);
	len = ft_strlen(temp->tetrimino[index]);
	if (len != 5 || temp->tetrimino[index][4] != '\n')
		return (-1);
	temp->tetrimino[index][4] = '\0';
	return (gnl);
}

static int	read2(int fd)
{
	char	line[6];
	int		gnl;

	gnl = 0;
	ft_bzero(line, 5);
	gnl = (int)read(fd, &line, 1);
	if (gnl != (int)ft_strlen(line))
		return (-1);
	return (gnl);
}

static void	copy_tetriminos(int fd)
{
	t_tlist	*head;
	t_tlist	*temp;
	int		gnl;
	int		index;

	head = new_tetrimino(NULL);
	temp = head;
	gnl = 1;
	index = 0;
	while (gnl > 0)
	{
		gnl = read1(fd, temp, index++);
		if (gnl < 1)
			temp->tetrimino[index] = NULL;
		else if (index == 4)
		{
			gnl = read2(fd);
			if (gnl > 0)
				temp->next = new_tetrimino(head);
			if (gnl > 0)
				temp = temp->next;
			index = 0;
		}
	}
	check_errors(head, gnl);
}

/* Opens the file given as an argument on the command line.
** Sends the file descriptor forward.
** Closes the file after the solving is done.
** In case of an error, the program exits with error code 1.
*/

void	handle_fd(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl("error");
		exit (2);
	}
	copy_tetriminos(fd);
	if (close(fd) == -1)
	{
		ft_putendl("error");
		exit (9);
	}
}
