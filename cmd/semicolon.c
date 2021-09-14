#include "../minishell.h"

extern t_ext	g_var;

int	ft_semicolon(t_cmd *c)
{
	//while (g_var.size_se > 0)
	//{
	//	c->flag = 0;
	//	g_var.qmark = exec_cmd(c++);
	//	g_var.size_se--;
	//}
	//if (c->cmd[0] != NULL)
	//{
	//	c->flag = 0;
	//	g_var.qmark = exec_cmd(c);
	//}
	if (c)
		return (g_var.qmark);
	return (g_var.qmark);
}
