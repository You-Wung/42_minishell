#include "../minishell.h"

extern t_ext	g_var;

int	unset_env(t_env *env, char **cmd)
{
	t_env	*tmp;
	char	*find;

	find = cmd[1];
	if (find == NULL)
		return (SUCCESS);
	if (env->next == NULL && ft_strcmp(env->name, find) == 0)
	{
		free(env);
		return (SUCCESS);
	}
	while (env && env->next)
	{
		if (ft_strcmp(env->next->name, find) == 0)
		{
			tmp = env->next->next;
			env->next = tmp;
			return (SUCCESS);
		}
		env = env->next;
	}
	return (SUCCESS);
}

int	env_size(t_env *env)
{
	int	size;

	size = 0;
	while (env && env->next)
	{
		env = env->next;
		size++;
	}
	return (size);
}

int	ft_unset(t_env *env, char **cmd)
{
	char	**tmp;
	char	*nenv;
	int		size;
	int		i;

	if (unset_env(env, cmd) == SUCCESS)
	{
		size = env_size(env);
		tmp = malloc(sizeof(char *) * (size + 1));
		i = 0;
		while (env)
		{
			nenv = ft_strjoin(env->name, "=");
			nenv = ft_strjoin(nenv, env->content);
			tmp[i] = nenv;
			i++;
			env = env->next;
		}
		tmp[i] = NULL;
		g_var.n_env = tmp;
	}
	return (SUCCESS);
}
