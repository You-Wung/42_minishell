#include "../minishell.h"

int	is_num(char *str)
{
	while (*str)
	{
		if ('0' <= *str && *str <= '9')
			str++;
		else
			return (ERROR);
	}
	return (SUCCESS);
}

int	ft_exit(char **cmd)
{
	int	exit_status;

	exit_status = 0;
	printf("exit\n");
	if (cmd[1] == NULL)
		exit(0);
	if (cmd[1] && cmd[2])
	{
		exit_status = 1;
		printf("minishell: too many arguments\n");
	}
	if (cmd[1] && is_num(cmd[1]) == ERROR)
	{
		exit_status = 255;
		printf("minishell: numeric argument required\n");
		exit(0);
	}
	if (cmd[1])
	{
		exit_status = ft_atoi(cmd[1]);
		exit(0);
	}
	return (exit_status);
}
