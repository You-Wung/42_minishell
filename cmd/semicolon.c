#include "../minishell.h"

extern t_ext var;

int ft_semicolon(t_cmd *c)
{
	while (var.size_se > 0)
	{
		c->flag = 0;
		exec_cmd(c++);
		var.size_se--;
	}
	if (c->cmd[0] != NULL)
	{
		c->flag = 0;
		exec_cmd(c);
	}
	return (SUCCESS);
}
