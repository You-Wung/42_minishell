#include "../minishell.h"

extern t_ext	g_var;

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
		result = ft_unset(&e, c->cmd);
	return (result);
}

void	notbui_child(t_cmd *c, int *fd)
{
	int		i;
	char	*buf;
	char	buff[4];

	buf = ft_itoa(run_cmd(c->cmd, g_var.env));
	i = -1;
	while (buf[++i])
		buff[i] = buf[i];
	buff[++i] = '\0';
	write(fd[1], buff, ft_strlen(buff));
	exit(0);
}

void	not_builtin(t_cmd *c)
{
	int		pid;
	int		fd[2];
	int		status;
	char	buff[4];

	if (pipe(fd) == -1)
	{
		perror("pipe\n");
		exit(0);
	}
	pid = fork();
	g_var.pid[g_var.pnum++] = pid;
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		close(fd[1]);
		read(fd[0], buff, 4);
		close(fd[0]);
		if (buff[0] != '\0')
			g_var.qmark = ft_atoi(buff);
	}
	else if (pid == 0)
		notbui_child(c, fd);
}

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

	path_env = NULL;
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
