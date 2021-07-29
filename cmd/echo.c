#include "minishell.h"

int	check_option_n(char *str)
{
	if (*str == '-')
		str++;
	else
		return (0);
	while (*str)
	{
		if (*str == 'n')
			str++;
		else
			return (0);
	}
	return (1);
}

int	ft_echo(char **cmd)
{
	int	i;
	int	option_n;

	i = 1;
	option_n = 0;
	if (cmd[0])
	{
		while (cmd[i] && check_option_n(cmd[i]) == 1)
		{
			option_n = 1;
			i++;
		}
		while (cmd[i])
		{
			// if (cmd[i][0] == '$')
				/* 환경병수 출력 */
			printf("%s", cmd[i]);
			if (cmd[i + 1] && cmd[i + 1][0] != '\0')
				printf(" ");
			i++;
		}
	}
	if (option_n == 0)
		printf("\n");
	return (0);
}
