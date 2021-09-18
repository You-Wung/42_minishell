#include "../minishell.h"

extern t_ext	g_var;

void	redi_L_APP(char *str, int flag)
{
	int		wstatus;
	int		pid;

	pid = fork();
	g_var.writing = 2;
	if (pid == 0)
		redi_L_APP_op(flag, str);
	else if (pid > 0)
	{
		g_var.writing = 3;
		waitpid(pid, &wstatus, 0);
		g_var.writing = 0;
	}
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
		redi_L_APP(str, 1);
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

void	redi_child(t_cmd *c, int n, int s_re)
{
	int	file;

	file = redi_one(c[n].cmd[0], c[n - 1].flag);
	if (file == -1)
		exit(1);
	if (c[n - 1].flag == L_RE || c[n - 1].flag == L_APP)
		dup2(file, STDIN_FILENO);
	else if (c[n - 1].flag == R_APP || c[n - 1].flag == R_RE)
		dup2(file, STDOUT_FILENO);
	if (n == s_re)
		g_var.qmark = use_redi_cmd(c);
	close(file);
	exit(g_var.qmark);
}

int	check_L(t_cmd *c, int *in, int *out, int s_re)
{
	int		file;
	int		n;

	n = 0;
	*in = 0;
	*out = 0;
	while (++n < s_re)
	{
		file = redi_one(c[n].cmd[0], c[n - 1].flag);
		if (file == -1)
			return (-1);
		if (file != -1
			&& (c[n - 1].flag == L_RE || c[n - 1].flag == L_APP))
			*in = file;
		else if (file != -1
			&& (c[n - 1].flag == R_RE || c[n - 1].flag == R_APP))
			*out = file;
	}
	return (n);
}

int	ft_redirect(t_cmd *c, int s_re)
{
	pid_t	pid;
	int		n;
	int		in;
	int		out;

	n = check_L(c, &in, &out, s_re);
	if (n == -1)
		return (1);
	pid = fork();
	g_var.pid[g_var.pnum++] = pid;
	if (pid < 0)
	{
		printf("fork error\n");
		return (ERROR);
	}
	else if (pid == 0)
	{
		in_out(&in, &out, 1);
		redi_child(c, n, s_re);
		in_out(&in, &out, 0);
	}
	else if (pid > 0)
		redi_parent(pid, c);
	return (g_var.qmark);
}
