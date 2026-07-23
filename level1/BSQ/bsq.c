#include <stdio.h>
#include <stdlib.h>

typedef struct s_elements {
	int n_lines;
	char empty;
	char obstacle;
	char full;
} t_elements;

typedef struct s_map {
	char **grid;
	int width;
	int height;
} t_map;

typedef struct s_square {
	int size;
	int i;
	int j;
} t_square;

static void free_map(char **arr) {
	if (!arr)
		return;
	for (int i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
}

static int cleanup_fail(char *line, char **grid) {
	free(line);
	free_map(grid);
	return -1;
}

static int load_elements(FILE *file, t_elements *e) {
	if (fscanf(file, "%d %c %c %c", &e->n_lines,
			&e->empty, &e->obstacle, &e->full) != 4)
		return -1;
	if (e->n_lines <= 0)
		return -1;
	if (e->empty < 32 || e->empty > 126
		|| e->obstacle < 32 || e->obstacle > 126
		|| e->full < 32 || e->full > 126)
		return -1;
	if (e->empty == e->obstacle || e->empty == e->full
		|| e->obstacle == e->full)
		return -1;
	return 0;
}

static int load_map(FILE *file, t_map *map, t_elements *e) {
	map->height = e->n_lines;
	map->grid = calloc((size_t)map->height + 1, sizeof(char *));
	if (!map->grid)
		return -1;

	char *line = NULL;
	size_t len = 0;
	int r = getline(&line, &len, file);
	if (r < 1 || line[r - 1] != '\n')
		return cleanup_fail(line, map->grid);

	for (int i = 0; i < map->height; i++) {
		r = getline(&line, &len, file);
		if (r <= 1 || line[r - 1] != '\n')
			return cleanup_fail(line, map->grid);
		r--;

		if (i == 0)
			map->width = r;
		else if (map->width != r)
			return cleanup_fail(line, map->grid);

		map->grid[i] = malloc(r + 1);
		if (!map->grid[i])
			return cleanup_fail(line, map->grid);
		int k;
		for (k = 0; k < r; k++) {
			if (line[k] != e->empty && line[k] != e->obstacle)
				break;
			map->grid[i][k] = line[k];
		}
		if (k < r) {
			map->grid[i][k] = '\0';
			return cleanup_fail(line, map->grid);
		}
		map->grid[i][r] = '\0';
	}
	if (getline(&line, &len, file) != -1)
		return cleanup_fail(line, map->grid);
	free(line);
	return 0;
}

static int find_square(t_map *map, t_square *sq, t_elements *e) {
	int w = map->width;
	int *m = calloc((size_t)map->height * w, sizeof(int));
	if (!m)
		return -1;
	for (int i = 0; i < map->height; i++)
		for (int j = 0; j < w; j++) {
			if (map->grid[i][j] == e->obstacle)
				m[i*w+j] = 0;
			else if (i == 0 || j == 0)
				m[i*w+j] = 1;
			else {
				int min = m[(i-1)*w+j];
				if (m[(i-1)*w+(j-1)] < min)
					min = m[(i-1)*w+(j-1)];
				if (m[i*w+(j-1)] < min)
					min = m[i*w+(j-1)];
				m[i*w+j] = min + 1;
			}
			if (m[i*w+j] > sq->size) {
				sq->size = m[i*w+j];
				sq->i = i - m[i*w+j] + 1;
				sq->j = j - m[i*w+j] + 1;
			}
		}
	free(m);
	return 0;
}

static void print_map(t_map *map, t_square *sq, t_elements *e) {
	for (int i = sq->i; i < sq->i + sq->size; i++)
		for (int j = sq->j; j < sq->j + sq->size; j++)
			map->grid[i][j] = e->full;
	for (int i = 0; i < map->height; i++)
		fprintf(stdout, "%s\n", map->grid[i]);
}

int execute_bsq(FILE *file) {
	t_elements e;
	if (load_elements(file, &e) == -1)
		return -1;

	t_map map;
	if (load_map(file, &map, &e) == -1)
		return -1;

	t_square sq = {0, 0, 0};
	if (find_square(&map, &sq, &e) == -1) {
		free_map(map.grid);
		return -1;
	}
	print_map(&map, &sq, &e);
	free_map(map.grid);
	return 0;
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		if (execute_bsq(stdin) == -1)
			fprintf(stderr, "map error\n");
	} else {
		for (int i = 1; i < argc; i++) {
			FILE *file = fopen(argv[i], "r");
			if (!file || execute_bsq(file) == -1)
				fprintf(stderr, "map error\n");
			if (file)
				fclose(file);
			if (i < argc - 1)
				fprintf(stdout, "\n");
		}
	}
	return 0;
}
