/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_tetriminos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:44:34 by raho              #+#    #+#             */
/*   Updated: 2022/02/03 23:55:39 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/* Checks if the tetrimino can be moved up.
*/

static int	check_up(t_tlist *elem)
{
	int	counter;
	int	col;
	
	counter = 0;
	col = 0;
	while (elem->tetrimino[0][col] != '\0')
	{
		if (elem->tetrimino[0][col] == '.')
			counter++;
		col++;
	}
	if (counter == 4)
		return (1);
	return (0);
}

/* Moves the tetrimino up
*/

static void	move_up(t_tlist *elem)
{
	int	row;
	int	col;

	row = 0;
	while (elem->tetrimino[row + 1] != NULL)
	{
		col = 0;
		while (elem->tetrimino[row][col] != '\0')
		{
			elem->tetrimino[row][col] = elem->tetrimino[row + 1][col];
			col++;
		}
		row++;
	}
	col = 0;
	while (elem->tetrimino[row][col] != '\0')
	{
		elem->tetrimino[row][col] = '.';
		col++;
	}
}

/* Checks if the tetrimino can be moved left.
*/

static int	check_left(t_tlist *elem)
{
	int	counter;
	int	row;
	
	counter = 0;
	row = 0;
	while (elem->tetrimino[row] != NULL)
	{
		if (elem->tetrimino[row][0] == '.')
			counter++;
		row++;
	}
	if (counter == 4)
		return (1);
	return (0);
}

/* Moves the tetrimino to the left
*/

static void	move_left(t_tlist *elem)
{
	int	row;
	int	col;

	row = 0;
	while (elem->tetrimino[row] != NULL)
	{
		col = 0;
		while (elem->tetrimino[row][col + 1] != '\0')
		{
			elem->tetrimino[row][col] = elem->tetrimino[row][col + 1];
			col++;
		}
		elem->tetrimino[row][col] = '.';
		row++;
	}
}

/* Calls for functions that check and move the tetriminos up and left
** if the functions return true. Aim is to get the tetriminos to their top-left corners.
** After that the linked list is sent to solve the square.
*/

void	move_tetriminos(t_tlist *head)
{
	t_tlist	*temp;
	int	count;

	temp = head;
	count = 0;
	while (temp->next != NULL)
	{
		while (check_up(temp))
			move_up(temp);
		while (check_left(temp))
			move_left(temp);
		count++;
		temp = temp->next;
	}
	solve_square(head, count);
}
