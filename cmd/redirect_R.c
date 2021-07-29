#include "minishell.h"

/* redirect > */
// file c[1].cmd[0]
int	ft_redirect_R(char **cmd, char *file)
{
	pid_t	pid;
	int		fd[2];
	int		out;
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (out < 0)
		{
			printf("minishell: no such file or directory: %s\n", file);
			return (ERROR);
		}
		dup2(out, 1);
		run_cmd(cmd);
		close(out);
	}
	else if (pid > 0)
		wait(&status);
	return (0);
}
