/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_tetriminos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:42:45 by vlaine            #+#    #+#             */
/*   Updated: 2022/02/17 19:42:45 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/* Creates new struct element for a new tetrimino piece and allocates memory
** for 'char **tetrimino' inside the struct. In case of an error, free the
** already allocated memory and exit.
*/

static t_tlist	*new_tetrimino(t_tlist *head)
{
	t_tlist	*new;

	new = malloc(sizeof(t_tlist));
	if (new == NULL)
	{
		free_list(head);
		exit (0);
	}
	new->tetrimino = (char **)malloc(sizeof(char *) * (4 + 1));
	if (new->tetrimino == NULL)
	{
		free(new);
		free_list(head);
		exit (0);
	}
	new->tetrimino[4] = NULL;
	new->next = NULL;
	return (new);
}

static int	read_line(int fd, t_tlist *temp, int index)
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

static int	read_empty_line(int fd)
{
	char	line[6];
	int		gnl;

	gnl = 0;
	ft_bzero(line, 5);
	gnl = (int)read(fd, &line, 1);
	if (line[0] != '\n' || gnl != (int)ft_strlen(line))
		return (-1);
	return (gnl);
}

/* Reads the tetriminos from the file one line at a time.
** Saves the complete tetriminos to their own structs in 4 line cycles.
** Forms a linked list from the structs and sends the head of the list forward.
*/

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
		gnl = read_line(fd, temp, index++);
		if (gnl < 1)
			temp->tetrimino[index] = NULL;
		else if (index == 4)
		{
			gnl = read_empty_line(fd);
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
** In case of an error, the program exits.
*/

void	handle_fd(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl("error");
		exit (0);
	}
	copy_tetriminos(fd);
	if (close(fd) == -1)
	{
		ft_putendl("error");
		exit (0);
	}
}
