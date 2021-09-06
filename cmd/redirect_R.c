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
	if (g_var.qmark == -2)
	{
		g_var.qmark = 0;
		if (c->cmd[0])
			g_var.qmark = run_cmd(c->cmd, g_var.env);
	}
	return (g_var.qmark);
}

void	re_R_child(t_cmd *c)
{
	int	out;

	out = open(c[1].cmd[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (check_open(out, c) == 1)
		exit (1);
	dup2(out, STDOUT_FILENO);
	g_var.qmark = use_redi_cmd(c);
	close(out);
	exit(g_var.qmark);
}

int	ft_redirect_R(t_cmd *c)
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
		re_R_child(c);
	else if (pid > 0)
	{
		waitpid(pid, &wstatus, 0);
		g_var.qmark = WEXITSTATUS(wstatus);
		if (g_var.qmark == 127)
			printf("minishell: %s: command not found.\n", c[0].cmd[0]);
	}
	return (g_var.qmark);
}
