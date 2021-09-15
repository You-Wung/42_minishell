#include "minishell.h"

extern t_ext	g_var;

static void	input(char *env, t_env *buf)
{
	int			i;
	int			j;

	i = 0;
	while (env[i] != '=')
		i++;
	j = -1;
	while (++j < i)
		buf->name[j] = env[j];
	j = -1;
	while (env[++i])
		buf->content[++j] = env[i];
	buf->flag = 0;
	buf->print = 1;
}

void	init_env(char **env)
{
	t_env	*e;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	e = malloc(sizeof(t_env) * i);
	e[i - 1].next = NULL;
	j = -1;
	while (++j < i - 1)
		e[j].next = &(e[j + 1]);
	i = -1;
	while (env[++i])
		input(env[i], &e[i]);
	g_var.env = e;
}
