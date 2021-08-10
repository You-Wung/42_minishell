#include "../minishell.h"

extern t_ext var;

int	use_cmd(t_cmd *c)
{
	t_env	*e;

	e = var.env;
	if (ft_strcmp(c->cmd[0], "export") == 0
		&& ft_strcmp(c->cmd[0], "unset") == 0)
		return (var.qmark);
	if (c->flag <= 1)
		var.qmark = use_builtin(c, e);
	else
		var.qmark = use_redirect(c);
	if (var.qmark != -2)
		exit(1);
	else
	{
		var.qmark = 0;
		var.qmark = run_cmd(c->cmd);
	}
	return (var.qmark);
}

void	exec_pipe(t_cmd *c, int fd[2], int flags)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return ;
	}
	if (pid == 0)
	{
		if (flags == 1 || flags == 3)
		{
			if (dup2(fd[0], STDIN_FILENO) < 0)
				perror("dup2");
		}
		if (flags == 2 || flags == 3)
		{
			if (dup2(fd[1], STDOUT_FILENO) < 0)
				perror("dup2");
		}
		close(fd[0]);
		close(fd[1]);
		var.qmark = use_cmd(c);
	}
}

void	use_pipe(t_cmd *c, int size_pi, int (*fd)[2])
{
	int	temp_fd[2];
	int	i;
	int	j;

	i = 0;
	j = 0;
	exec_pipe(&c[j++], fd[0], 2);
	close(fd[i][1]);
	while (size_pi > 1 && i < size_pi - 1)
	{
		temp_fd[0] = fd[i][0];
		temp_fd[1] = fd[i + 1][1];
		exec_pipe(&c[j], temp_fd, 3);
		while (c[j].flag > 1)
			j++;
		j++;
		close(fd[i][0]);
		close(fd[++i][1]);
	}
	exec_pipe(&c[j], fd[i], 1);
	close(fd[i][0]);
}

int	ft_pipe(t_cmd *c, int size_pi)
{
	int	i;

	int (*fd)[2];
	fd = malloc(sizeof(int) * 2 * size_pi);
	i = 0;
	while (i < size_pi)
		pipe(fd[i++]);
	use_pipe(c, size_pi, fd);
	return (0);
}
