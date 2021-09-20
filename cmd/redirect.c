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
		return (0);
	if (flag == L_RE)
		file = open(str, O_RDONLY);
	if (file < 0)
	{
		printf("minishell: %s: no such file or directory\n", str);
		return (-1);
	}
	return (file);
}

int	redi_child(t_cmd *c, int lapp, int s_re, int in, int out)
{
	int	file;

	if (lapp != -2 || c[s_re - 1].flag == L_APP)
	{
		if (c[s_re - 1].flag == L_APP)
			lapp = s_re;
		redi_L_APP(c[lapp].cmd[0], 1);
		file = open("./cmd/user_tmp", O_RDONLY);
		in = file;
	}
	file = redi_one(c[s_re].cmd[0], c[s_re - 1].flag);
	if (file == -1)
		exit(1);
	if (c[s_re - 1].flag == L_RE || c[s_re - 1].flag == L_APP)
	{
		if (out != 0)
			dup2(out, STDOUT_FILENO);
		dup2(file, STDIN_FILENO);
		if (s_re == lapp)
			dup2(in, STDIN_FILENO);
	}
	else if (c[s_re - 1].flag == R_APP || c[s_re - 1].flag == R_RE)
	{
		if (in != 0)
			dup2(in, STDIN_FILENO);
		dup2(file, STDOUT_FILENO);
	}
	g_var.qmark = use_redi_cmd(c);
	close(file);
	return (g_var.qmark);
}

int	check_L(t_cmd *c, int *in, int *out, int s_re)
{
	int		file;
	int		n;
	int		lapp;

	n = 0;
	*in = 0;
	*out = 0;
	lapp = -2;
	// printf("%d_flag=%d>>>>>%s<<<<<<\n", n,c[n - 1].flag, c[n].cmd[0]);
	while (++n < s_re)
	{
		// printf("%d_flag=%d>>>>>%s<<<<<<\n", n,c[n - 1].flag, c[n].cmd[0]);
		file = redi_one(c[n].cmd[0], c[n - 1].flag);
		if (file == -1)
			return (-1);
		if (c[n - 1].flag == L_APP)
			lapp = n;
		if (c[n - 1].flag == L_RE)
			*in = file;
		else if (c[n - 1].flag == R_RE || c[n - 1].flag == R_APP)
			*out = file;
	}
	return (lapp);
}

int	ft_redirect(t_cmd *c, int s_re)
{
	pid_t	pid;
	int		lapp;
	int		in;
	int		out;

	lapp = check_L(c, &in, &out, s_re);
	if (lapp == -1)
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
		g_var.qmark = redi_child(c, lapp, s_re, in, out);
		if (in != 0)
			close(in);
		if (out != 0)
			close(out);
		exit (g_var.qmark);
	}
	else if (pid > 0)
		redi_parent(pid, c);
	return (g_var.qmark);
}
