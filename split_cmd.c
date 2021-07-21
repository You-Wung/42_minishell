#include "minishell.h"

static int	ft_rt(char *str, int ret)
{
	if (ret == 0)
	{
		if (str[0] == 0)
			return (0);
		return (1);
	}
	return (ret);
}

static void	init_int(int *i, int *ret, int *in, int *flag)
{
	*i = -1;
	*ret = 0;
	*flag = 0;
	*in = 1;
}

static int	is_sep(char c)
{
	if (c == '|' || c == '>'
		|| c == '<' || c == ';')
	{
		if (c == '<')
			return (3);
		if (c == '>')
			return (2);
		return (1);
	}
	return (0);
}

/* | ; < > 단위로 끊어서 몇개의 커맨드인지 카운트*/
static int	count_cmd(char *str)
{
	int	i;
	int	ret;
	int	in;
	int	flag;

	init_int(&i, &ret, &in, &flag);
	while (str[++i])
	{
		if (is_sep(str[i]))
		{
			in = 1;
			if ((flag && 2 > is_sep(str[i - 1])) || (is_sep(str[i + 1])
				&& (is_sep(str[i]) != is_sep(str[i + 1])
				|| (is_sep(str[i - 1]) && is_sep(str[i + 1])))))
				return (ERROR);
			flag = is_sep(str[i]);
			continue ;
		}
		if (in == 1 && str[i] != ' ')
		{
			ret++;
			in = 0;
			flag = 0;
		}
	}
	return (ft_rt(str, ret));
}

void	fill_cmd(t_cmd **c, char *input, char **env)
{
	int	size;
	int	i;

	size = count_cmd(input);
	*c = (t_cmd *)malloc(sizeof(t_cmd) * (size + 1));
	c[size] = NULL;
	printf("it will be splited %d input : %s\n", size, input);
	i = -1;
	while (++i < size && input)
		input = init_cmd(c[i], input, env);
}
