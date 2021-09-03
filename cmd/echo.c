#include "../minishell.h"

extern t_ext	g_var;

int	check_option_n(char *str)
{
	if (*str && *str == '-')
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
	while (cmd[i] && check_option_n(cmd[i]) == 1)
	{
		option_n = 1;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		++i;
		if (cmd[i])
			printf(" ");
	}
	if (option_n == 0)
		printf("\n");
	return (0);
}
