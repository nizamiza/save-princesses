#ifndef SAVE_PRINCESSES_ERROR_H
#define SAVE_PRINCESSES_ERROR_H

#include <stdio.h>
#include <errno.h>

/* Error messages */

#define ERR_MSG_FOPEN 		"Could not open map file\n"
#define ERR_MSG_MALLOC 		"Could not allocate memory\n"
#define ERR_MSG_NEG_VAL		"Rows and cols cannot have negative value\n"
#define ERR_MSG_MAP_PARAMS	"Could not read map parameters\n"
#define ERR_MSG_READ_CELL_SYM	"Could not read cell symbol\n"
#define ERR_MSG_FSCANF		"Failed to read from file\n"
#define ERR_MSG_SCANFF 		"Failed to scan input\n"
#define ERR_MSG_CELL_SYM 	"Incorrect symbol\n"
#define ERR_MSG_FCLOSE 		"Could not close file\n"

#define func_perror(messages...) (fprintf(stderr, "%s: " messages, __func__))

#define PERROR_MALLOC (func_perror(ERR_MSG_MALLOC))

#define PERROR_NEG_ROWS_COLS {		\
	errno = EINVAL;			\
	func_perror(ERR_MSG_NEG_VAL);	\
}

#endif