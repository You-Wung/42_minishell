#include "../minishell.h"

extern t_ext	g_var;

void	exec_pipe(t_cmd *c, int fd[2], int flags)
{
	pid_t	pid;

	pid = fork();
	g_var.pid[g_var.pnum++] = pid;
	if (pid < 0)
		perror("fork");
	if (pid > 0)
		return ;
	if (pid == 0)
	{
		if (flags == 1 || flags == 2)
		{
			if (ft_strcmp(c->cmd[0], "echo") != 0)
				if (dup2(fd[0], STDIN_FILENO) < 0)
					perror("dup2");
		}
		if (flags == 2 | flags == 3)
		{
			if (dup2(fd[1], STDOUT_FILENO) < 0)
				perror("dup2");
		}
		close(fd[0]);
		close(fd[1]);
		exit(use_cmd(c));
	}
}

int	check_flag_pipe(int j, t_cmd *c)
{
	while (2 <= c[j].flag && c[j].flag <= 5)
		j++;
	j++;
	return (j);
}

int	use(t_cmd *c, int (*fd)[2], int i, int j)
{
	int	temp_fd[2];

	temp_fd[0] = fd[i][0];
	temp_fd[1] = fd[i + 1][1];
	exec_pipe(&c[j], temp_fd, 2);
	close(fd[i][0]);
	close(fd[i + 1][1]);
	return (check_flag_pipe(j, c));
}

void	use_pipe(t_cmd *c, int (*fd)[2])
{
	int	wstatus;
	int	i;
	int	j;

	i = 0;
	j = 0;
	exec_pipe(&c[j], fd[i], 3);
	close(fd[i][1]);
	j = check_flag_pipe(j, c);
	while (i < g_var.size_pi - 2)
		j = use(c, fd, i++, j);
	exec_pipe(&c[j], fd[i], 1);
	close(fd[i][0]);
	j = 0;
	while (wait(&wstatus) > 0)
		g_var.qmark = WEXITSTATUS(wstatus);
}
