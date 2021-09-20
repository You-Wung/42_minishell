#include "../minishell.h"

extern t_ext	g_var;

void	redi_parent(pid_t pid, t_cmd *c)
{
	int		wstatus;

	waitpid(pid, &wstatus, 0);
	g_var.qmark = WEXITSTATUS(wstatus);
	print_error(g_var.qmark, c->cmd[0]);
}
