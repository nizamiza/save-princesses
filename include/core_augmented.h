#ifndef SAVE_PRINCESSES_CORE_AUGMENTED_H
#define SAVE_PRINCESSES_CORE_AUGMENTED_H

#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "error.h"
#include "core_utils.h"
#include "core_map_generator.h"

#define ROAD 		' '
#define BUSH 		'@'
#define WALL 		'#'
#define DRAKE 		'D'
#define PRINCESS 	'P'

#define ROAD_ALT	'C'
#define BUSH_ALT	'H'
#define WALL_ALT	'N'

#define CURSOR		'>'

#define CELLS "CHNDP"
#define PRINCESSES_MAX_COUNT 5

#define _static_always_inline static inline __attribute__ ((__always_inline__))
#define _always_inline inline __attribute__ ((__always_inline__))

struct Map {
	int rows;
	int cols;
	int drake_wake_time;
	char *cells[];
};

_always_inline char get_cell_span(char cell)
{
	switch (cell) {
		case ROAD_ALT:
		case WALL_ALT:
		case ROAD:
		case WALL:
		case DRAKE:
		case PRINCESS:
			return 1;
		case BUSH:
		case BUSH_ALT:
			return 2;
		default:
			return -1;
	}
}

_always_inline
char validate_cell(char cell, int *princesses_count, bool *drake_is_set)
{
	char *error_message = NULL; 

	if (cell == EOF)
		error_message = strdup(ERR_MSG_FSCANF);

	else if (get_cell_span(cell) < 0)
		error_message = strdup(ERR_MSG_CELL_SYM);

	else if (cell == PRINCESS && ++(*princesses_count) >= PRINCESSES_MAX_COUNT)
		error_message = strdup(ERR_MSG_PRINCESSES_MAX_COUNT_EXCEEDED);

	else if (cell == DRAKE) {
		if (*drake_is_set)
			error_message = strdup(ERR_MSG_MULTI_DRAKE_DEFS);
		else *drake_is_set = true;
	}
	
	if (error_message) {
		eprintf(error_message);
		return -1;
	}

	return cell;
}

#define print_delta_time(stream, func_name, delta_time) \
	(fprintf((stream), "> %s took %ld ns\n", (func_name), (delta_time)))

_always_inline void record_timestamp(struct timespec *timespec)
{
	if (clock_gettime(CLOCK_REALTIME, timespec) < 0)
		eprintf(ERR_MSG_CLOCK_GETTIME);
}

_always_inline long calc_delta_time(struct timespec start, struct timespec end) {
	return end.tv_nsec - start.tv_nsec;
}

int *save_princesses(struct Map *map, int *path_length);

#endif
