#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int count_neighbors(char *board, int row, int col, int width, int height) {
	int count = 0;

	for (int r = row - 1; r <= row + 1; r++)
		for (int c = col - 1; c <= col + 1; c++)
			if ((r != row || c != col) && r >= 0 && r < height && c >= 0 && c < width)
				count += board[r * width + c];
	return count;
}

int main(int argc, char **argv) {
	if (argc != 4)
		return 1;

	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int iter = atoi(argv[3]);
	int size = width * height;

	char *board = calloc(size, 1);
	char *next = malloc(size);
	if (!board || !next) {
		free(board);
		free(next);
		return 1;
	}

	int row = 0, col = 0, draw = 0;
	char cmd;

	while (read(STDIN_FILENO, &cmd, 1) == 1) {
		if (cmd == 'w') {
			if (row > 0) row--;
		} else if (cmd == 's') {
			if (row < height - 1) row++;
		} else if (cmd == 'a') {
			if (col > 0) col--;
		} else if (cmd == 'd') {
			if (col < width - 1) col++;
		} else if (cmd == 'x') {
			draw = !draw;
		}
		if (draw)
			board[row * width + col] = 1;
	}

	for (int i = 0; i < iter; i++) {
		for (int r = 0; r < height; r++) {
			for (int c = 0; c < width; c++) {
				int neighbors = count_neighbors(board, r, c, width, height);
				int idx = r * width + c;
				next[idx] = neighbors == 3 || (board[idx] && neighbors == 2);
			}
		}
		char *temp = board;
		board = next;
		next = temp;
	}

	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++)
			putchar(board[r * width + c] ? 'O' : '.');
		putchar('\n');
	}
	free(board);
	free(next);
	return 0;
}
