#include "minishell.h"

extern t_ext	g_var;

static void	input_is_null(void)
{
	printf("%c[1A", 27);
	printf("%c[1000D", 27);
	printf("%sexit\n", make_prompt());
	printf(COLOR_RESET);
	tcsetattr(STDIN_FILENO, TCSANOW, &g_var.restore);
	exit(0);
}

/* t_cmd *c 동적할당 해주는 부분 */
static t_cmd	*malloc_c(char *input)
{
	t_cmd	*c;
	int		size;

	size = count_cmd(input);
	if (size == ERROR)
	{
		printf("minishell : error\n");
		return (NULL);
	}
	c = (t_cmd *)malloc(sizeof(t_cmd) * size);
	return (c);
}

char	*make_prompt(void)
{
	static char	prompt[1027];
	int			i;

	ft_memset(&prompt[0], 0, 1027);
	prompt[0] = 'm';
	prompt[1] = 'i';
	prompt[2] = 'n';
	prompt[3] = 'i';
	prompt[4] = 's';
	prompt[5] = 'h';
	prompt[6] = 'e';
	prompt[7] = 'l';
	prompt[8] = 'l';
	i = 0;
	while (prompt[i])
		i++;
	prompt[i++] = '$';
	prompt[i++] = ' ';
	prompt[i] = '\0';
	return (prompt);
}

static void	freee_c(t_cmd *c)
{
	int	i;

	i = -1;
	while (c->cmd[++i])
		free(c->cmd[i]);
	free(c->cmd);
}

int	start_read(void)
{
	t_cmd	*c;
	char	*input;

	while (1)
	{
		input = readline(make_prompt());
		if (input == NULL)
			input_is_null();
		if (!(*input) || all_space(input))
			continue ;
		add_history(input);
		c = malloc_c(input);
		g_var.size_pi = 0;
		if (c && fill_cmd(c, input))
		{
			g_var.writing = 1;
			g_var.qmark = exec_cmd(c);
			g_var.writing = 0;
			freee_c(c);
		}
		free(c);
		free(input);
	}
	return (0);
}
