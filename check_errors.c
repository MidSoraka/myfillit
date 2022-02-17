/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:44:32 by raho              #+#    #+#             */
/*   Updated: 2022/02/11 10:48:30 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	side_by_side(t_tlist *elem, int row, int col)
{
	int	count;

	count = 0;
	if (col != 0)
		if (elem->tetrimino[row][col - 1] == '#')
			count++;
	if (row != 0)
		if (elem->tetrimino[row - 1][col] == '#')
			count++;
	if (elem->tetrimino[row][col + 1] == '#')
		count++;
	if (row != 3)
		if (elem->tetrimino[row + 1][col] == '#')
			count++;
	return (count);
}

static int	assign_value(t_tlist *elem, int row, int col, int hasfound)
{
	int	len;
	int	index;

	len = 0;
	index = 0;
	while (elem->tetrimino[row] != NULL)
	{
		col = 0;
		while (elem->tetrimino[row][col] != '\0')
		{
			if (elem->tetrimino[row][col++] == '#')
			{
				hasfound = side_by_side(elem, row, col - 1) + hasfound;
				elem->row[index] = row;
				elem->col[index++] = col - 1;
			}
			else if (elem->tetrimino[row][col - 1] != '.')
				return (-1);
			len++;
		}
		row++;
	}
	if (hasfound >= 6 && len == 16 && index == 4)
		return (0);
	return (-1);
}

static int	validate_tetriminos(t_tlist *elem, int hasfound)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	elem->row[4] = '\0';
	elem->col[4] = '\0';
	return (assign_value(elem, row, col, hasfound));
}

/* Goes through the struct's tetrimino and turns all '#'s to letters and
** saves the letter to its variable 'int letter'.
*/

static void	turn_alpha(t_tlist *head)
{
	int		letter;
	int		row;
	int		col;
	t_tlist	*temp;

	letter = 65;
	temp = head;
	while (temp != NULL)
	{
		row = 0;
		while (temp->tetrimino[row] != NULL)
		{
			col = 0;
			while (temp->tetrimino[row][col] != '\0')
			{	
				if (temp->tetrimino[row][col] == '#')
					temp->tetrimino[row][col] = (char)letter;
				col++;
			}	
			row++;
		}
		temp->letter = letter;
		letter++;
		temp = temp->next;
	}
}

void	check_errors(t_tlist *head, int gnl)
{
	t_tlist	*temp;

	temp = head;
	if (gnl < 0)
	{
		ft_putendl("error");
		free_list(head);
		exit (5);
	}
	while (temp != NULL)
	{
		if (validate_tetriminos(temp, 0) == -1)
		{
			ft_putendl("error");
			free_list(head);
			exit (6);
		}
		temp->height = (temp->row[3] - temp->row[0]) + 1;
		temp = temp->next;
	}
	turn_alpha(head);
	move_tetriminos(head);
}
