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
	else
		c->flag = 0;
	while (*input == '>' || *input == '<'
		|| *input == '|')
	{
		input++;
		*sign = -1;
	}
	return (input);
}

int	check_input(char *input, t_match *m)
{
	if (!(*input) || (check_comma_index(*m) && *input == '>')
		|| (check_comma_index(*m) && *input == ';')
		|| (check_comma_index(*m) && *input == '<')
		|| (check_comma_index(*m) && *input == '|'))
		return (0);
	while (*input && *input == ' ')
		input++;
	if (!*input)
		return (0);
	return (1);
}

static char	*set_after(char *input, int in)
{
	char	*after;
	int		i;

	i = 0;
	after = malloc(sizeof(char) * ft_strlen(input) + 10);
	while (is_flag(input[in]))
		after[i++] = input[in++];
	while (input[in] && input[in] == ' ')
	{
		after[i++] = ' ';
		in++;
	}
	while (input[in] && input[in] != ' ')
		after[i++] = input[in++];
	after[i] = '\0';
	return (after);
}

static char	*save_cmd(char *input, int i)
{
	int		in;
	int		in2;
	char	*ret;
	char	*after;

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
	in++;
	while (input[in] && in < i)
		ret[in2++] = input[in++];
	input_plus_after(&(ret[in2]), &after, &in2);
	while (input[in])
		ret[in2++] = input[in++];
	ret[in2] = '\0';
	modify_input_for_option(ret);
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
	if (**input == '<' && *(*input + 1) == '<')
		return (NULL);
	printf("START\n");
	while (*(*input + ++i))
	{
		set_comma_index(*(*input + i), &m);
		if ((*(*input + i) == '>' || *(*input + i) == '<')
			&& check_comma_index(m))
			if (++cnt == 2)
				return (save_cmd(*input, i));
		if (*(*input + i) == '|')
			return (*input);
	}
	printf("END\n");
	if (*(*input + i) == '\0')
		return (save_cmd(*input, i));
	return (*input);
}
