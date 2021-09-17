#include "../minishell.h"

extern t_ext	g_var;

void	redi_L_APP(char *str)
{
	int		file;
	char	*buf;

	file = open("./cmd/user_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		buf = readline(" > ");
		if (ft_strcmp(buf, str) == 0)
			break ;
		if (buf)
		{
			write(file, buf, ft_strlen(buf));
			write(file, "\n", 1);
		}
		free(buf);
	}
	close(file);
}

int	redi_one(char *str, int flag)
{
	int	file;

	file = 0;
	if (flag == R_APP)
		file = open(str, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (flag == R_RE)
		file = open(str, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (flag == L_APP)
	{
		redi_L_APP(str);
		file = open("./cmd/user_tmp", O_RDONLY);
	}
	if (flag == L_RE)
		file = open(str, O_RDONLY);
	if (file < 0)
	{
		printf("minishell: %s: no such file or directory\n", str);
		return (-1);
	}
	return (file);
}

void	redi_child(t_cmd *c, int n, int in)
{
	int	file;

	file = redi_one(c[n].cmd[0], c[n - 1].flag);
	if (file == -1)
		exit(1);
	if (c[n - 1].flag == L_RE || c[n - 1].flag == L_APP)
		dup2(file, STDIN_FILENO);
	else if (c[n - 1].flag == R_APP || c[n - 1].flag == R_RE)
	{
		if (in != 0)
			dup2(in, STDIN_FILENO);
		dup2(file, STDOUT_FILENO);
	}
	g_var.qmark = use_redi_cmd(c);
	close(file);
	if (in != 0)
		close(in);
	exit(g_var.qmark);
}

int	check_L(t_cmd *c, int n)
{
	int		file;

	file = redi_one(c[n].cmd[0], c[n - 1].flag);
	if (file != -1 && (c[n - 1].flag == L_RE || c[n - 1].flag == L_APP))
		return (file);
	return (0);
}

int	ft_redirect(t_cmd *c)
{
	pid_t	pid;
	int		wstatus;
	int		n;
	int		in;

	n = 0;
	in = 0;
	while (++n < g_var.size_re)
		in = check_L(c, n);
	pid = fork();
	g_var.pid[g_var.pnum++] = pid;
	if (pid < 0)
	{
		printf("fork error\n");
		return (ERROR);
	}
	else if (pid == 0)
		redi_child(c, n, in);
	else if (pid > 0)
	{
		waitpid(pid, &wstatus, 0);
		g_var.qmark = WEXITSTATUS(wstatus);
		print_error(g_var.qmark, c->cmd[0]);
	}
	return (SUCCESS);
}
