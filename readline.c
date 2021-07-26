#include "minishell.h"

extern t_ext var;

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

int	start_read(void)
{
	t_cmd	*c;
	char	*input;

	while (1)
	{
		input = readline(make_prompt());
		if (!input)
			break ;
		add_history(input);
		fill_cmd(&c, input);
		free(input);
	}
	return (0);
}
