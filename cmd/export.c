#include "../minishell.h"

extern t_ext	g_var;

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

void	free_2char(char **tmp)
{
	int	j;

	j = 0;
	while (tmp[j])
		free(tmp[j++]);
	free(tmp);
}

void	check_equl(int i, char **cmd, char **tmp)
{
	int		equl;
	int		k;
	char	*fre;
	char	*con;

	equl = equl_num(cmd[i]);
	if (equl != 1)
	{
		con = ft_strchr(cmd[i], '=');
		k = -1;
		while (++k < equl - 1)
		{
			fre = tmp[1];
			tmp[1] = ft_strjoin("=", tmp[1]);
			free(fre);
		}
	}
}

int	use_export(t_env *env, char **cmd, int i)
{
	char	**tmp;

	tmp = ft_split(cmd[i], '=');
	if (vaild_env(tmp[0]) == 0)
	{
		printf("minishell: %s: not a valid identifier.\n", cmd[i]);
		free_2char(tmp);
		return (1);
	}
	check_equl(i, cmd, tmp);
	if (ft_strcmp(tmp[0], cmd[i]) == 0)
	{
		free_2char(tmp);
		return (SUCCESS);
	}
	add_env(env, tmp);
	free_2char(tmp);
	return (2);
}

int	ft_export(t_env *env, char **cmd)
{
	int		i;
	int		result;
	int		re;

	i = 1;
	result = 0;
	if (cmd[i] == NULL)
	{
		while (env && env->next != NULL)
		{
			printf("declare -x %s=\"%s\"\n", env->name, env->content);
			env = env->next;
		}
		return (SUCCESS);
	}
	while (cmd[i])
	{
		re = use_export(env, cmd, i);
		if (re != SUCCESS)
			result = re;
		i++;
	}
	return (result);
}
