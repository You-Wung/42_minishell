#include "minishell.h"

/* unset */
int	ft_unset(t_env *env, char **cmd)
{
	t_env	*tmp;
	char	*name;

	name = cmd[1];
	if (name == NULL)
		return (SUCCESS);
	if (ft_strcmp(env->content, name) == 0)
	{
		free(env);
		return (0);
	}
	while (env && env->next)
	{
		if (ft_strcmp(env->next->name, name) == 0)
		{
			tmp = env->next->next;
			free(env->next);
			env->next = tmp;
			return (0);
		}
		env = env->next;
	}
	return (0);
}
