#include "../minishell.h"

extern t_ext var;

void	use_cmd(t_cmd *c)
{
	int		result;
	t_env	*e;

	e = var.env;
	if (c->flag == 0)
		result = use_builtin(c, e);
	else
		result = use_redirect(c);
	if (result == -1)
		run_cmd(c->cmd);
}

void use_pipe(t_cmd *c, int fd[2], int flags)
{
	pid_t pid;
	
	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid > 0)
		return ;
	if (pid == 0)
	{
		if (flags == 1 || flags == 3)
		{
			if (dup2(fd[0], STDIN_FILENO) < 0)
				perror("1::dup2");
		}
		if (flags == 2 || flags == 3)
		{
			if (dup2(fd[1], STDOUT_FILENO) < 0)
				perror("2::dup2");
		}
		close(fd[0]);
		close(fd[1]);
		use_cmd(c);
	}
}

int	ft_pipe(t_cmd *c)
{
	int i;
	int	j;
	int cnt = 1;
	int (*fd)[2];
	int temp_fd[2];

	fd = malloc(sizeof(int) * 2 * cnt);
	i = 0;
	while (i < cnt)
		pipe(fd[i++]);

	i = 0;
	j = 0;
	use_pipe(&c[j], fd[0], 2);
	j++;
	close(fd[i][1]);
	while (i < cnt - 1)
	{
		temp_fd[0] = fd[i][0];
		temp_fd[1] = fd[i + 1][1];
		use_pipe(&c[j++], temp_fd, 3);
		close(fd[i][0]);
		close(fd[++i][1]);
	}
	use_pipe(&c[j], fd[i], 1);
	close(fd[i][0]);

	int status;
	while (wait(&status) > 0)
		;
	return (0);
}
