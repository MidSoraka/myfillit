/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:44:34 by raho              #+#    #+#             */
/*   Updated: 2022/02/03 22:43:52 by raho             ###   ########.fr       */
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
			while (index < 5)
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
