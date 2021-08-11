#include "../minishell.h"

int ft_semicolon(t_cmd *c)
{
	c->flag = 0;
	exec_cmd(c);
	if (++c != NULL)
		exec_cmd(c);
	return (SUCCESS);
}
