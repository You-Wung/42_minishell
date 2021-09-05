#include "../minishell.h"

extern t_ext	g_var;

int	get_user_tmp(t_cmd *c)
{
	char	*buf;
	int		in;

	in = open(".%%user_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

void	use_user_tmp(t_cmd *c)
{
	int		in;

	in = open(".%%user_tmp", O_RDONLY);
	if (in < 0)
	{
		printf("minishell: no such file or directory\n");
		exit (1);
	}
	dup2(in, STDIN_FILENO);
	g_var.qmark = use_redi_cmd(c);
	close(in);
	exit (g_var.qmark);
}

int	del_user_tmp(void)
{
	pid_t	pid;
	int		status;
	char	**del;

	pid = fork();
	g_var.pid[g_var.pnum++] = pid;
	if (pid < 0)
	{
		printf("fork error\n");
		return (-1);
	}
	if (pid == 0)
	{
		del = ft_split("/bin/rm .%%user_tmp", ' ');
		execve("/bin/rm", del, g_var.n_env);
	}
	if (pid > 0)
		waitpid(pid, &status, 0);
	return (0);
}

int	ft_redirect_LL(t_cmd *c)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	g_var.pid[g_var.pnum++] = pid;
	if (pid < 0)
	{
		printf("fork error\n");
		return (ERROR);
	}
	if (pid == 0)
	{
		if (get_user_tmp(c) != SUCCESS)
			exit (1);
		use_user_tmp(c);
	}
	else if (pid > 0)
	{
		waitpid(pid, &wstatus, 0);
		g_var.qmark = WEXITSTATUS(wstatus);
		if (g_var.qmark == 127)
			printf("minishell: %s: command not found.\n", c[0].cmd[0]);
		if (del_user_tmp() == -1)
			return (-1);
	}
	return (0);
}
