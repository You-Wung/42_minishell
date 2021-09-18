#include "minishell.h"

int	ed_co(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
			return (1);
		if (input[i] == '|')
			return (0);
		i++;
	}
	return (1);
}
