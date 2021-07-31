#include "../minishell.h"

int	print_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		printf("declare -x %s=%s\n", env->name, env->content);
		env = env->next;
	}
	return (SUCCESS);
}

int	vaild_env(char **tmp)
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

void	put_env(t_env *env, char *tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (tmp[0] == '\"' || tmp[0] == '\'')
		j = 1;
	while (i < ft_strlen(tmp) - (j * 2))
	{			
		env->content[i] = tmp[i + j];
		i++;
	}
	env->content[i] = '\0';
}

int	add_env(t_env *env, char **tmp)
{
	int		i;
	t_env	*e;

	while (env && env->next)
	{
		if (ft_strcmp(env->name, tmp[0]) == 0)
		{
			put_env(env, tmp[1]);
			return (1);
		}
		env = env->next;
	}
	e = (t_env *)malloc(sizeof(t_env));
	e->next = NULL;
	i = -1;
	while (tmp[0][++i])
		e->name[i] = tmp[0][i];
	put_env(e, tmp[1]);
	while (env && env->next)
		env = env->next;
	env->next = e;
	return (1);
}

int	ft_export(t_env *env, char **cmd)
{
	int		i;
	char	**tmp;

	i = 1;
	if (cmd[1] == NULL)
	{
		print_env(env);
		return (SUCCESS);
	}
	while (cmd[i])
	{
		tmp = ft_split(cmd[i], '=');
		if (vaild_env(tmp) == 0)
		{
			printf("minichell: not a valid identifier.\n");
			return (ERROR);
		}
		add_env(env, tmp);
		i++;
	}
	return (0);
}
