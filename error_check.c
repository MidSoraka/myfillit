/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omistaja <omistaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 08:10:22 by omistaja          #+#    #+#             */
/*   Updated: 2022/01/25 08:44:49 by omistaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "stdio.h" //remove

static int  side_by_side(char **line)
{
    int     col;
    int     row;
    int     hasfound;

    row = 0;
    hasfound = 0;
    while (line[row])
    {
        col = 0;
        while (line[row][col])
        {
            if (line[row][col] == '#')
            {
                if (col != 0)
                    if (line[row][(col - 1)] == '#')
                        hasfound++;
                if (row != 0)
                    if (line[(row - 1)][col] == '#')
                        hasfound++;
                if (line[row][(col + 1)] == '#')
                    hasfound++;
                if (row != 3)
                    if (line[(row + 1)][col] == '#')
                        hasfound++;
            }
            else if (line[row][col] != '.')
                return (0);
            col++;
        }
        row++;
    }
    if (hasfound >= 6)
        return (1);
    return (0);
}

int is_tetrimino_valid(char **line)
{
    size_t  index;
    size_t  len;
    size_t  isvalid;
    char    *tab;
    int     count;

    index = 0;
    len = 0;
    isvalid = 0;
    count = 0;
    while (index < 4)
    {
        len = ft_strlen(line[index]) + len;
        tab = ft_strchr(line[index], '#');
        while (tab)
        {
            if (tab)
                count++;
            tab = ft_strchr(tab + 1, '#');
        }
        index++;
    }
    isvalid = side_by_side(line);
//    printf("\n\nvalid is %lu\n\n", isvalid);
//    printf("\n\nlen is %lu\n\n", len);
//    printf("\n\nindex is %lu\n\n", index);
//    printf("\n\ncount is %d\n\n", count);
    if (isvalid == 1 && len == 16 && index == 4 && count == 4)
    {
//        ft_putendl("\n\n_____TRUE_____\n\n");
        return (1);
    }
    else
    {
//        ft_putendl("\n\n_____FALSE_____\n\n");
        return (0);
    }
}

int  error_check(t_tetrimino *tetrimino, int gnl)
{
    while (tetrimino->next)
    {   
        if (gnl == -2)
        {
            ft_putendl("Error tetrimino not a valid size.");
            return (0);
        }
        if (is_tetrimino_valid(tetrimino->line) == 0)
        {
            ft_putendl("Error tetrimino not valid.");
            return (0);
        }
        tetrimino = tetrimino->next;
    }
    return (1);
}
