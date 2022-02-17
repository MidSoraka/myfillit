/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_square.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:42:52 by vlaine            #+#    #+#             */
/*   Updated: 2022/02/17 19:42:52 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/* The size of the array is 27x27. Assigns dots to represent the smallest
** calculated size square with given tetriminos. 
** In case of an error while allocating memory, the function
** calls to free all dynamically allocated memories and exits.
*/

static char	**new_square(t_tlist *head, int smallest_size)
{
	int		index;
	char	**square;

	index = 0;
	square = (char **)malloc(sizeof(char *) * 27);
	if (square == NULL)
	{
		free_list(head);
		exit (0);
	}
	while (index < 26)
	{
		square[index] = ft_memalloc(27);
		if (square[index] == NULL)
		{
			free_all(head, square);
			exit (0);
		}
		if (index < smallest_size)
			ft_memset(square[index], '.', (unsigned long)smallest_size);
		index++;
	}
	square[index] = 0;
	return (square);
}

/* Every time the function is called, it increases the width and the
** height of the dot square inside that's inside the 2D array grid.
*/

static void	enlargen_square(char **square, int smallest_size)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (row < smallest_size)
	{
		square[row][smallest_size] = '.';
		row++;
	}
	while (col <= smallest_size)
	{
		square[row][col] = '.';
		col++;
	}
}

/* Creates the square where to put all the tetrimino pieces.
** Calls the solving function 'fillit' in a while loop and every time that
** the function can't solve the square, it enlarges the square of dots.
** Prints the solved square to the standard output
** and frees all the dynamically allocated memory.
*/

void	solve_square(t_tlist *head, int count)
{
	int		index;
	char	**square;
	int		smallest_size;

	index = 0;
	count = count * 4;
	smallest_size = ft_roundup(ft_sqrtf(count));
	square = new_square(head, smallest_size);
	while (fillit(square, head, smallest_size) == 0)
	{
		enlargen_square(square, smallest_size);
		smallest_size++;
	}
	while (square[index] != NULL && square[index][0] != '\0')
	{
		ft_putendl(square[index]);
		index++;
	}
	free_all(head, square);
}
