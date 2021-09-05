#include "minishell.h"

void	set_vars(int *i, int *in, char **tmp, char **str)
{
	*i = -1;
	*in = 0;
	*tmp = *str;
}

int	flag_check(char *input)
{
	int	i;
	int	comma;

	i = -1;
	comma = 0;
	while (input[++i])
	{
		if ((is_flag(input[i]) && is_flag(input[i + 1])
				&& is_flag(input[i + 2])) && comma % 2 == 0)
			return (1);
		if (comma % 2 == 0 && is_flag(input[i])
			&& is_flag(input[i + 1]) && (input[i] != input[i + 1]))
			return (1);
		if ((input[i] == '|' && input[i + 1] == '|')
			|| (input[i] == ';' && input[i + 1] == ';'))
			return (1);
		if (is_flag(input[i]) && ++i)
		{
			while (input[i] == ' ')
				i++;
			if (is_flag(input[i]))
				return (1);
		}
	}
	printf("NO ERROR\n");
	return (0);
}

void	input_plus_after(char *s1, char **s2, int *in)
{
	int	i;

	i = -1;
	while ((*s2)[++i])
		s1[i] = (*s2)[i];
	free(*s2);
	*in = *in + i;
}
