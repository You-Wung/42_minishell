#include "minishell.h"

extern t_ext	g_var;

void	count_flag(t_cmd **c, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (c[0][i].flag == PIPE)
			g_var.size_pi++;
		if (c[0][i].flag == SEMI && i + 1 < size)
			g_var.size_se++;
	}
}

void	set_vars(int *i, int *in, char **tmp, char **str)
{
	*i = -1;
	*in = 0;
	*tmp = *str;
}

int	flag_check2(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == ';')
		return (1);
	else
		return (0);
}

int	flag_check(char *input)
{
	int		i;
	t_match	m;

	i = -1;
	ft_memset(&m, 0, sizeof(t_match));
	while (input[++i])
	{
		set_comma_index(input[i], &m);
		if (is_flag(input[i]) && is_flag(input[i + 1])
			&& is_flag(input[i + 2]) && check_comma_index(m))
			return (1);
		if (is_flag(input[i]) && is_flag(input[i + 1])
			&& (input[i] != input[i + 1]) && check_comma_index(m))
			return (1);
		if (input[i] == '|' && input[i + 1] == '|' && check_comma_index(m))
			return (1);
	}
	return (flag_check2(input));
}

void	input_plus_after(char *s1, char **s2, int *in)
{
	int	i;

	i = -1;
	while ((*s2)[++i])
		s1[i] = (*s2)[i];
	free(*s2);
	*in = *in + i;
}
