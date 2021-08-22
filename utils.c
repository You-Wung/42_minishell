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
	int		i;

	i = 0;
	if (g_var.qmark == 0)
	{
		rt[in] = '0';
		return (1);
	}
	buf = ft_itoa(g_var.qmark);
	printf("Qmark Exchange started. buf : %s\n", buf);
	while (*buf)
	{
		rt[in++] = *buf;
		i++;
		buf++;
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
	rt = (char *)malloc(ft_strlen(*str) + count_qmark(*str) + 1);
	i = 0;
	in = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '`')
			return ;
		if ((*str)[i] == '$' && (*str)[i + 1] == '?' && ++i)
			in += exchange_qmark(rt, in);
		else
			rt[in++] = (*str)[i];
		i++;
	}
	tmp = *str;
	free(tmp);
	*str = rt;
}
