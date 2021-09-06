#include "../minishell.h"

extern t_ext	g_var;

void	re_RR_child(t_cmd *c)
{
	int		out;

	out = open(c[1].cmd[0], O_RDWR | O_CREAT | O_APPEND, 0644);
	if (check_open(out, c) == 1)
		exit (1);
	dup2(out, STDOUT_FILENO);
	g_var.qmark = use_redi_cmd(c);
	close(out);
	exit(g_var.qmark);
}

int	ft_redirect_RR(t_cmd *c)
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
	else if (pid == 0)
		re_RR_child(c);
	else if (pid > 0)
	{
		waitpid(pid, &wstatus, 0);
		g_var.qmark = WEXITSTATUS(wstatus);
		if (g_var.qmark == 127)
			printf("minishell: %s: command not found.\n", c[0].cmd[0]);
	}
	return (SUCCESS);
}
