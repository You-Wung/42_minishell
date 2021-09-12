#include "../minishell.h"

int	vaild_env_name(char c)
{
	if (!('a' <= c && c <= 'z')
		&& !('A' <= c && c <= 'Z')
		&& !(c == '_'))
		return (0);
	return (1);
}

int	vaild_env(char *c)
{
	int	i;

	i = 0;
	if (vaild_env_name(c[i]) == 0)
		return (0);
	while (c[++i])
		if (c[i] == '?')
			return (0);
	return (1);
}

int	equl_num(char *c)
{
	int	num;

	num = 0;
	while (*c)
	{
		if (*c == '=')
			num++;
		c++;
	}
	return (num);
}


int	ft_env(t_env *env, t_cmd *c)
{
	int		i;

	i = 0;
	while (c->cmd[++i])
	{
		if (ft_strcmp(c->cmd[i], "env") != 0)
		{
			if (ft_strcmp(c->cmd[i], "=") == 0)
			{
				printf("minishell: env: =: Invalid argument\n");
				return (1);
			}
			else if (equl_num(c->cmd[i]) == 0)
			{
				printf("minishell: env: %s: error.\n", c->cmd[i]);
				return (127);
			}
		}
	}

	while (env && env->next)
	{
		printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
	if (env)
		printf("%s=%s\n", env->name, env->content);


	// i = 0;
	// while (c->cmd[++i])
	// 	if (ft_strcmp(c->cmd[i], "env") != 0)
	// 	{
			
	// 		printf("%s\n", c->cmd[i]);
	// 	}

	return (0);
}
