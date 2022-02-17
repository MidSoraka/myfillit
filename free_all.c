/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:45:16 by vlaine            #+#    #+#             */
/*   Updated: 2022/02/17 19:45:16 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/* Frees the tetrimino inside the struct, then the struct itself and
** continues to do the same to all structs in the linked list.
*/

void	free_list(t_tlist *head)
{
	t_tlist	*temp;
	t_tlist	*hold;
	int		index;

	temp = head;
	while (temp != NULL)
	{
		hold = temp->next;
		if (temp->tetrimino != NULL)
		{
			index = 0;
			while (temp->tetrimino[index])
			{
				free(temp->tetrimino[index]);
				index++;
			}
			free(temp->tetrimino);
		}
		free(temp);
		temp = hold;
	}
}

/* Frees the square.
*/

void	free_square(char **square)
{
	int	index;

	index = 0;
	while (index < 27)
	{
		free(square[index]);
		index++;
	}
	free(square);
}

/* Frees both the square and the linked list.
*/

void	free_all(t_tlist *head, char **square)
{
	free_list(head);
	free_square(square);
}
