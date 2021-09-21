#include "minishell.h"

//먼 나오는 플래그
int	ed_co(char *input)
{
	int		i;
	t_match	m;

	ft_memset(&m, 0, sizeof(t_match));
	i = 0;
	while (input[i])
	{
		set_comma_index(input[i], &m);
		if ((input[i] == '>' || input[i] == '<') && check_comma_index(m))
			return (1);
		if ((input[i] == '|') && check_comma_index(m))
			return (0);
		i++;
	}
	return (1);
}

int	is_re(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}
