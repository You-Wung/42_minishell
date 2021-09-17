#include "../minishell.h"

extern t_ext	g_var;

void	check_path_env(char **path_env, char **cmd)
{
	int			i;
	const char	*path;

	if (path_env == NULL)
		return ;
	i = -1;
	while (path_env[++i])
	{
		path_env[i] = ft_strjoin(path_env[i], "/");
		path = ft_strjoin(path_env[i], cmd[0]);
		execve(path, cmd, g_var.n_env);
	}
}

void	print_error(int qmark, char *str)
{
	if (qmark == 127)
		printf("minishell: %s: command not found.\n", str);
	if (qmark == 126)
		printf("minishell: Permission denied\n");
}

static int	permission_check(char **cmd)
{
	open(cmd[0], O_RDWR);
	if (errno == EACCES)
		return (126);
	return (127);
}

int	run_cmd(char **cmd, t_env *env)
{
	char		**path_env;

	path_env = NULL;
	execve(cmd[0], cmd, g_var.n_env);
	while (env && env->next)
	{
		if (ft_strcmp(env->name, "PATH") == 0)
			path_env = ft_split(env->content, ':');
		env = env->next;
	}
	check_path_env(path_env, cmd);
	return (permission_check(cmd));
}

int	exec_cmd(t_cmd *c)
{
	t_env	*e;

	e = g_var.env;
	if (g_var.size_pi != 0)
		g_var.qmark = ft_pipe(c);
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
	if (g_var.sig_qmark)
		return (g_var.sig_qmark);
	return (g_var.qmark);
}
