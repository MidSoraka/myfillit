/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:44:32 by raho              #+#    #+#             */
/*   Updated: 2022/02/02 02:23:03 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	side_by_side(t_tlist *elem, int row, int col)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	if (col != 0)
		if (elem->tetrimino[row][col - 1] == '#')
			width++;
	if (row != 0)
		if (elem->tetrimino[row - 1][col] == '#')
			height++;
	if (elem->tetrimino[row][col + 1] == '#')
		width++;
	if (row != 3)
		if (elem->tetrimino[row + 1][col] == '#')
			height++;
	elem->width = width + elem->width;
    elem->height = height + elem->height;
	return (width + height);
}

static int	validate_tetriminos(t_tlist *elem, int hasfound, int count)
{
	int	len;
	int	row;
	int	col;
	int index; // can maybe use count instead

	index = 0;
	len = 0;
	row = 0;
	elem->row[4] = '\0';
	elem->col[4] = '\0';
	//printf("_______________________________________ %c\n", elem->letter);
	while (elem->tetrimino[row] != NULL)
	{
		col = 0;
		while (elem->tetrimino[row][col] != '\0')
		{
			if (elem->tetrimino[row][col++] == '#')
			{
				count++;
				hasfound = side_by_side(elem, row, col - 1) + hasfound;
				elem->row[index] = row;
				elem->col[index] = col - 1;
				//printf("Row %d\nCol %d\n", elem->row[index], elem->col[index]);
				index++;
			}
			else if (elem->tetrimino[row][col - 1] != '.')
				return (-1);
			len++;
		}
		row++;
	}
	if (hasfound >= 6 && len == 16 && count == 4)
		return (0);
	return (-1);
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
	while (temp->next != NULL)
	{
		row = 0;
		while (temp->tetrimino[row] != NULL)
		{
			col = 0;
			while (temp->tetrimino[row][col] != '\0')
			{	
				if (temp->tetrimino[row][col] == '#')
					temp->tetrimino[row][col] = letter;
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
	while (temp->next != NULL)
	{
		temp->width = 0;
		temp->height = 0;
		if (validate_tetriminos(temp, 0, 0) == -1)
		{
			ft_putendl("error");
			free_list(head);
			exit (6);
		}
		if (temp->width == 4 && temp->height == 4)
        {
            temp->width = 2;
            temp->height = 2;
        }
        if (temp->width == 0)
            temp->width = 1;
        if (temp->height == 0)
            temp->height = 1;
        if (temp->width >= 4)
            if(temp->width-- == 6)
                temp->width--;
        if (temp->height >= 4)
            if(temp->height-- == 6)
                temp->height--;
			printf("\nwidth is %d\nheight is %d\n", temp->width, temp->height);
		temp = temp->next;
	}
	turn_alpha(head);
	move_tetriminos(head);
}
