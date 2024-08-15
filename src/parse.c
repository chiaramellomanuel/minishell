#include "minishell.h"

static char	*trim_input(char *input)
{
	int		i;
	int		j;
	int		offset;
	char	*str;
	
	i = 0;
	while (input[i] == ' ' || input[i] == '\t' || input[i] == '\n')
		i++;
	offset = i;
	while (input[offset + 1])
		offset++;
	while (input[offset] == ' ' || input[offset] == '\t' || input[offset] == '\n')
		offset--;
	str = ft_calloc((offset - i) + 2, sizeof(char));
	j = 0;
	while (i <= offset)
		str[j++] = input[i++];
	return (str);
}

static char	*get_prompt()
{
	char	*prompt;
	char	cwd[1024];
	size_t	i;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		return (NULL);
	}
	i = 0;
	while (cwd[i++]);
		;
	prompt = ft_strjoin("\033[1;32m", getenv("USER"));
	prompt = ft_freejoin(prompt, "\033[0m:\033[1;34m");
	prompt = ft_freejoin(prompt, cwd);
	prompt = ft_freejoin(prompt, "\033[0m$ ");
	return (prompt);
}

int	main(void)
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
			str = trim_input(input);
			// ft_printf("%s\n", str);
			free (input);
			free (str);
		}
		else
		{
			free (input);
			return (0);
		}
    }
	return (0);
}
