#include "bsq.h"

static void free_map(char **arr) {
	if (!arr)
		return;
	for (int i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
}

static int load_elements(FILE *file, t_elements *e) {
	if (fscanf(file, "%d %c %c %c", &e->n_lines, &e->empty, &e->obstacle, &e->full) != 4)
		return -1;

	if (e->n_lines <= 0)
		return -1;
	if (e->empty == e->obstacle || e->empty == e->full || e->obstacle == e->full)
		return -1;
	if (e->empty < 32 || e->empty > 126)
		return -1;
	if (e->obstacle < 32 || e->obstacle > 126)
		return -1;
	if (e->full < 32 || e->full > 126)
		return -1;
	return 0;
}

static int valid_chars(char **grid, char empty, char obstacle) {
	for (int i = 0; grid[i]; i++) {
		for (int j = 0; grid[i][j]; j++) {
			if (grid[i][j] != empty && grid[i][j] != obstacle)
				return -1;
		}
	}
	return 0;
}

static int load_map(FILE *file, t_map *map, t_elements *e) {
	map->height = e->n_lines;
	map->grid = calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return -1;

	char *line = NULL;
	size_t len = 0;
	if (getline(&line, &len, file) == -1) {
		free(line);
		free_map(map->grid);
		return -1;
	}

	for (int i = 0; i < map->height; i++) {
		int r = getline(&line, &len, file);
		if (r == -1 || line[r - 1] != '\n') {
			free(line);
			free_map(map->grid);
			return -1;
		}

		r--;

		if (i == 0)
			map->width = r;
		else if (map->width != r) {
			free(line);
			free_map(map->grid);
			return -1;
		}

		map->grid[i] = malloc(r + 1);
		if (!map->grid[i]) {
			free(line);
			free_map(map->grid);
			return -1;
		}
		for (int k = 0; k < r; k++) map->grid[i][k] = line[k];
		map->grid[i][r] = '\0';
	}
	free(line);

	if (valid_chars(map->grid, e->empty, e->obstacle) == -1) {
		free_map(map->grid);
		return -1;
	}
	return 0;
}

static void find_square(t_map *map, t_square *sq, t_elements *e) {
	int m[map->height][map->width];
	for (int i = 0; i < map->height; i++)
		for (int j = 0; j < map->width; j++)
		{
			if (map->grid[i][j] == e->obstacle) m[i][j] = 0;
			else if (i == 0 || j == 0) m[i][j] = 1;
			else
			{
				int min = m[i-1][j];
				if (m[i-1][j-1] < min) min = m[i-1][j-1];
				if (m[i][j-1] < min) min = m[i][j-1];
				m[i][j] = min + 1;
			}
			if (m[i][j] > sq->size)
			{
				sq->size = m[i][j];
				sq->i = i - m[i][j] + 1;
				sq->j = j - m[i][j] + 1;
			}
		}
}

static void print_map(t_map *map, t_square *sq, t_elements *e) {
	for (int i = sq->i; i < sq->i + sq->size; i++)
		for (int j = sq->j; j < sq->j + sq->size; j++)
			map->grid[i][j] = e->full;
	for (int i = 0; i < map->height; i++) {
		fputs(map->grid[i], stdout);
		fputs("\n", stdout);
	}
}

int execute_bsq(FILE *file) {
	t_elements e;
	if (load_elements(file, &e) == -1)
		return -1;

	t_map map;
	if (load_map(file, &map, &e) == -1)
		return -1;

	t_square sq = {0, 0, 0};
	find_square(&map, &sq, &e);
	print_map(&map, &sq, &e);
	free_map(map.grid);
	return 0;
}

int convert_file_pointer(char *name) {
	FILE *file = fopen(name, "r");
	if (!file)
		return -1;
	int ret = execute_bsq(file);
	fclose(file);
	return ret;
}
