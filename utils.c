#include "minishell.h"

extern t_ext	g_var;

int	is_flag(char c)
{
	if (c == '|' || c == '>'
		|| c == '<' || c == ';')
		return (1);
	return (0);
}

static int	count_qmark(char *str)
{
	int	i;
	int	rt;

	rt = 0;
	i = 0;
	while (str[i + 2])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			rt++;
			i += 2;
		}
		else
			i++;
	}
	return (rt);
}

static int	exchange_qmark(char *rt, int in)
{
	char	*buf;
	char	*for_free;
	int		i;

	i = 0;
	if (g_var.qmark == 0)
	{
		rt[in] = '0';
		return (1);
	}
	buf = ft_itoa(g_var.qmark);
	for_free = buf;
	while (*buf)
	{
		rt[in++] = *buf;
		i++;
		buf++;
	}
	free(for_free);
	return (i);
}

void	check_qmark(char **str)
{
	char	*rt;
	char	*tmp;
	int		i;
	int		in;

	if (!ft_strchr(*str, '$') && !ft_strchr(*str, '?'))
		return ;
	rt = malloc(ft_strlen(*str) + count_qmark(*str) + 1);
	set_vars(&i, &in, &tmp, str);
	while (str[0][++i])
	{
		if ((*str)[i] == '\'')
		{
			while ((*str)[i + 1] && (*str)[i] != '\'')
				i++;
		}
		if ((*str)[i + 1] && (*str)[i] == '$' && (*str)[i + 1] == '?' && ++i)
			in += exchange_qmark(rt, in);
		else
			rt[in++] = str[0][i];
	}
	rt[in] = '\0';
	free(tmp);
	*str = rt;
}

int	all_space(char **input)
{
	int	i;

	i = 0;
	while (input[0][i] == ' ' || input[0][i] == '\t')
		i++;
	if (!input[0][i])
	{
		free(*input);
		return (1);
	}
	return (0);
}
