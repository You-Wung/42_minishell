#include "minishell.h"

char	*set_flag(t_cmd *c, char *input, int *sign)
{
	if (*input == '>' && *(input + 1) == '>')
		c->flag = R_APP;
	else if (*input == '<' && *(input + 1) == '<')
		c->flag = L_APP;
	else if (*input == '>')
		c->flag = R_RE;
	else if (*input == '<')
		c->flag = L_RE;
	else if (*input == '|')
		c->flag = PIPE;
	else if (*input == ';')
		c->flag = SEMI;
	else
		c->flag = 0;
	while (*input == '>' || *input == '<'
		|| *input == ';' || *input == '|')
	{
		input++;
		*sign = -1;
	}
	return (input);
}

int	check_input(char *input, t_match *m)
{
	int	c;
	int	dc;

	c = m->comma % 2;
	dc = m->dcomma % 2;
	if (*input && (c || dc || *input != '>')
		&& (c || dc || *input != ';')
		&& (c || dc || *input != '<')
		&& (c || dc || *input != '|'))
		return (1);
	return (0);
}

static char	*set_after(char *input)
{
	char	*rt;
	int		i;

	i = -1;
	rt = malloc(ft_strlen(input));
	while (is_flag(input[++i]))
		rt[i] = input[i];
	while (input[i] && input[i] == ' ')
	{
		rt[i] = ' ';
		i++;
	}
	while (input[i] && input[i] != ' ')
	{
		rt[i] = input[i];
		i++;
	}
	rt[i] = '\0';
	return (rt);
}

static char	*save_cmd(char *input, int i)
{
	int		in;
	int		in2;
	char	*ret;
	char	*after;

	ret = malloc(ft_strlen(input));
	//ft_memset(ret, ' ', ft_strlen(input));
	in = -1;
	in2 = 0;
	while (!is_flag(input[++in]))
		ret[in2++] = input[in];
	after = set_after(&(input[in]));
	while (is_flag(input[in]) || input[in] == ' ')
		in++;
	while (input[in] && input[in] != ' ')
		in++;
	while (input[in] && in < i)
		ret[in2++] = input[in++];
	input_plus_after(&(ret[in2]), &after, &in2);
	while (input[in])
		ret[in2++] = input[in++];
	ret[in2] = '\0';
	return (ret);
}

char	*edit_input(char **input)
{
	t_match	m;
	int		i;
	int		cnt;

	i = -1;
	cnt = 0;
	ft_memset(&m, 0, sizeof(t_match));
	if ((**input == '<' && *(*input + 1) == '<') || **input == ';')
		return (NULL);
	while (*(*input + ++i))
	{
		if (*(*input + i) == '\"')
			m.comma++;
		if (*(*input + i) == '\'')
			m.dcomma++;
		if (is_flag(*(*input + i)) && !(m.comma % 2) && !(m.dcomma % 2))
		{
			cnt++;
			if (cnt == 2)
				return (save_cmd(*input, i));
		}
	}
	if (*(*input + i) == '\0')
		return (save_cmd(*input, i));
	return (*input);
}
