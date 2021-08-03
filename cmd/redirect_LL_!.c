#include "../minishell.h"

/* redirect << */
// 수정필요
int	ft_redirect_LL(t_cmd *c)
{
	pid_t	pid;
	// int		fd[2];
	int		in;
	int		status;

	// pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		in = open(c[1].cmd[0], O_RDWR | O_APPEND);
		if (in < 0)
		{
			printf("minishell: no such file or directory: %s\n", c[1].cmd[0]);
			return (ERROR);
		}
		dup2(in, STDIN_FILENO);
		run_cmd(c[0].cmd);
		close(in);
	}
	else if (pid > 0)
		wait(&status);
	return (0);
}
