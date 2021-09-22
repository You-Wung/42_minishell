#include "minishell.h"

static int	checking(char *input, int i)
{
	while (input[i] && input[i] == ' ')
		i++;
	if (input[i] == '|')
		return (1);
	return (0);
}

static int	find_opt(char *input)
{
	int		i;
	t_match	m;

	i = 0;
	ft_memset(&m, 0, sizeof(t_match));
	while (input[i])
	{
		set_comma_index(input[i], &m);
		if (input[i] == ' ' && check_comma_index(m))
			return (i);
		i++;
	}
	return (0);
}

static int	prep(int *j, int *in, t_match *m, char *input)
{
	*j = 0;
	*in = -1;
	ft_memset(m, 0, sizeof(t_match));
	if (ft_strlen(input) > 1023)
		return (1);
	return (0);
}

static void	pull_options(char *input, int i, int opt)
{
	int		in;
	char	buf[1024];
	t_match	m;
	int		j;

	if (prep(&j, &in, &m, input))
		return ;
	while (++in < opt)
		buf[in] = input[in];
	while (input[i] && input[i] != '|')
	{
		set_comma_index(input[i], &m);
		if (check_comma_index(m) && is_re(input[i]))
			break ;
		buf[in++] = input[i];
		j = i - 1;
		while (input[++j])
			input[j] = input[j + 1];
	}
	while (input[opt])
		buf[in++] = input[opt++];
	buf[in] = '\0';
	i = -1;
	while (buf[++i])
		input[i] = buf[i];
}

void	modify_input_for_option(char *input)
{
	int		i;

	i = 0;
	while (input[i] && input[i] != '|')
	{
		if (is_re(input[i]) && ++i)
		{
			if (is_re(input[i]))
				i++;
			while (input[i] && input[i] == ' ')
				i++;
			while (input[i] && input[i] != ' ' && input[i] != '|'
				&& input[i] != '>' && input[i] != '<')
				i++;
			if (checking(input, i))
				return ;
			if (input[i] && !is_re(input[i]))
				pull_options(input, i, find_opt(input));
		}
		else
			i++;
	}
}
