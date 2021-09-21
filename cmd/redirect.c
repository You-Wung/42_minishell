#include "../minishell.h"

extern t_ext	g_var;

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

void	close_in_out(t_redi *re)
{
	if (re[0].in != 0)
		close(re[0].in);
	if (re[0].out != 0)
		close(re[0].out);
}

void	redi_parent(pid_t pid, t_cmd *c)
{
	int		wstatus;

	waitpid(pid, &wstatus, 0);
	g_var.qmark = WEXITSTATUS(wstatus);
	print_error(g_var.qmark, c->cmd[0]);
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
		close_in_out(re);
		exit (g_var.qmark);
	}
	else if (pid > 0)
		redi_parent(pid, c);
	return (g_var.qmark);
}
