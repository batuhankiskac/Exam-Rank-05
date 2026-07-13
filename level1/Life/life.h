#ifndef LIFE_H
#define LIFE_H

#include <stdlib.h>
#include <unistd.h>

typedef struct s_game
{
	int width;
	int height;
	int iterations;
	int i;
	int j;
	int draw;
	char **board;
} t_game;

int init_game(t_game *g, char *argv[]);
void fill_board(t_game *g);
int play(t_game *g);
void print_board(t_game *g);
void free_board(t_game *g);

#endif
