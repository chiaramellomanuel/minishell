#include "parse.h"
#include "libft.h"

int	get_type(char c)
{
	switch (c)
	{
		case T_QUOTE:
			return (T_QUOTE);
			break;
		case T_DQUOTE:
			return (T_DQUOTE);
			break;
		case T_RED_IN:
			return (T_RED_IN);
			break;
		case T_RED_OUT:
			return (T_RED_OUT);
			break;
		case T_PIPE:
			return (T_PIPE);
			break;
		case T_VAR:
			return (T_VAR);
			break;
		default:
			return (T_GENERAL);
	}
	return (0);
}

static size_t	cmd_len(char *input, int type)
{
	size_t	i;

	i = 0;
	switch (type)
	{
		case T_QUOTE:
			input++;
			while (*input && *input != T_QUOTE)
			{
				input++;
				i++;
			}
			return (i);
			break;
		case T_DQUOTE:
			input++;
			while (*input && *input != T_DQUOTE)
			{
				input++;
				i++;
			}
			return (i);
			break;
		case T_RED_IN:
			if (*(input + 1) && *(input + 1) == T_RED_IN)
				return (2);
			else
				return (1);
			break;
		case T_RED_OUT:
			if (*(input + 1) && *(input + 1) == T_RED_OUT)
				return (2);
			else
				return (1);
			break;
		case T_PIPE:
			return (1);
			break;
		default:
			while (*input && (*input != T_WHITESPC &&
					*input != T_NEWLINE && *input != T_TAB))
			{
				input++;
				i++;
			}
			return (i);
			break;
	}
	return (0);
}

void	input_parse(char *input)
{
	t_input	*commands;
	t_input	*head;
	size_t	size;
	size_t	i;

	commands = malloc(sizeof(t_input));
	head = commands;
	while (*input && *input != T_NEWLINE)
	{
		commands->type = get_type(*input);
		size = cmd_len(input, commands->type);
		commands->data = ft_calloc(size + 1, sizeof(char));
		i = 0;
		switch (commands->type)
		{
			case T_QUOTE:
			case T_DQUOTE:
				input++;
				while (i < size)
					while (i < size)
					commands->data[i++] = *input++;
				commands->next = NULL;
				if (*input == T_QUOTE || *input == T_DQUOTE)
					input++;
				break;
			case T_RED_IN:
				if (size == 2)
				{
					commands->data = "<<";
					commands->type = T_DELIM;
					input++;
				}
				else
					commands->data[0] = T_RED_IN;
				input++;
				commands->next = NULL;
				break;
			case T_RED_OUT:
				if (size == 2)
				{
					commands->data = ">>";
					commands->type = T_RED_APPEN;
					input++;
				}
				else
					commands->data[0] = T_RED_OUT;
				input++;
				commands->next = NULL;
				break;
			default:
				while (i < size)
					commands->data[i++] = *input++;
				commands->next = NULL;
				break;
		}
		while (*input == T_WHITESPC || *input == T_TAB ||
				*input == T_NEWLINE)
			input++;
		if (*input)
			commands->next = malloc(sizeof(t_input));
		commands = commands->next;
	}
	commands = head;
}
