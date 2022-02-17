/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_square.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:39:15 by raho              #+#    #+#             */
/*   Updated: 2022/02/17 17:12:03 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/* Removes a tetrimino piece using the help of 'int letter' that was saved in
** the structs when turning the '#'s into letters.
*/

static void	remove_piece(char **square, t_tlist *elem)
{
	int	row;
	int	col;
	int	frow;
	int	fcol;
	int	index;

	row = elem->row[4];
	col = elem->col[4];
	index = 0;
	frow = elem->row[0];
	fcol = elem->col[0];
	while (index < 4)
	{
		square[row + elem->row[index] - frow] \
				[col + elem->col[index] - fcol] = '.';
		index++;
	}
}

/* Checks and places tetrimino piece to the given coordinate if possible.
** Returns true if succesful and false if it not.
*/

static int	place(char **square, t_tlist *elem, int frow, int fcol)
{
	int	index;
	int	row;
	int	col;

	index = 0;
	row = elem->row[4];
	col = elem->col[4];
	while (index < 4)
	{
		square[row + elem->row[index] - frow] \
				[col + elem->col[index] - fcol] = (char)elem->letter;
		index++;
	}
	return (1);
}

static int	check(char **square, t_tlist *elem, int row, int col)
{
	int	index;
	int	frow;
	int	fcol;

	index = 0;
	frow = elem->row[0];
	fcol = elem->col[0];
	elem->row[4] = row;
	elem->col[4] = col;
	while (index < 4)
	{
		if ((col + elem->col[index] - fcol >= 0) && \
			(square[row + elem->row[index] - frow] \
					[col + elem->col[index] - fcol] == '.'))
		{
			index++;
			if (index == 4)
				return (place(square, elem, frow, fcol));
		}
		else
			return (0);
	}
	return (0);
}

/* Goes through the square to check if the next tetrimino can be placed in it.
** Checks every coordinate one by one with function 'place_tetrimino'.
** If tetrimino was placed and there are more tetriminos left in the list,
** the function calls for itself with the next tetrimino as the new head of the
** list. If placing isn't possible at some point, the tetrimino is removed and
** the checking continues. If the function reaches the end of the square
** without being able to place all the tetriminos, it returns 0 so that the
** previous function knows to increase the square size for the next try.
*/

static int	fillit_helper( char **square, t_tlist *head, int smallest_size)
{
	if (head->next != NULL)
	{
		if (fillit(square, head->next, smallest_size))
			return (1);
		else
		{
			remove_piece(square, head);
			return (0);
		}
	}
	else
		return (1);
}

int	fillit(char **square, t_tlist *head, int smallest_size)
{
	int	col;
	int	row;

	row = 0;
	while (square[row] != NULL)
	{
		col = 0;
		if (row + head->height > smallest_size)
			return (0);
		else
		{
			while (square[row][col] != '\0')
			{
				if (square[row][col] == '.' && check(square, head, row, col))
				{
					if (fillit_helper(square, head, smallest_size))
						return (1);
				}
				col++;
			}
		}
		row++;
	}
	return (0);
}
