#include "../minishell.h"

extern t_ext	g_var;

int	use_redi_cmd(t_cmd *c)
{
	t_env	*e;

	e = g_var.env;
	if (ft_strcmp(c->cmd[0], "export") == 0
		&& ft_strcmp(c->cmd[0], "unset") == 0)
		return (g_var.qmark);
	if (c->flag == 0 || 1 < c->flag)
		g_var.qmark = use_builtin(c, e);
	if (g_var.qmark == -2)
	{
		g_var.qmark = 0;
		if (c->cmd[0])
			g_var.qmark = run_cmd(c->cmd, g_var.env);
	}
	return (g_var.qmark);
}

int	use_cmd(t_cmd *c)
{
	t_env	*e;

	e = g_var.env;
	if (ft_strcmp(c->cmd[0], "export") == 0
		|| ft_strcmp(c->cmd[0], "unset") == 0
		|| (c->flag != 0 && ft_strcmp(c->cmd[0], "exit") == 0))
		return (g_var.qmark);
	if (c->flag <= 1)
	{
		if (ft_strcmp(c->cmd[0], "exit") == 0)
			c->flag = 1;
		g_var.qmark = use_builtin(c, e);
	}
	if (2 <= c->flag && c->flag <= 5)
		g_var.qmark = use_redirect(c);
	if (g_var.qmark == -2)
	{
		g_var.qmark = 0;
		if (c->cmd[0])
			g_var.qmark = run_cmd(c->cmd, g_var.env);
	}
	return (g_var.qmark);
}

int	is_have_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
