#include "../minishell.h"

extern t_ext	g_var;

void	redi_parent(pid_t pid, t_cmd *c)
{
	int		wstatus;

	waitpid(pid, &wstatus, 0);
	g_var.qmark = WEXITSTATUS(wstatus);
	print_error(g_var.qmark, c->cmd[0]);
}

void	in_out(int *in, int *out, int flag)
{
	if (flag == 1 && *in != 0)
		dup2(*in, STDIN_FILENO);
	if (flag == 1 && *out != 0)
		dup2(*out, STDOUT_FILENO);
	if (flag == 0 && *in != 0)
		close(*in);
	if (flag == 0 && *out != 0)
		close(*out);
}
