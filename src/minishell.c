#include "minishell.h"
#include "parse.h"
#include "libft.h"

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

static void	print_temp()
{
	t_input *commands;
	size_t	i;

	i = 1;
	while (commands)
	{
		ft_printf("\nn.%d\ndata: %s\ntype: %d\npath: %s\n", i, commands->data, commands->type, commands->path);
		i++;
		commands = commands->next;
	}
}

static int	init()
{
	char	*input;
	char	*str;
	char	*prompt;

	while (1)
	{
		if (!(prompt = get_prompt()))
			return (1);
    	input = readline(prompt);
		free (prompt);
		if (input[0] != '0')
		{
			str = ft_strtrim(input, " \t\n");
			if (input_parse(str))
				print_temp();
			free (input);
			free (str);
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