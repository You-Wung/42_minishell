#include "../minishell.h"

extern t_ext	g_var;

int	check_path_env(char **path_env, char **cmd)
{
	int			i;
	const char	*path;

	if (path_env == NULL)
	{
		printf("minishell: PATH dose not exist.\n");
		return (1);
	}
	i = -1;
	while (path_env[++i])
	{
		path_env[i] = ft_strjoin(path_env[i], "/");
		path = ft_strjoin(path_env[i], cmd[0]);
		execve(path, cmd, g_var.n_env);
	}
	return (0);
}

int	run_cmd(char **cmd, t_env *env)
{
	char		**path_env;

	execve(cmd[0], cmd, g_var.n_env);
	while (env && env->next)
	{
		if (ft_strcmp(env->name, "PATH") == 0)
			path_env = ft_split(env->content, ':');
		env = env->next;
	}
	if (check_path_env(path_env, cmd) == 0)
		printf("minishell: %s: command does not exist.\n", cmd[0]);
	return (127);
}

int	exec_cmd(t_cmd *c)
{
	t_env	*e;

	e = g_var.env;
	if (c->flag == 0)
		g_var.qmark = use_builtin(c, e);
	else if (c->flag == 1)
		g_var.qmark = ft_pipe(c);
	else if (c->flag == 6)
		g_var.qmark = ft_semicolon(c);
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
