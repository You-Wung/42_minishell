#include "../minishell.h"

int	ft_unset(t_env *env, char **cmd)
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
			// free(env->next);
			env->next = tmp;
			return (SUCCESS);
		}
		env = env->next;
	}
	return (SUCCESS);
}
