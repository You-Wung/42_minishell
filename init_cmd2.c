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

static char	*set_after(char *input, int in)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char) * ft_strlen(input) + 1);
	while (is_flag(input[in]))
		ret[i++] = input[in++];
	while (input[in] && input[in] == ' ')
	{
		ret[i++] = ' ';
		in++;
	}
	while (input[in] && input[in] != ' ')
		ret[i++] = input[in++];
	ret[i] = '\0';
	printf("[%s]\n", ret);
	return (ret);
}

static char	*save_cmd(char *input, int i)
{
	int		in;
	int		in2;
	char	*ret;
	char	*after;

	printf("input : [%s]\n", input);
	ret = (char *)malloc(sizeof(char) * ft_strlen(input) + 1);
	in = 0;
	in2 = 0;
	while (input[in] && !is_flag(input[in]))
		ret[in2++] = input[in++];
	after = set_after(input, in);
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
			if (++cnt == 2)
				return (save_cmd(*input, i));
		if (*(*input + i) == '|' || *(*input + i) == ';')
			return (*input);
	}
	if (*(*input + i) == '\0')
		return (save_cmd(*input, i));
	return (*input);
}
