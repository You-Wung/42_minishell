#include "../minishell.h"

extern t_ext var;

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

/* result 값은 $? */
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

void	run_cmd(char **cmd)
{
	const char	*path;

	path = ft_strjoin("/bin/", cmd[0]);
	execve(path, cmd, NULL);
	path = ft_strjoin("/usr/local/bin/", cmd[0]);
	execve(path, cmd, NULL);
	path = ft_strjoin("/usr/bin/", cmd[0]);
	execve(path, cmd, NULL);
	path = ft_strjoin("/user/sbin/", cmd[0]);
	execve(path, cmd, NULL);
	path = ft_strjoin("/sbin/", cmd[0]);
	execve(path, cmd, NULL);
	printf("Error: %s: command does not exist.\n", cmd[0]);
	exit(1);
}

void	exec_cmd(t_cmd *c, int pipe)
{
	int		pid;
	int		status;
	int		result;
	t_env	*e;

	e = var.env;
	if (pipe != 1 && c->flag == 1)
		result = ft_pipe(c, var.size_pi);
	else if (c->flag == 0)
		result = use_builtin(c, e);
	else
		result = use_redirect(c);
	if (result == -2)
	{
		if (c->cmd[0])
		{
			pid = fork();
			if (pid > 0)
				waitpid(pid, &status, 0);
			else if (pid == 0)
				run_cmd(c->cmd);
		}
	}
}
