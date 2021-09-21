#include "../minishell.h"

extern t_ext	g_var;

void	redi_L_APP_op(int flag, char *str, t_redi *re)
{
	int		file;
	char	*buf;
	int		i;
	int		wri;

	wri = 1;
	i = 0;
	if (flag == 1)
		file = open("./cmd/user_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		buf = readline(" > ");
		if (!buf)
			printf("%c[1A %c[3C", 27, 27);
		if (flag == 0)
		{
			wri = 0;
			if (!buf || ft_strcmp(buf, str) == 0)
				exit(0);
		}
		else
		{
			if (re[0].lapp == 1)
				wri = 0;
			if (i == re[0].i - 1)
				wri = 0;
			if (ft_strcmp(buf, re[0].str[i]) == 0)
				i++;
			if (!buf || i == re[0].i)
				exit(0);
		}
		if (buf && flag == 1 && wri == 0)
		{
			write(file, buf, ft_strlen(buf));
			write(file, "\n", 1);
		}
		free(buf);
	}
	if (flag == 1)
		close(file);
}

void	redi_L_APP(char *str, int flag, t_redi *re)
{
	int		wstatus;
	int		pid;

	pid = fork();
	g_var.writing = 2;
	if (pid == 0)
		redi_L_APP_op(flag, str, re);
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
		if (g_var.size_pi == 0)
			printf("minishell: %s: no such file or directory\n", str);
		return (-1);
	}
	return (file);
}

int	redi_child(t_cmd *c, t_redi *re, int s_re)
{
	int	file;

	if (re[0].lapp != -2 || c[s_re - 1].flag == L_APP)
	{
		if (c[s_re - 1].flag == L_APP)
		{
			re[0].str[re[0].i++] = c[s_re].cmd[0];
			re[0].lapp = s_re;
		}
		re[0].str[re[0].i] = NULL;
		redi_L_APP(c[re[0].lapp].cmd[0], 1, re);
		file = open("./cmd/user_tmp", O_RDONLY);
		re[0].in = file;
	}
	file = redi_one(c[s_re].cmd[0], c[s_re - 1].flag);
	if (file == -1)
		exit(1);
	if (c[s_re - 1].flag == L_RE || c[s_re - 1].flag == L_APP)
	{
		if (re[0].out != 0)
			dup2(re[0].out, STDOUT_FILENO);
		dup2(file, STDIN_FILENO);
		if (s_re ==re[0].lapp)
			dup2(re[0].in, STDIN_FILENO);
	}
	else if (c[s_re - 1].flag == R_APP || c[s_re - 1].flag == R_RE)
	{
		if (re[0].in != 0)
			dup2(re[0].in, STDIN_FILENO);
		dup2(file, STDOUT_FILENO);
	}
	g_var.qmark = use_redi_cmd(c);
	close(file);
	return (g_var.qmark);
}

int	check_L(t_cmd *c, t_redi *re, int s_re)
{
	int		file;
	int		n;

	n = 0;
	while (++n < s_re)
	{
		file = redi_one(c[n].cmd[0], c[n - 1].flag);
		if (file == -1)
			return (-1);
		if (c[n - 1].flag == L_APP)
		{
			re[0].lapp = n;
			re[0].str[re[0].i++] = c[n].cmd[0];
		}
		if (c[n - 1].flag == L_RE)
			re[0].in = file;
		else if (c[n - 1].flag == R_RE || c[n - 1].flag == R_APP)
			re[0].out = file;
	}
	return (0);
}

void	redi_init(t_redi *re)
{
	re[0].i = 0;
	re[0].in = 0;
	re[0].out = 0;
	re[0].lapp = -2;
}

int	ft_redirect(t_cmd *c, int s_re)
{
	pid_t	pid;
	t_redi	*re;

	re = malloc(sizeof(t_redi) * 1);
	redi_init(re);
	if (check_L(c, re, s_re) == -1)
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
		g_var.qmark = redi_child(c, re, s_re);
		if (re[0].in != 0)
			close(re[0].in);
		if (re[0].out != 0)
			close(re[0].out);
		exit (g_var.qmark);
	}
	else if (pid > 0)
		redi_parent(pid, c);
	return (g_var.qmark);
}
