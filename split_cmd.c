#include "minishell.h"

extern t_ext	g_var;

static int	find_error(char *c)
{
	if ((*c == '|' && is_flag(*(c + 1)))
		|| (*c == ';' && is_flag(*(c + 1)))
		|| (is_flag(*c) && is_flag(*(c + 1) && is_flag(*(c - 1))))
		|| (is_flag(*c) && is_flag(*(c + 1) && is_flag(*(c - 1))))
		|| (*c == '>' && *(c + 1) == '<')
		|| (*c == '<' && *(c + 1) == '>'))
		return (ERROR);
	while (*c)
		c++;
	c--;
	if (*c == '>' || *c == '<' || *c == '|')
		return (ERROR);
	return (0);
}

static void	chogiwha(char *a, int *b, int *c)
{
	*a = 0;
	*b = 1;
	*c = -1;
}

/* | > < ; 기준으로 커맨드 몇개로 잘릴까 */
int	count_cmd(char *input)
{
	int		rt;
	int		i;
	char	c;

	if (input[0] == '\0')
		return (0);
	chogiwha(&c, &rt, &i);
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '\"' || input[i] == '`')
		{
			if (c == input[i])
				c = 0;
			else if (!c)
				c = input[i];
		}
		if (c && find_error(&input[i]) == ERROR)
			return (ERROR);
		if (is_flag(input[i]) && input[i + 1] && !c)
			rt++;
		if ((input[i] == '>' && input[i + 1] == '>')
			|| (input[i] == '<' && input[i + 1] == '<'))
			i++;
	}
	return (rt);
}

char	*fill_cmd(t_cmd **c, char **input)
{
	int	size;
	int	i;

	i = -1;
	size = count_cmd(*input);
	while (*input && ++i < size)
	{
		*input = init_cmd(&(c[0][i]), input);
		if (*input == NULL || flag_check(*input))
		{
			printf("minishell: Error\n");
			return (NULL);
		}
	}
	i = -1;
	while (++i < size)
	{
		if (c[0][i].flag == PIPE)
			g_var.size_pi++;
		if (c[0][i].flag == SEMI && i + 1 < size)
			g_var.size_se++;
	}
	return (*input);
}
