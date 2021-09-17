#include "../minishell.h"

extern t_ext	g_var;

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

int	end_shell(int flag, int exit_status)
{
	if (flag != 1)
	{
		printf(COLOR_RESET);
		tcsetattr(STDIN_FILENO, TCSANOW, &g_var.restore);
		exit(exit_status);
	}
	return (0);
}

int	ft_exit(char **cmd, int flag)
{
	int	exit_status;

	exit_status = 0;
	printf("exit\n");
	if (cmd[1] == NULL)
		end_shell(flag, exit_status);
	else if (cmd[1] && cmd[2])
	{
		exit_status = 1;
		printf("minishell: too many arguments\n");
	}
	else if (cmd[1] && is_num(cmd[1]) == ERROR)
	{
		exit_status = 255;
		printf("minishell: numeric argument required\n");
		end_shell(flag, exit_status);
	}
	else if (cmd[1])
	{
		exit_status = ft_atoi(cmd[1]);
		if (ft_strlen(cmd[1]) >= 20)
			printf("minishell: %s: numeric argument required\n", cmd[1]);
		end_shell(flag, exit_status);
	}
	return (exit_status);
}
