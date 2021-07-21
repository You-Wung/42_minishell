#include "minishell.h"

char	*make_prompt(void)
{
	static char	prompt[1027];
	int		i;

	ft_memset(&prompt[0], 0, 1027);
	getcwd(prompt, 1024);
	i = 0;
	while (prompt[i])
		i++;
	prompt[i++] = '$';
	prompt[i++] = ' ';
	prompt[i] = '\0';
	return (prompt);
}

int	start_read(char **env)
{
	t_cmd	*c;
	char	*input;

	input = readline(make_prompt());
	while (input)
	{
		add_history(input);
		fill_cmd(&c, input, env);
		free(input);
		input = readline(make_prompt());
	}
	return (0);
}
