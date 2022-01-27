/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omistaja <omistaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:38:42 by omistaja          #+#    #+#             */
/*   Updated: 2022/01/27 13:23:15 by omistaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fillit.h"
#include "stdio.h" // rm

static int find_piece(t_tetrimino *tetrimino, int row, int col)
{
    while (tetrimino->line[row][col] != '#' && tetrimino->line[row][col])
        col++;
    return (col);
}

static int add_to_board(t_tetrimino *tetrimino, char ***board, int row, int col, char alphabet)
{
    int t_row;
    int t_col;
    int frow;
    int fcol;
    int count;

    count = 0; // checks how many free spaces for tetrimino... Has to be 4 free spaces or it wont place it
    t_row = 0;
    frow = 0;
    fcol = 0;
    while (tetrimino->line[t_row]) //goes through the entire tetrimino inside struct and sees if there is space for a tetrimino
    {
        t_col = 0;
        while (tetrimino->line[t_row][t_col])
        {
            if (tetrimino->line[t_row][t_col] == '#') // finds pieces from struct tetrimino
            {
                //printf("\n\ntetri t_row is %d\n\n", t_row);
                //printf("\n\ntetri t_col is %d\n\n", t_col);
                //printf("\n\nboard row is %d\n\n", row);
                //printf("\n\nboard col is %d\n\n", col);
                if (frow == 0 && fcol == 0) // finds the first # in struct tetrmino->line
                {
                    frow = t_row;
                    fcol = t_col;
                    if (tetrimino->line[0][0] == '#') // edge case if tetriminos first character is a #
                    {
                        frow = 0;
                        fcol = 0;
                    }
                }
                if (((*board)[row + t_row - frow][col + t_col - fcol]) == '.') // counts if there are enough spaces to place the entire tetrimino
                    count++; //if count == 4 means there is enough space to place tetrimino
            }
            t_col++;
        }
        t_row++;
    }
    t_row = 0; //reset
    frow = 0; //reset
    fcol = 0; //reset
    if (count == 4) // same function as the above except this one places the tetrimino instead of checking if there is enough space.
    {
        while (tetrimino->line[t_row])
        {
            t_col = 0;
            while (tetrimino->line[t_row][t_col])
            {
                if (tetrimino->line[t_row][t_col] == '#')
                {
                    //printf("\n\ntetri t_row is %d\n\n", t_row);
                    //printf("\n\ntetri t_col is %d\n\n", t_col);
                    //printf("\n\nboard row is %d\n\n", row);
                    //printf("\n\nboard col is %d\n\n", col);
                    if (frow == 0 && fcol == 0)
                    {
                        frow = t_row;
                        fcol = t_col;
                        if (tetrimino->line[0][0] == '#')
                        {
                            frow = 0;
                            fcol = 0;
                        }
                    }
                    (*board)[row + t_row - frow][col + t_col - fcol] = alphabet; //places the tetrimino block x 4 times
                }
                t_col++;
            }
            t_row++;
        }
        return (1); // returns true means tetrimino has been placed
    }
    else
        return (0); // returns false means tetrimino has notbeen placed and needs to keep looking for a new spot.
}

void solve(t_tetrimino *tetrimino, int count)
{
    char **board;
    char alphabet = 'A';
    int row;
    int col;

    board = (char **)malloc(sizeof(char *) * 10); // malloc space for rows
    if (board == NULL)
            printf("no space 1\n");
    board[9] = NULL; // 10 row is NULL, index starts from 0
    row = 0;
    while (row <= 8) //mallocs space for rows
    {
        board[row] = ft_strnew(10);
        ft_bzero(board[row], 10); //sets all of the rows to '\0'
        ft_memset(board[row], '.', 9); //sets all of the rows to '.'
        row++;
    }
    row = 0;
    while (board[row]) // goes through the entire board
    {
        col = 0;
        while (board[row][col])
        {
            if (board[row][col] == '.' && tetrimino->next) //if board has . means empty spot and tries to place tetrimino
            {
                if (tetrimino->next && add_to_board(tetrimino, &board, row, col, alphabet) == 1) // if add_to_board returns 1 it means it has succesfully placed tetrimino
                {
                    tetrimino = tetrimino->next; // goes to next piece after add_to_board has returned 1
                    alphabet++; // next letter starts a 'A'
                }
            }
            col++;
        }
        row++;
    }
    row = 0;
    while (row < 9) // prints the whole board
        printf("%s\n", board[row++]);
}
