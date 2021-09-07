#include "../minishell.h"

extern t_ext	g_var;

int	use_cmd(t_cmd *c)
{
	t_env	*e;

	e = g_var.env;
	if (ft_strcmp(c->cmd[0], "export") == 0
		|| ft_strcmp(c->cmd[0], "unset") == 0
		|| ft_strcmp(c->cmd[0], "exit") == 0)
		return (g_var.qmark);
	if (c->flag <= 1)
		g_var.qmark = use_builtin(c, e);
	if (2 <= c->flag && c->flag <= 5)
		g_var.qmark = use_redirect(c);
	if (g_var.qmark == -2)
	{
		g_var.qmark = 0;
		if (c->cmd[0])
			g_var.qmark = run_cmd(c->cmd, g_var.env);
	}
	return (g_var.qmark);
}

void	exec_pipe2(t_cmd *c, int fd[2], int flags)
{
	if (flags == 1 || flags == 3)
	{
		if (ft_strcmp(c->cmd[0], "echo") != 0)
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
	g_var.qmark = 0;
	g_var.qmark = use_cmd(c);
}

void	exec_pipe(t_cmd *c, int fd[2], int flags)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	g_var.pid[g_var.pnum++] = pid;
	if (pid < 0)
		perror("fork");
	if (pid > 0)
	{
		waitpid(pid, &wstatus, 0);
		g_var.qmark = WEXITSTATUS(wstatus);
		return ;
	}
	if (pid == 0)
	{
		exec_pipe2(c, fd, flags);
		exit(g_var.qmark);
	}
}

int	check_flag_pipe(int j, t_cmd *c)
{
	if (2 <= c[j].flag && c[j].flag <= 5)
		j += 2;
	else
		j++;
	return (j);
}

void	use_pipe(t_cmd *c, int (*fd)[2])
{
	int	temp_fd[2];
	int	i;
	int	j;

	i = 0;
	j = 0;
	exec_pipe(&c[j], fd[i], 2);
	close(fd[i][1]);
	while (i < g_var.size_pi - 1)
	{
		g_var.qmark = 0;
		temp_fd[0] = fd[i][0];
		temp_fd[1] = fd[i + 1][1];
		exec_pipe(&c[j], temp_fd, 3);
		close(fd[i][0]);
		close(fd[++i][1]);
		if (g_var.qmark == 127)
			printf("minishell: %s: command not found.\n", c[j].cmd[0]);
		j = check_flag_pipe(j, c);
	}
	exec_pipe(&c[j], fd[i], 1);
	if (g_var.qmark == 127)
		printf("minishell: %s: command not found.\n", c[j].cmd[0]);
	close(fd[i][0]);
}
