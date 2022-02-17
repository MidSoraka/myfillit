/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raho <raho@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:37:19 by raho              #+#    #+#             */
/*   Updated: 2022/02/11 12:54:08 by raho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/* Checks that a single filename was given as an argument on the command line
** and sends the filename forward. If the check fails, the program quits and
** gives a short instruction on how to use the program.
*/

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		ft_putendl("usage: ./fillit tetrimino_file");
		return (1);
	}
	else
		handle_fd(argv[1]);
	return (0);
}
