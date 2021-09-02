#include "../minishell.h"

extern t_ext	g_var;

int	use_redirect(t_cmd *c)
{
	int	result;

	result = -2;
	if (c->flag == 2)
		result = ft_redirect_R(c);
	if (c->flag == 3)
		result = ft_redirect_L(c);
	if (c->flag == 4)
		result = ft_redirect_RR(c);
	if (c->flag == 5)
		result = ft_redirect_LL(c);
	return (result);
}

int	cha_env(char **buf, char *cmd, t_env *env, int j)
{
	int		i;
	char	env_name[256];

	i = 0;
	if (vaild_env_name(cmd[j]) == 0)
	{
		*buf = ft_strjoin(*buf, "$");
		return (j - 1);
	}
	while (cmd[j] && vaild_env_name(cmd[j]) == 1)
		env_name[i++] = cmd[j++];
	env_name[i] = '\0';
	while (env && env->next)
	{
		if (ft_strcmp(env->name, env_name) == 0)
		{
			*buf = ft_strjoin(*buf, env->content);
			return (j - 1);
		}
		env = env->next;
	}
	return (j - 1);
}

int	rr(char **buf, char *cmd, t_env *env, int j)
{
	char	c[2];

	c[0] = cmd[j];
	c[1] = '\0';
	if (cmd[j] == '\"')
	{
		while (cmd[++j] != '\"')
		{
			if (cmd[j] == '$')
				j = cha_env(&(*buf), cmd, env, ++j);
			else
				*buf = ft_strjoin(*buf, c);
		}
	}
	else if (cmd[j] == '\'')
	{
		while (cmd[++j] != '\'')
			*buf = ft_strjoin(*buf, c);
	}
	else if (cmd[j] == '$')
		j = cha_env(&(*buf), cmd, env, ++j);
	else
		*buf = ft_strjoin(*buf, c);
	return (j);
}

void	cha_print(int i, t_env *env, char **cmd)
{
	int		j;
	char	*buf;

	buf = "";
	j = -1;
	while (cmd[i][++j])
	{
		j = rr(&buf, cmd[i], env, j);
	}
	cmd[i] = buf;
}

int	exec_cmd(t_cmd *c)
{
	t_env	*e;
	int		i;

	e = g_var.env;
	if (c->flag == 1)
		g_var.qmark = ft_pipe(c);
	else if (c->flag == 6)
		g_var.qmark = ft_semicolon(c);
	else if (c->flag == 0)
		g_var.qmark = use_builtin(c, e);
	else
		g_var.qmark = use_redirect(c);
	i = 0;
	while (c->cmd[++i])
		cha_print(i, e, c->cmd);
	if (g_var.qmark == -2)
	{
		g_var.qmark = 0;
		if (c->cmd[0])
			not_builtin(c);
	}
	return (g_var.qmark);
}
