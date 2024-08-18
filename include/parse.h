#ifndef PARSE_H
# define PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

enum tokenValues
{
	T_GENERAL	= -1,
	T_WHITESPC	= ' ',
	T_TAB		= '\t',
	T_NEWLINE	= '\n',
	T_QUOTE		= '\'',
	T_DQUOTE	= '\"',
	T_RED_IN	= '<',
	T_RED_OUT	= '>',
	T_PIPE		= '|',
	T_VAR		= '$',
	T_EXIT_STAT	= 1024,
	T_DELIM,
	T_RED_APPEN,
	T_COMMAND,
	T_FLAG
};

typedef struct s_input
{
	char			*data;
	int				type;
	char			*path;
	struct s_input	*next;
}	t_input;

int	input_parse(char *input);

#endif