#include <stdio.h>
#include <stdlib.h>

typedef struct s_map {
	char **grid;
	int height;
	int width;
	char empty;
	char obstacle;
	char full;
} t_map;

static void free_map(t_map *map) {
	if (!map->grid)
		return;
	for (int i = 0; i < map->height; i++)
		free(map->grid[i]);
	free(map->grid);
}

static int fail(t_map *map, char *line) {
	free(line);
	free_map(map);
	return 1;
}

static int load_map(FILE *file, t_map *map) {
	char *line = NULL;
	size_t cap = 0;
	int r;

	if (fscanf(file, "%d %c %c %c", &map->height,
			&map->empty, &map->obstacle, &map->full) != 4)
		return 1;
	r = getline(&line, &cap, file);
	if (r < 1 || line[r - 1] != '\n')
		return fail(map, line);
	for (int i = 0; i < r - 1; i++)
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\r')
			return fail(map, line);
	free(line);
	line = NULL;
	cap = 0;
	if (map->height <= 0
		|| map->empty < 32 || map->empty > 126
		|| map->obstacle < 32 || map->obstacle > 126
		|| map->full < 32 || map->full > 126
		|| map->empty == map->obstacle || map->empty == map->full
		|| map->obstacle == map->full)
		return 1;
	map->grid = calloc(map->height, sizeof(char *));
	if (!map->grid)
		return 1;
	for (int i = 0; i < map->height; i++) {
		r = getline(&line, &cap, file);
		if (r <= 1 || line[r - 1] != '\n')
			return fail(map, line);
		r--;
		if (i == 0)
			map->width = r;
		else if (r != map->width)
			return fail(map, line);
		for (int j = 0; j < r; j++)
			if (line[j] != map->empty && line[j] != map->obstacle)
				return fail(map, line);
		line[r] = '\0';
		map->grid[i] = line;
		line = NULL;
		cap = 0;
	}
	if (getline(&line, &cap, file) != -1)
		return fail(map, line);
	free(line);
	return 0;
}

static int solve(t_map *map) {
	int *dp = calloc(map->width + 1, sizeof(int));
	int best = 0;
	int best_i = 0;
	int best_j = 0;

	if (!dp)
		return 1;
	for (int i = 0; i < map->height; i++) {
		int diagonal = 0;
		for (int j = 1; j <= map->width; j++) {
			int top = dp[j];
			if (map->grid[i][j - 1] == map->obstacle)
				dp[j] = 0;
			else {
				int min = dp[j] < dp[j - 1] ? dp[j] : dp[j - 1];
				if (diagonal < min)
					min = diagonal;
				dp[j] = min + 1;
			}
			if (dp[j] > best) {
				best = dp[j];
				best_i = i - best + 1;
				best_j = j - best;
			}
			diagonal = top;
		}
	}
	free(dp);
	for (int i = best_i; i < best_i + best; i++)
		for (int j = best_j; j < best_j + best; j++)
			map->grid[i][j] = map->full;
	for (int i = 0; i < map->height; i++)
		fprintf(stdout, "%s\n", map->grid[i]);
	return 0;
}

static int execute_bsq(FILE *file) {
	t_map map = {0};
	if (load_map(file, &map))
		return 1;
	if (solve(&map)) {
		free_map(&map);
		return 1;
	}
	free_map(&map);
	return 0;
}

int main(int argc, char **argv) {
	if (argc == 1) {
		if (execute_bsq(stdin))
			fprintf(stderr, "map error\n");
		return 0;
	}
	for (int i = 1; i < argc; i++) {
		FILE *file = fopen(argv[i], "r");
		if (!file || execute_bsq(file))
			fprintf(stderr, "map error\n");
		if (file)
			fclose(file);
		if (i < argc - 1)
			fprintf(stdout, "\n");
	}
	return 0;
}
