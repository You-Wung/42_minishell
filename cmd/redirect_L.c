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

int	ft_redirect_L(t_cmd *c)
{
	pid_t	pid;
	int		in;
	int		wstatus;

	pid = fork();
	g_var.pid[g_var.pnum++] = pid;
	if (pid == 0)
	{
		in = open(c[1].cmd[0], O_RDONLY);
		if (check_open(in, c) == 1)
			return (1);
		dup2(in, STDIN_FILENO);
		g_var.qmark = use_redi_cmd(c);
		close(in);
		exit(g_var.qmark);
	}
	else if (pid > 0)
	{
		waitpid(pid, &wstatus, 0);
		g_var.qmark = WEXITSTATUS(wstatus);
	}
	return (SUCCESS);
}
