#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int count_neighbors(char *board, int row, int col, int width, int height) {
	static const int d[] = {-1,-1, -1,0, -1,1, 0,-1, 0,1, 1,-1, 1,0, 1,1};
	int count = 0;
	for (int i = 0; i < 16; i += 2) {
		int neighbor_row = row + d[i];
		int neighbor_col = col + d[i + 1];
		count += neighbor_row >= 0 && neighbor_row < height
			&& neighbor_col >= 0 && neighbor_col < width
			&& board[neighbor_row * width + neighbor_col] == 'O';
	}
	return count;
}

int main(int argc, char **argv) {
	if (argc != 4)
		return 1;

	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int iter = atoi(argv[3]);
	int size = width * height;

	char *board = malloc(size);
	char *next = malloc(size);
	if (!board || !next)
		return 1;

	for (int i = 0; i < size; i++)
		board[i] = ' ';

	int row = 0, col = 0, draw = 0;
	char cmd;

	while (read(STDIN_FILENO, &cmd, 1) == 1) {
		int moved = 1;
		if (cmd == 'w') {
			if (row > 0)
				row--;
		} else if (cmd == 's') {
			if (row < height - 1)
				row++;
		} else if (cmd == 'a') {
			if (col > 0)
				col--;
		} else if (cmd == 'd') {
			if (col < width - 1)
				col++;
		} else if (cmd == 'x') {
			draw = !draw;
		} else {
			moved = 0;
		}

		if (draw && moved)
			board[row * width + col] = 'O';
	}

	for (int iteration = 0; iteration < iter; iteration++) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				int neighbors = count_neighbors(board, y, x, width, height);
				int idx = y * width + x;
				if (board[idx] == 'O') {
					next[idx] = (neighbors == 2 || neighbors == 3) ? 'O' : ' ';
				} else {
					next[idx] = (neighbors == 3) ? 'O' : ' ';
				}
			}
		}
		char *temp = board;
		board = next;
		next = temp;
	}

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			putchar(board[y * width + x]);
		putchar('\n');

	free(board);
	free(next);
	return 0;
}
