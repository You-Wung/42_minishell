#include "minishell.h"

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

static void	pull_options(char *input, int i, int opt)
{
	int		in;
	char	buf[1024];
	t_match	m;
	int		j;

	j = 0;
	in = -1;
	ft_memset(&m, 0, sizeof(t_match));
	if (ft_strlen(input) > 1023)
		return ;
	while (++in < opt)
		buf[in] = input[in];
	while (input[i])
	{
		set_comma_index(input[i], &m);
		if (check_comma_index(m) && (input[i] == '>' || input[i] == '<'))
			return ;
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
	t_match	m;

	i = 0;
	ft_memset(&m, 0, sizeof(t_match));
	while (input[i] && input[i] != '|')
	{
		set_comma_index(*input, &m);
		if ((input[i] == '>' || input[i] == '<') && check_comma_index(m))
		{
			printf("FIRST : %d\t %s\n", i, &input[i]);
			if (input[i] == '>' || input[i] == '<')
				i++;
			while (input[++i] && input[i] == ' ')
				;
			while (input[++i] && input[i] != ' '
				&& input[i] != '>' && input[i] != '<')
				;
			//if ((input[i]) && ((input[i] == '>' && input[i - 1] == '>')
					//|| (input[i] == '<' && input[i - 1] == '<')))
				//i++;
			printf("PULLOPTION: [%s]\n", &input[i]);
			if (input[i] && input[i] != '>' && input[i] != '<')
				pull_options(input, i, find_opt(input));
		}
		else
			i++;
	}
}
