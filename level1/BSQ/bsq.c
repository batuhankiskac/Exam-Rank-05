#include <stdio.h>
#include <stdlib.h>

typedef struct s_elements {
	int num_lines;
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

static int load_elements(FILE *file, t_elements *e) {
	if (fscanf(file, "%d %c %c %c", &e->num_lines,
			&e->empty, &e->obstacle, &e->full) != 4)
		return 1;
	if (e->num_lines <= 0)
		return 1;
	if (e->empty < 32 || e->empty > 126
		|| e->obstacle < 32 || e->obstacle > 126
		|| e->full < 32 || e->full > 126)
		return 1;
	if (e->empty == e->obstacle || e->empty == e->full
		|| e->obstacle == e->full)
		return 1;
	return 0;
}

static int load_map(FILE *file, t_map *map, t_elements *e) {
	map->height = e->num_lines;
	map->grid = calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return 1;

	char *line = NULL;
	size_t len = 0;

	int r = getline(&line, &len, file);
	if (r != 1 || line[0] != '\n') {
		free(line);
		return 1;
	}
	free(line);
	line = NULL;
	len = 0;

	for (int i = 0; i < map->height; i++) {
		r = getline(&line, &len, file);
		if (r == -1 || line[r - 1] != '\n') {
			free(line);
			return 1;
		}
		r--;

		if (i == 0) {
			if (r == 0) {
				free(line);
				return 1;
			}
			map->width = r;
		} else if (r != map->width) {
			free(line);
			return 1;
		}

		for (int k = 0; k < r; k++) {
			if (line[k] != e->empty && line[k] != e->obstacle) {
				free(line);
				return 1;
			}
		}
		line[r] = '\0';
		map->grid[i] = line;
		line = NULL;
		len = 0;
	}
	if (getline(&line, &len, file) != -1) {
		free(line);
		return 1;
	}
	free(line);
	return 0;
}

static int find_square(t_map *map, t_elements *e, t_square *sq) {
	int w = map->width;
	int *m = calloc(map->height * w, sizeof(int));
	if (!m)
		return 1;

	for (int i = 0; i < map->height; i++) {
		for (int j = 0; j < w; j++) {
			if (map->grid[i][j] == e->obstacle) {
				m[i * w + j] = 0;
			} else if (i == 0 || j == 0) {
				m[i * w + j] = 1;
			} else {
				int min = m[(i - 1) * w + j];
				if (m[i * w + j - 1] < min)
					min = m[i * w + j - 1];
				if (m[(i - 1) * w + j - 1] < min)
					min = m[(i - 1) * w + j - 1];
				m[i * w + j] = min + 1;
			}
			if (m[i * w + j] > sq->size) {
				sq->size = m[i * w + j];
				sq->i = i;
				sq->j = j;
			}
		}
	}
	free(m);
	return 0;
}

static void print_map(t_map *map, t_elements *e, t_square *sq) {
	if (sq->size > 0) {
		for (int i = sq->i - sq->size + 1; i <= sq->i; i++) {
			for (int j = sq->j - sq->size + 1; j <= sq->j; j++) {
				map->grid[i][j] = e->full;
			}
		}
	}
	for (int i = 0; i < map->height; i++)
		fprintf(stdout, "%s\n", map->grid[i]);
}

int execute_bsq(FILE *file) {
	t_elements e;
	if (load_elements(file, &e))
		return 1;

	t_map map;
	if (load_map(file, &map, &e)) {
		free_map(map.grid);
		return 1;
	}

	t_square sq = {0, 0, 0};
	if (find_square(&map, &e, &sq)) {
		free_map(map.grid);
		return 1;
	}

	print_map(&map, &e, &sq);
	free_map(map.grid);
	return 0;
}

int main(int argc, char **argv) {
	if (argc == 1) {
		if (execute_bsq(stdin))
			fprintf(stderr, "map error\n");
	} else {
		for (int i = 1; i < argc; i++) {
			FILE *file = fopen(argv[i], "r");
			if (!file || execute_bsq(file))
				fprintf(stderr, "map error\n");
			if (file)
				fclose(file);
			if (i < argc - 1)
				fprintf(stdout, "\n");
		}
	}
	return 0;
}
