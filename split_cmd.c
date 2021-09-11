#include "minishell.h"

extern t_ext	g_var;

static int	find_error(char *c)
{
	if (error_check(c) == ERROR)
		return (ERROR);
	if ((*c == '|' && is_flag(*(c + 1)))
		|| (*c == ';' && is_flag(*(c + 1)))
		|| (is_flag(*c) && is_flag(*(c + 1)) && *c != *(c + 1))
		|| (is_flag(*c) && is_flag(*(c + 1)) && *c != *(c + 1))
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

static void	chogiwha(t_match *m, int *b, int *c)
{
	ft_memset(m, 0, sizeof(t_match));
	*b = 1;
	*c = -1;
}

/* | > < ; 기준으로 커맨드 몇개로 잘릴까 */
int	count_cmd(char *input)
{
	int		rt;
	int		i;
	t_match	m;

	ft_memset(&m, 0, sizeof(t_match));
	chogiwha(&m, &rt, &i);
	while (input[++i] && (input[i] == '\'' || input[i] == '\"'
			|| input[i] == '|' || input[i] == ' '))
		;
	if (!input[i] || full_check(input))
		return (ERROR);
	i = -1;
	while (input[++i])
	{
		set_comma_index(input[i], &m);
		if (check_comma_index(m) && find_error(&input[i]) == ERROR)
			return (ERROR);
		if (is_flag(input[i]) && input[i + 1] && check_comma_index(m))
			rt++;
		if ((input[i] == '>' && input[i + 1] == '>')
			|| (input[i] == '<' && input[i + 1] == '<'))
			i++;
	}
	return (rt);
}

char	*fill_cmd(t_cmd **c, char **input)
{
	int		size;
	int		i;

	i = -1;
	size = count_cmd(*input);
	if (size == ERROR)
		return (NULL);
	if (single_redirection(*input))
		return (NULL);
	while (*input && ++i < size)
	{
		if (!flag_check(*input))
			*input = init_cmd(&(c[0][i]), input);
		if (*input == NULL || flag_check(*input))
		{
			printf("minishell: Error\n");
			return (NULL);
		}
	}
	count_flag(c, size);
	return (*input);
}
