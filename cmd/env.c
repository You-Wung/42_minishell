#include "../minishell.h"

int	ft_env(t_env *env)
{
	while (env && env->next)
	{
		printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
	if (env)
		printf("%s=%s\n", env->name, env->content);
	return (0);
}
