#include "../minishell.h"

extern t_ext	g_var;

void	not_builtin(t_cmd *c)
{
	int	pid;
	int	wstatus;

	pid = fork();
	g_var.pid[g_var.pnum++] = pid;
	if (pid > 0)
	{
		waitpid(pid, &wstatus, 0);
		g_var.qmark = WEXITSTATUS(wstatus);
	}
	else if (pid == 0)
	{
		g_var.qmark = run_cmd(c->cmd, g_var.env);
		print_error(g_var.qmark, c->cmd[0]);
		exit(g_var.qmark);
	}
}

int	use_redirect(t_cmd *c)
{
	int	result;
	int	s_re;
	int	i;

	s_re = 0;
	i = 0;
	while (c[i].flag != 1 && c[i].flag != 0)
	{
		if (2 <= c[i].flag && c[i].flag <= 5)
			s_re++;
		i++;
	}
	result = -2;
	if (c->flag == R_RE || c->flag == L_RE
		|| c->flag == R_APP || c->flag == L_APP)
		result = ft_redirect(c, s_re);
	return (result);
}

int	use_echo(int result, t_cmd *c)
{
	int	pid;
	int	wstatus;

	pid = fork();
	g_var.pid[g_var.pnum++] = pid;
	if (pid > 0)
	{
		waitpid(pid, &wstatus, 0);
		result = WEXITSTATUS(wstatus);
	}
	else if (pid == 0)
	{
		result = ft_echo(c->cmd);
		exit(result);
	}
	return (result);
}

int	use_env(int result, t_cmd *c, t_env *env)
{
	int	pid;
	int	wstatus;

	pid = fork();
	g_var.pid[g_var.pnum++] = pid;
	if (pid > 0)
	{
		waitpid(pid, &wstatus, 0);
		result = WEXITSTATUS(wstatus);
	}
	else if (pid == 0)
	{
		result = ft_env(env, c);
		exit(result);
	}
	return (result);
}

int	use_builtin(t_cmd *c, t_env *e)
{
	int	result;
	int	i;

	result = -2;
	i = -1;
	while (c->cmd[++i])
		cha_print(i, c);
	if (ft_strcmp(c->cmd[0], "export") == 0)
		result = ft_export(e, c->cmd);
	else if (ft_strcmp(c->cmd[0], "unset") == 0)
		result = ft_unset(&e, c->cmd);
	else if (ft_strcmp(c->cmd[0], "exit") == 0)
		result = ft_exit(c->cmd, c->flag);
	else if (ft_strcmp(c->cmd[0], "pwd") == 0)
		result = ft_pwd();
	else if (ft_strcmp(c->cmd[0], "env") == 0)
		result = use_env(result, c, e);
	else if (ft_strcmp(c->cmd[0], "cd") == 0)
		result = ft_cd(e, c->cmd);
	else if (ft_strcmp(c->cmd[0], "echo") == 0)
		result = use_echo(result, c);
	return (result);
}
