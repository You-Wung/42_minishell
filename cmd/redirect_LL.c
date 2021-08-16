#include "../minishell.h"

extern t_ext var;

int	get_user_tmp(t_cmd *c)
{
	char	*buf;
	int		in;

	in = open("%%user_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (in < 0)
		return (ERROR);
	while (1)
	{
		buf = readline(" > ");
		if (ft_strcmp(buf, c[1].cmd[0]) == 0)
			break ;
		if (buf)
		{
			write(in, buf, ft_strlen(buf));
			write(in, "\n", 1);
		}
		free(buf);
	}
	close(in);
	return (SUCCESS);
}

int	use_user_tmp(t_cmd *c)
{
	int		in;

	in = open("%%user_tmp", O_RDONLY);
	if (in < 0)
	{
		printf("minishell: no such file or directory\n");
		return (1);
	}
	dup2(in, STDIN_FILENO);
	run_cmd(c[0].cmd);
	close(in);
	return (SUCCESS);
}

int	del_user_tmp(void)
{
	pid_t	pid;
	int		status;
	char	**del;

	pid = fork();
	var.pid[var.pnum++] = pid;
	if (pid < 0)
	{
		printf("fork error\n");
		return (-1);
	}
	if (pid == 0)
	{
		del = ft_split("rm ./%%user_tmp", ' ');
		run_cmd(del);
	}
	if (pid > 0)
		waitpid(pid, &status, 0);
	return (0);
}

int	ft_redirect_LL(t_cmd *c)
{
	pid_t	pid;
	int		status;

	pid = fork();
	var.pid[var.pnum++] = pid;
	if (pid < 0)
	{
		printf("fork error\n");
		return (ERROR);
	}
	if (pid == 0)
	{
		if (get_user_tmp(c) != SUCCESS)
			return (1);
		if (use_user_tmp(c) != SUCCESS)
			return (1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (del_user_tmp() == -1)
			return (-1);
	}
	return (0);
}
