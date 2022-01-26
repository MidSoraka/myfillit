/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omistaja <omistaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 08:10:22 by omistaja          #+#    #+#             */
/*   Updated: 2022/01/26 10:37:58 by omistaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "stdio.h" //remove

static int  side_by_side(t_tetrimino *tetrimino, int row, int col)
{
    size_t found_width;
    size_t found_height;

    found_width = 0;
    found_height = 0;
    if (col != 0)
        if (tetrimino->line[row][(col - 1)] == '#')
            found_width++;
    if (row != 0)
        if (tetrimino->line[(row - 1)][col] == '#')
            found_height++;
    if (tetrimino->line[row][(col + 1)] == '#')
        found_width++;
    if (row != 3)
        if (tetrimino->line[(row + 1)][col] == '#')
            found_height++;
    tetrimino->width = found_width + tetrimino->width;
    tetrimino->height = found_height + tetrimino->height;
   // printf("\n\nheight is %d\n\n", tetrimino->height);
   //         printf("\n\nwidth is %d\n\n", tetrimino->width);
    return (found_width + found_height);
}

int is_tetrimino_valid(t_tetrimino *tetrimino)
{
    size_t  count;
    size_t  len;
    int     col;
    int     row;
    int     hasfound;

    row = 0;
    hasfound = 0;
    len = 0;
    count = 0;
    while (tetrimino->line[row])
    {
        col = 0;
        while (tetrimino->line[row][col])
        {
            if (tetrimino->line[row][col++] == '#')
            {
                count++;
                hasfound = side_by_side(tetrimino, row, col - 1) + hasfound;
            }
            else if (tetrimino->line[row][col - 1] != '.')
                return (0);
            len++;
        }
        row++;
    }
    if (hasfound >= 6 && len == 16 && count == 4)
        return (1);
    return (0);
}

int  error_check(t_tetrimino *tetrimino, int gnl)
{
    while (tetrimino->next)
    {
        tetrimino->width = 0;
        tetrimino->height = 0;
        if (gnl == -2)
        {
            ft_putendl("Error tetrimino not a valid size.");
            return (0);
        }
        if (is_tetrimino_valid(tetrimino) == 0)
        {
            ft_putendl("Error tetrimino not valid.");
            return (0);
        }
        if (tetrimino->width == 4 && tetrimino->height == 4)
        {
            tetrimino->width = 2;
            tetrimino->height = 2;
        }
        if (tetrimino->width == 0)
            tetrimino->width = 1;
        if (tetrimino->height == 0)
            tetrimino->height = 1;
        if (tetrimino->width >= 4)
            if(tetrimino->width-- == 6)
                tetrimino->width--;
        if (tetrimino->height >= 4)
            if(tetrimino->height-- == 6)
                tetrimino->height--;
        tetrimino = tetrimino->next;
    }
    return (1);
}

/*

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

*/