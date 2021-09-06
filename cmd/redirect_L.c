#include "../minishell.h"

extern t_ext	g_var;

int	check_open(int in, t_cmd *c)
{
	if (in < 0)
	{
		printf("minishell: no such file or directory: %s\n", c[1].cmd[0]);
		return (1);
	}
	return (0);
}

void	re_L_child(t_cmd *c)
{
	int	in;

	in = open(c[1].cmd[0], O_RDONLY);
	if (check_open(in, c) == 1)
		exit (1);
	dup2(in, STDIN_FILENO);
	g_var.qmark = use_redi_cmd(c);
	close(in);
	exit(g_var.qmark);
}

int	ft_redirect_L(t_cmd *c)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	g_var.pid[g_var.pnum++] = pid;
	if (pid < 0)
	{
		printf("fork error\n");
		return (ERROR);
	}
	if (pid == 0)
		re_L_child(c);
	else if (pid > 0)
	{
		waitpid(pid, &wstatus, 0);
		g_var.qmark = WEXITSTATUS(wstatus);
		if (g_var.qmark == 127)
			printf("minishell: %s: command not found.\n", c[0].cmd[0]);
	}
	return (SUCCESS);
}
