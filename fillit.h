/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omistaja <omistaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:44:44 by raho              #+#    #+#             */
/*   Updated: 2022/01/26 09:19:34 by omistaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include "./libft/libft.h"

typedef struct s_tetrimino
{
	int					height;
	int					width;
	char			    **line;
	struct s_tetrimino	*next;
}					t_tetrimino;

int	get_next_line(const int fd, char **line);

void	fillit(char *str);

int  error_check(t_tetrimino *tetrimino, int gnl);

int is_tetrimino_valid(t_tetrimino *tetrimino);

#endif
