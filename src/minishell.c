#include "minishell.h"
#include "parse.h"
#include "libft.h"

void	free_all(char *input, char *str, t_input *commands)
{
	t_input *current;

	current = commands;
	if (str)
		free (str);
	if (input)
		free (input);
	while (current)
	{
		if (current->data)
			free (current->data);
		if (current->path)
			free (current->path);
		commands = commands->next;
		free (current);
		current = NULL;
		current = commands;
	}
}

static char	*get_prompt()
{
	char	*prompt;
	char	cwd[1024];
	char	*user;
	char	*path;
	size_t	i;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		return (NULL);
	}
	user = getenv("USER");
	path = ft_strnstr(cwd, user, ft_strlen(cwd));
	i = 1;
	while (i++ < ft_strlen(user))
		path++;
	path[0] = '~';
	prompt = ft_strjoin("\033[1;32m", user);
	prompt = ft_freejoin(prompt, "\033[0m:\033[1;34m");
	prompt = ft_freejoin(prompt, path);
	prompt = ft_freejoin(prompt, "\033[0m$ ");
	return (prompt);
}

static void	print_temp(t_input *commands)
{
	size_t	i;
	t_input	*head;

	i = 1;
	head = commands;
	while (commands)
	{
		ft_printf("\nn.%d\ndata: %s\ntype: %d\npath: %s\n", i, commands->data, commands->type, commands->path);
		i++;
		commands = commands->next;
	}
	commands = head;
}

static int	init()
{
	char	*input;
	char	*str;
	char	*prompt;
	t_input	*commands;

	while (1)
	{
		if (!(prompt = get_prompt()))
			return (1);
    	input = readline(prompt);
		free (prompt);
		if (input[0] != '0')
		{
			str = ft_strtrim(input, " \t\n");
			commands = malloc(sizeof(t_input));
			if (input_parse(str, commands))
				print_temp(commands);
			free_all(input, str, commands);
		}
		else
		{
			free (input);
			return (1);
		}
    }
	return (1);
}

int	main(void)
{
	init();

	return (0);
}