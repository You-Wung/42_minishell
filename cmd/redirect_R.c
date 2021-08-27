#include "../minishell.h"

extern t_ext	g_var;

int	use_redi_cmd(t_cmd *c)
{
	t_env	*e;

	e = g_var.env;
	if (ft_strcmp(c->cmd[0], "export") == 0
		&& ft_strcmp(c->cmd[0], "unset") == 0)
		return (g_var.qmark);
	if (c->flag == 0 || 1 < c->flag)
		g_var.qmark = use_builtin(c, e);
	if (g_var.qmark != -2)
		exit(1);
	else
	{
		g_var.qmark = 0;
		g_var.qmark = run_cmd(c->cmd);
	}
	return (g_var.qmark);
}

int	ft_redirect_R(t_cmd *c)
{
	pid_t	pid;
	int		out;
	int		status;

	pid = fork();
	g_var.pid[g_var.pnum++] = pid;
	if (pid == 0)
	{
		out = open(c[1].cmd[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (check_open(out, c) == 1)
			return (1);
		dup2(out, STDOUT_FILENO);
		if (use_redi_cmd(c) == 1)
			exit(0);
		close(out);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	return (SUCCESS);
}
