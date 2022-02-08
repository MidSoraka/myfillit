/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_tetriminos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:41:01 by raho              #+#    #+#             */
/*   Updated: 2022/02/01 23:33:15 by raho             ###   ########.fr       */
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

static void	copy_tetriminos(int fd)
{
	t_tlist *head;
	t_tlist *temp;
	int		gnl;
	int		index;

	head = new_tetrimino(NULL);
	temp = head;
	gnl = 1;
	index = 0;
	while (gnl > 0)
	{
		gnl = get_next_line(fd, &temp->tetrimino[index]);
		if (index == 3)
		{
			temp->next = new_tetrimino(head);
			temp = temp->next;
			gnl = get_next_line(fd, &temp->tetrimino[index]);
			index = 0;
		}
		else
			index++;
	}
	check_errors(head, gnl);
}

/* Opens the file given as an argument on the command line.
** Sends the file descriptor forward.
** Closes the file after the solving is done.
** In case of an error, the program exits with error code 1.
*/

void handle_fd(char *file)
{
    int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("error couldn't open file: ");
		ft_putendl(file);
		exit (2);
	}
	copy_tetriminos(fd);
	if (close(fd) == -1)
	{
		ft_putstr("error couldn't close file: ");
		ft_putendl(file);
		exit (9);
	}
}
