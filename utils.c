#include "minishell.h"

extern t_ext	g_var;

int	is_flag(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

static int	count_qmark(char *str)
{
	int	i;
	int	rt;

	rt = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			rt += 3;
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
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (g_var.qmark == 0 && g_var.sig_qmark == 0)
	{
		rt[in] = '0';
		return (1);
	}
	if (g_var.sig_qmark)
		buf = ft_itoa(g_var.sig_qmark);
	else
		buf = ft_itoa(g_var.qmark);
	while (buf[j])
	{
		rt[in++] = buf[j++];
		i++;
	}
	free(buf);
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
	g_var.sig_qmark = 0;
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
