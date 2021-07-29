#include "minishell.h"

int	print_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		printf("declare -x %s=%s\n", env->name, env->content);
		env = env->next;
	}
	if (env)
		printf("declare -x %s=%s\n", env->name, env->content);
	return (SUCCESS);
}

void	put_env(t_env *env, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (tmp[1][0] == '\"' || tmp[1][0] == '\'')
		j = 1;
	while (i < ft_strlen(tmp[1]) - (j * 2))
	{			
		env->content[i] = tmp[1][i + j];
		i++;
	}
	env->content[i] = '\0';
}

int	vaild_env(t_env *env, char **tmp)
{
	if (tmp[0] == NULL)
		return (0);
	if (!(('0' <= tmp[0][0] && tmp[0][0] <= '9')
		|| ('a' <= tmp[0][0] && tmp[0][0] <= 'z')
		|| ('A' <= tmp[0][0] && tmp[0][0] <= 'Z')
		|| (tmp[0][0] == '_')))
		return (0);
	return (1);
}

int	ft_export(t_env *env, char **cmd)
{
	int		i;
	char	**tmp;
	t_env	*make;

	if (cmd[1] == NULL)
	{
		print_env(env);
		return (SUCCESS);
	}
	tmp = ft_split(cmd[1], '=');
	if (vaild_env(env) == 0)
	{
		printf("minichell: not a valid identifier.\n");
		return (ERROR);
	}
	while (env && env->next)
	{
		if (ft_strcmp(env->name, tmp[0]) == 0)
		{
			put_env(env, tmp);
			return (1);
		}
		env = env->next;
	}
	/* add_env */
	return (0);
}
