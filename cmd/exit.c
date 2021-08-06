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

int end_shell(int flag)
{
	if (flag != 1)
		exit(0);
	return (0);
}

int	ft_exit(char **cmd, int flag)
{
	int	exit_status;

	exit_status = 0;
	printf("exit\n");
	if (cmd[1] == NULL)
		end_shell(flag);
	else if (cmd[1] && cmd[2])
	{
		exit_status = 1;
		printf("minishell: too many arguments\n");
	}
	else if (cmd[1] && is_num(cmd[1]) == ERROR)
	{
		exit_status = 255;
		printf("minishell: numeric argument required\n");
		end_shell(flag);
	}
	else if (cmd[1])
	{
		exit_status = ft_atoi(cmd[1]);
		end_shell(flag);
	}
	return (exit_status);
}
