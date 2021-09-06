#include "../minishell.h"

extern t_ext	g_var;

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

int	ft_unset2(t_env **env, char **cmd, char *find)
{
	if (vaild_env(cmd[1]) == 0)
	{
		printf("minishell: %s: not a valid identifier.\n", cmd[1]);
		return (1);
	}
	if (find == NULL)
		return (SUCCESS);
	if ((*env)->next == NULL && ft_strcmp((*env)->name, find) == 0)
	{
		free((*env));
		return (SUCCESS);
	}
	return (2);
}

int	ft_unset(t_env **env, char **cmd)
{
	t_env	*tmp;
	char	*find;
	int		result;

	find = cmd[1];
	result = ft_unset2(env, cmd, find);
	if (result != 2)
		return (result);
	while ((*env) && (*env)->next)
	{
		if (ft_strcmp((*env)->next->name, find) == 0)
		{
			tmp = (*env)->next;
			(*env)->next = (*env)->next->next;
			if (tmp->flag)
				free(tmp);
			return (SUCCESS);
		}
		*env = (*env)->next;
	}
	return (SUCCESS);
}
