#include "life.h"
#include <stdio.h>

int init_game(t_game *g, char *argv[])
{
	g->width = atoi(argv[1]);
	g->height = atoi(argv[2]);
	g->iterations = atoi(argv[3]);
	g->i = 0;
	g->j = 0;
	g->draw = 0;
	g->board = malloc(g->height * sizeof(char *));
	if (!g->board) return -1;
	for (int i = 0; i < g->height; i++)
	{
		g->board[i] = malloc(g->width);
		if (!g->board[i]) { free_board(g); return -1; }
		for (int j = 0; j < g->width; j++) g->board[i][j] = ' ';
	}
	return 0;
}

void fill_board(t_game *g)
{
	char c;
	while (read(STDIN_FILENO, &c, 1) == 1)
	{
		int moved = 1;
		if (c == 'w') { if (g->i > 0) g->i--; }
		else if (c == 's') { if (g->i < g->height - 1) g->i++; }
		else if (c == 'a') { if (g->j > 0) g->j--; }
		else if (c == 'd') { if (g->j < g->width - 1) g->j++; }
		else if (c == 'x') { g->draw = !g->draw; }
		else moved = 0;

		if (g->draw && moved)
			if (g->i >= 0 && g->i < g->height && g->j >= 0 && g->j < g->width)
				g->board[g->i][g->j] = 'O';
	}
}

static int count_neighbors(t_game *g, int i, int j)
{
	int n = 0;
	for (int di = -1; di <= 1; di++)
		for (int dj = -1; dj <= 1; dj++)
		{
			if (di == 0 && dj == 0) continue;
			int ni = i + di, nj = j + dj;
			if (ni >= 0 && nj >= 0 && ni < g->height && nj < g->width)
				if (g->board[ni][nj] == 'O') n++;
		}
	return n;
}

int play(t_game *g)
{
	char **tmp = malloc(g->height * sizeof(char *));
	if (!tmp) return -1;
	for (int i = 0; i < g->height; i++)
	{
		tmp[i] = malloc(g->width);
		if (!tmp[i]) { for (int k = 0; k < i; k++) free(tmp[k]); free(tmp); return -1; }
		for (int j = 0; j < g->width; j++)
		{
			int n = count_neighbors(g, i, j);
			if (g->board[i][j] == 'O') tmp[i][j] = (n == 2 || n == 3) ? 'O' : ' ';
			else tmp[i][j] = (n == 3) ? 'O' : ' ';
		}
	}
	free_board(g);
	g->board = tmp;
	return 0;
}

void print_board(t_game *g)
{
	for (int i = 0; i < g->height; i++)
	{
		for (int j = 0; j < g->width; j++) putchar(g->board[i][j]);
		putchar('\n');
	}
}

void free_board(t_game *g)
{
	if (g->board)
	{
		for (int i = 0; i < g->height; i++) free(g->board[i]);
		free(g->board);
	}
}

int main(int argc, char *argv[])
{
	if (argc != 4) return 1;
	t_game g;
	if (init_game(&g, argv) == -1) return 1;
	fill_board(&g);
	for (int i = 0; i < g.iterations; i++)
		if (play(&g) == -1) { free_board(&g); return 1; }
	print_board(&g);
	free_board(&g);
	return 0;
}
