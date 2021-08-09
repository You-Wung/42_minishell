#include "minishell.h"

extern t_ext var;

static void	input(char *env, t_env *buf)
{
	static int	size;
	int			i;
	int			j;
	
	//var.size_env = ++size;
	i = 0;
	while (env[i] != '=')
		i++;
	j = -1;
	while (++j < i)
		buf->name[j] = env[j];
	j = -1;
	while (env[++i])
		buf->content[++j] = env[i];
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
		e[j].next = &e[j + 1];
	i = -1;
	while (env[++i])
		input(env[i], &e[i]);
	var.env = e;
	i = -1;
	/* --- 체크용 --- */
	// while (++i < var.size_env)
	// {
	// 	printf("NAME : %s\n",var.env[i].name);
	// 	printf("CONT : %s\n",var.env[i].content);
	// 	if (e[i].next)
	// 		printf("NEXT : %s\n\n",var.env[i].next->name);
	// }
}