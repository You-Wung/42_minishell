#include "../minishell.h"

char	*spl_name(char *cmd)
{
	char	*name;
	int		k;

	k = 0;
	while (cmd[k] != '=')
		k++;
	name = malloc(sizeof(char) * k + 1);
	k = -1;
	while (cmd[++k] != '=')
		name[k] = cmd[k];
	name[++k] = '\0';
	return (name);
}

char	*make_tmp(t_env *e, char *cmd, char **tmp, int j)
{
	char	*name;
	int		i;

	name = spl_name(cmd);
	i = 0;
	while (i < j)
	{
		if (ft_strcmp(name, tmp[i]) == 0)
			return (NULL);
		i++;
	}
	while (e)
	{
		if (ft_strcmp(e->name, name) == 0)
			e->print = 0;
		e = e->next;
	}
	return (name);
}

void	main_env(t_env *env, t_cmd *c, char **tmp, int size)
{
	int	j;
	int	i;

	j = 0;
	print_env(env);
	while (tmp[j])
	{
		i = size;
		while (0 < --i)
		{
			if (ft_strcmp(c->cmd[i], "env") != 0)
			{
				if (ft_strcmp(spl_name(c->cmd[i]), tmp[j]) == 0)
				{
					j++;
					printf("%s\n", c->cmd[i]);
					break ;
				}
			}
		}
	}
}

int	check_error_env(char *str, int flag)
{
	char	*buf;

	buf = "";
	if (str[0] == '=')
	{
		buf = ft_strjoin(buf, "minishell: env: ");
		buf = ft_strjoin(buf, str);
		buf = ft_strjoin(buf, ": Invalid argument\n");
		write(2, buf, ft_strlen(buf));
		return (1);
	}
	else if (equl_num(str) == 0 && flag == 1)
	{
		buf = ft_strjoin(buf, "minishell: env: ");
		buf = ft_strjoin(buf, str);
		buf = ft_strjoin(buf, ": error\n");
		write(2, buf, ft_strlen(buf));
		return (127);
	}
	return (0);
}

int	ft_env(t_env *env, t_cmd *c)
{
	char	*tmp[256];
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	while (c->cmd[++i])
	{
		if (ft_strcmp(c->cmd[i], "env") != 0)
		{
			size = check_error_env(c->cmd[i], 1) != 0;
			if (size != 0)
				return (size);
			tmp[j] = make_tmp(env, c->cmd[i], tmp, j);
			if (tmp[j] != NULL)
				j++;
		}
	}
	tmp[j] = NULL;
	size = 0;
	while (c->cmd[size])
		size++;
	main_env(env, c, tmp, size);
	return (0);
}
