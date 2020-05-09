#ifndef SAVE_PRINCESSES_RESCUE_MISSION_H
#define SAVE_PRINCESSES_RESCUE_MISSION_H

#define DUMMY_NODE_SPAN -1
#define DUMMY_NODE_ROW -1
#define DUMMY_NODE_COL -1

#include "map_generator_augmented.h"

struct Node {
	char span;
	int row;
	int col;
	int priority;
	struct Node *neighbours[DIRECTIONS_COUNT]; 
};

struct Graph {
	int rows;
	int cols;
	int nodes_count;
	struct Node *nodes[];
};

struct Rescue_Mission {
	struct Graph *graph;
	int princesses_count;
	int drake_pos[2];
	int princesses_pos[][2];	
};

void free_rescue_mission(struct Rescue_Mission *mission);

struct Rescue_Mission *make_rescue_mission(struct Map *map);

void print_graph(const struct Graph *graph);

void print_rescue_mission(struct Rescue_Mission *mission);

#endif
