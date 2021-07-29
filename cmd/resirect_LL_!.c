#include "minishell.h"

/* redirect << */
// 수정필요
int	ft_redirect_LL(char **cmd, char *file)
{
	pid_t	pid;
	int		fd[2];
	int		in;
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		in = open(file, O_RDONLY | O_APPEND);
		if (in < 0)
		{
			printf("minishell: no such file or directory: %s\n", file);
			return (ERROR);
		}
		dup2(in, 0);
		run_cmd(cmd);
		close(in);
	}
	else if (pid > 0)
		wait(&status);
	return (0);
}
