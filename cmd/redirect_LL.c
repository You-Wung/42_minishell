#include "../minishell.h"

int	ft_redirect_LL(t_cmd *c)
{
	pid_t	pid;
	int		in;
	int		status;
	char	*buf;
	char	**del;

	pid = fork();
	if (pid == 0)
	{
		in = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (in < 0)
			return (ERROR);
		while(1)
		{
			buf = readline(" > ");
			if (buf)
			{
		        write(in, buf, ft_strlen(buf));
				write(in, "\n", 1);
			}
			buf[ft_strlen(buf)] = '\0';
			if (ft_strcmp(buf, c[1].cmd[0]) == 0)
				break ;
			free(buf);
		}
		close(in);

		in = open("tmp", O_RDONLY);
		if (in < 0)
		{
			printf("minishell: no such file or directory\n");
			return (ERROR);
		}
		if (c[1].cmd[1])
		{
			close(in);
			exit(0);
		}
		dup2(in, STDIN_FILENO);
		run_cmd(c[0].cmd);
		close(in);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		del[0] = "rm";
		del[1] = "tmp";
		del[2] = NULL;
		run_cmd(del);
	}
	return (0);
}
