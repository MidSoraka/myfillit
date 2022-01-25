/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omistaja <omistaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:08:57 by omistaja          #+#    #+#             */
/*   Updated: 2022/01/25 08:49:01 by omistaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"
#include "fillit.h"

static t_tetrimino	*ft_lstnewmal(void)
{
	t_tetrimino	*list;

	list = malloc(sizeof(t_tetrimino));
	if (list == NULL)
		return (NULL);
    list->line = (char **)malloc(sizeof(char *) * 6);
    list->line[4] = NULL; // not needed, but might be depending if tetrimino->line is used in a while condition
	list->next = NULL;
	return (list);
}

static void	print_tetriminos(t_tetrimino *tetrimino)
{
	size_t index;

	while (tetrimino->next)
	{
        index = 0;
        is_tetrimino_valid(tetrimino->line);
		while (tetrimino->line[index])
		{
			ft_putendl(tetrimino->line[index]);
			index++;
		}
        tetrimino = tetrimino->next;
        if (tetrimino->next)
		    ft_putchar('\n');
	}
}

static void copy(int fd)
{
    t_tetrimino *tetrimino;
    t_tetrimino *head;
    int gnl;
    int index;

    gnl = 1;
    index = 0;
    tetrimino = ft_lstnewmal(); // if index is 0 malloc space for next list and set a pointer when index is at 3
    head = tetrimino;
    while (gnl > 0)
    {
        gnl = get_next_line(fd, &tetrimino->line[index]);
        if (index == 3)
        {
            index = 0;
            tetrimino->next = ft_lstnewmal();
            tetrimino = tetrimino->next;
            gnl = get_next_line(fd, &(tetrimino->line[index]));
        }
        else if (!tetrimino->line[index]) // doesnt work atm
            gnl = -2;
        else
            index++;
    }
    tetrimino = head;
    if (error_check(tetrimino, gnl) == 0)
        ft_putendl("Error found. (Ending program...)");
    else
    {
        tetrimino = head;
        print_tetriminos(tetrimino);
    }
//    print_tetriminos(tetrimino);
}

void fillit(char *filename)
{
    int	fd;
	int	index;

	index = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl("error");
		return ;
	}
	copy(fd);
	if (close(fd) == -1)
	{
		ft_putendl("error");
		return ;
	}
}

/*
int main(int argc, char **argv)
{
    t_tetrimino *tetrimino;
    t_tetrimino *head;
    char **line;
    int res;
    int gnl;
    int index;
    int count;

    count = 0;
    res = open(argv[1], O_RDONLY);
    gnl = 1;
    index = 0;
    tetrimino = ft_lstnewmal(); // if index is 0 malloc space for next list and set a pointer when index is at 3
    head = ft_lstnewmal();
    tetrimino->line = (char **)malloc(sizeof(char *) * 6);
    tetrimino->line[4] = NULL;
    head = tetrimino;
    while (gnl > 0)
    {
        gnl = get_next_line(res, &tetrimino->line[index]);
       // printf("\n\ngnl is %d\n\n", gnl);
       // printf("\n\nline is %s\n\n", tetrimino->line[index]);
        //printf("\n\n%s\n\n", head->line[0]);
        if (index == 3)
        {
            index = 0;
            strchr_count(tetrimino->line);
           // ft_lstaddmal(&tetrimino, ft_lstnewmal());
            tetrimino->next = ft_lstnewmal();
            tetrimino = tetrimino->next;
            tetrimino->line = (char **)malloc(sizeof(char *) * 6);
            tetrimino->line[4] = NULL;
            index = 0;
            gnl = get_next_line(res, &(tetrimino->line[index]));
        }
        else
            index++;
    }
    //printf("\n\n%s\n\n", head->line[0]);
    
    while (head->next)
    {
        index = 0;
        printf("\n\n_______________________________\n\n");
        strchr_count(head->line);
        while (index < 4)
        {
            printf("%s      strlen is %lu\n", head->line[index], ft_strlen(head->line[index]));
            index++;
        }
        head = head->next;
    }
    return (1);
}

int main(int argc, char **argv)
{
    t_tetrimino *tetrimino;
    char **line;
    int res;
    int gnl;
    int index;
    int count;

    count = 0;
    res = open(argv[1], O_RDONLY);
    gnl = 1;
    index = 0;
    tetrimino = malloc(sizeof(t_tetrimino)); // if index is 0 malloc space for next list and set a pointer when index is at 3
    tetrimino->line = (char **)malloc(sizeof(char *) * 6);
    tetrimino->line[4] = NULL;
    while (gnl > 0)
    {
        gnl = get_next_line(res, &tetrimino->line[index]);
       // printf("\n\ngnl is %d\n\n", gnl);
     //   printf("\n\nline is %s\n\n", tetrimino->line[index]);
        if (index == 3)
        {
            index = 0;
            strchr_count(tetrimino->line);
            while (index != 4)
            {
                printf("%s      strlen is %lu\n", tetrimino->line[index], ft_strlen(tetrimino->line[index]));
                index++;
            }
            index = 0;
            gnl = get_next_line(res, &(tetrimino->line[index]));
        }
        else
            index++;
    }
    return (1);
}*/