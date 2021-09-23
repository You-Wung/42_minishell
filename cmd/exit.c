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

int	check_exit_sta(char **cmd)
{
	int	exit_status;

	exit_status = ft_atoi(cmd[1]);
	if (exit_status >= 255)
		exit_status = 255;
	return (exit_status);
}

void	print_exit_error(char *str)
{
	char	*buf;

	buf = "";
	buf = ft_strjoin(buf, "minishell: ");
	buf = ft_strjoin(buf, str);
	buf = ft_strjoin(buf, ": numeric argument required\n");
	write(2, buf, ft_strlen(buf));
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
		ft_putstr_fd("minishell: too many arguments\n", 2);
	}
	else if (cmd[1] && is_num(cmd[1]) == ERROR)
	{
		exit_status = 255;
		ft_putstr_fd("minishell: numeric argument required\n", 2);
		end_shell(flag, exit_status);
	}
	else if (cmd[1])
	{
		exit_status = check_exit_sta(cmd);
		if (ft_strlen(cmd[1]) >= 20)
			print_exit_error(cmd[1]);
		end_shell(flag, exit_status);
	}
	return (exit_status);
}
