#include "../minishell.h"

extern t_ext var;

int	ft_redirect_L(t_cmd *c)
{
	pid_t	pid;
	int		in;
	int		status;

	pid = fork();
	var.pid[var.pnum++] = pid;
	if (pid == 0)
	{
		in = open(c[1].cmd[0], O_RDONLY);
		if (in < 0)
		{
			printf("minishell: no such file or directory: %s\n", c[1].cmd[0]);
			return (1);
		}
		if (c[1].cmd[1])
		{
			close(in);
			return (1);
		}
		var.writing = 1;
		dup2(in, STDIN_FILENO);
		run_cmd(c[0].cmd);
		close(in);
		var.writing = 0;
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	return (SUCCESS);
}
