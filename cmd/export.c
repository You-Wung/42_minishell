#include "../minishell.h"

extern t_ext	g_var;

int	print_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		printf("declare -x %s=\"%s\"\n", env->name, env->content);
		env = env->next;
	}
	return (SUCCESS);
}

void	put_env(t_env *env, char *tmp)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < (int)ft_strlen(tmp))
	{
		if (tmp[i] != '\"' || tmp[i] != '\'')
		{
			env->content[j] = tmp[i];
			j++;
		}
		i++;
	}
	env->content[i] = '\0';
}

int	add_env(t_env *env, char **tmp)
{
	int		i;
	t_env	*e;
	t_env	*find;

	find = env;
	while (find && find->next != NULL)
	{
		if (ft_strcmp(find->name, tmp[0]) == 0)
		{
			put_env(find, tmp[1]);
			return (1);
		}
		find = find->next;
	}
	while (env && env->next->next != NULL)
		env = env->next;
	e = (t_env *)malloc(sizeof(t_env));
	e->next = env->next;
	i = -1;
	while (tmp[0][++i])
		e->name[i] = tmp[0][i];
	e->name[i] = '\0';
	put_env(e, tmp[1]);
	env->next = e;
	return (1);
}

static void	free_tmp(char ***tmp)
{
	int	i;

	i = 0;
	while ((*tmp)[i])
		free((*tmp)[i++]);
	free(*tmp);
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
		if (vaild_env(tmp[0]) == 0)
		{
			printf("minishell: %s: not a valid identifier.\n", cmd[i]);
			return (1);
		}
		if (ft_strcmp(tmp[0], cmd[i]) == 0)
			return (SUCCESS);
		add_env(env, tmp);
		free_tmp(&tmp);
		i++;
	}
	return (SUCCESS);
}
