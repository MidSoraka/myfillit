/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:45:30 by vlaine            #+#    #+#             */
/*   Updated: 2022/02/17 19:45:30 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include "./libft/libft.h"

typedef struct s_tlist
{
	int					letter;
	char				**tetrimino;
	int					row[5];
	int					col[5];
	int					width;
	int					height;
	struct s_tlist		*next;
}	t_tlist;

void	handle_fd(char *file);
void	check_errors(t_tlist *head, int gnl);
void	move_tetriminos(t_tlist *head);
void	solve_square(t_tlist *head, int count);
void	free_list(t_tlist *head);
void	free_square(char **square);
void	free_all(t_tlist *head, char **square);
int		fillit(char **square, t_tlist *head, int smallest_size);

#endif
