#include "minishell.h"

extern t_ext	g_var;

static char	*its_error(void)
{
	printf("minishell: Error\n");
	g_var.qmark = 258;
	return (NULL);
}

static int	find_error(char *c)
{
	if (error_check(c) == ERROR)
		return (ERROR);
	if (*c == ';'
		|| (*c == '>' && *(c + 1) == '<')
		|| (*c == '<' && *(c + 1) == '>'))
		return (ERROR);
	while (*c)
		c++;
	c--;
	while (*c == ' ')
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
			|| input[i] == ' ' || is_flag(input[i])))
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
	char	*tmp;
	int		size;
	int		i;
	int		cnt;

	cnt = 0;
	i = -1;
	size = count_cmd(*input);
	if (size == ERROR)
		return (NULL);
	while (*input && ++i < size)
	{
		tmp = *input;
		*input = single_redirection(*input);
		if ((tmp != *input || !**input) && ++cnt)
			continue ;
		if (!flag_check(*input))
			*input = init_cmd(&(c[0][i - cnt]), input);
		if (*input == NULL || flag_check(*input))
			return (its_error());
		g_var_fre();
	}
	count_flag(c, size);
	return (*input);
}
