#include "../minishell.h"

extern t_ext	g_var;

int	use_redirect(t_cmd *c)
{
	int	result;

	result = -2;
	if (c->flag == 2)
		result = ft_redirect_R(c);
	if (c->flag == 3)
		result = ft_redirect_L(c);
	if (c->flag == 4)
		result = ft_redirect_RR(c);
	if (c->flag == 5)
		result = ft_redirect_LL(c);
	return (result);
}

int	use_builtin(t_cmd *c, t_env *e)
{
	int	result;

	result = -2;
	if (ft_strcmp(c->cmd[0], "exit") == 0)
		result = ft_exit(c->cmd, c->flag);
	if (ft_strcmp(c->cmd[0], "cd") == 0)
		result = ft_cd(e, c->cmd);
	if (ft_strcmp(c->cmd[0], "echo") == 0)
		result = ft_echo(e, c->cmd);
	if (ft_strcmp(c->cmd[0], "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp(c->cmd[0], "env") == 0)
		result = ft_env(e);
	if (ft_strcmp(c->cmd[0], "export") == 0)
		result = ft_export(e, c->cmd);
	if (ft_strcmp(c->cmd[0], "unset") == 0)
		result = ft_unset(e, c->cmd);
	return (result);
}

int	run_cmd(char **cmd)
{
	const char	*path;

	execve(cmd[0], cmd, g_var.n_env);
	path = ft_strjoin("/bin/", cmd[0]);
	execve(path, cmd, g_var.n_env);
	path = ft_strjoin("/usr/local/bin/", cmd[0]);
	execve(path, cmd, g_var.n_env);
	path = ft_strjoin("/usr/bin/", cmd[0]);
	execve(path, cmd, g_var.n_env);
	path = ft_strjoin("/user/sbin/", cmd[0]);
	execve(path, cmd, g_var.n_env);
	path = ft_strjoin("/sbin/", cmd[0]);
	execve(path, cmd, g_var.n_env);
	printf("Error: %s: command does not exist.\n", cmd[0]);
	return (1);
}

void	not_builtin(t_cmd *c)
{
	int		status;
	int		pid;
	int		qmark;

	qmark = 0;
	pid = fork();
	g_var.pid[g_var.pnum++] = pid;
	if (pid > 0)
		waitpid(pid, &status, 0);
	else if (pid == 0)
	{
		g_var.qmark = run_cmd(c->cmd);
		//printf("Qmakr changed %d\n",g_var.qmark);
		exit(0);
	}
}

int	exec_cmd(t_cmd *c)
{
	t_env	*e;

	e = g_var.env;
	if (c->flag == 1)
		g_var.qmark = ft_pipe(c);
	if (c->flag == 6)
		g_var.qmark = ft_semicolon(c);
	else if (c->flag == 0)
		g_var.qmark = use_builtin(c, e);
	else
		g_var.qmark = use_redirect(c);
	if (g_var.qmark == -2)
	{
		g_var.qmark = 0;
		if (c->cmd[0])
			not_builtin(c);
	}
	return (g_var.qmark);
}
