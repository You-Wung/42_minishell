#include "../minishell.h"

extern t_ext	g_var;

int	check_option_n(char *str)
{
	if (*str == '-')
		str++;
	else
		return (0);
	while (*str)
	{
		if (*str == 'n')
			str++;
		else
			return (0);
	}
	return (1);
}

int	cha_env(char **buf, char *cmd, t_env *env, int j)
{
	int		i;
	char	env_name[256];

	i = 0;
	if (vaild_env_name(cmd[j]) == 0)
	{
		*buf = ft_strjoin(*buf, "$");
		return (j - 1);
	}
	while (cmd[j] && vaild_env_name(cmd[j]) == 1)
		env_name[i++] = cmd[j++];
	env_name[i] = '\0';
	while (env && env->next)
	{
		if (ft_strcmp(env->name, env_name) == 0)
		{
			*buf = ft_strjoin(*buf, env->content);
			return (j - 1);
		}
		env = env->next;
	}
	return (j - 1);
}

int	cha_cmd(char **buf, char *cmd, t_env *env, int j)
{
	if (cmd[j] == '\"')
	{
		while (cmd[++j] != '\"')
		{
			if (cmd[j] == '$')
				j = cha_env(&(*buf), cmd, env, ++j);
			else
				ft_charjoin(j, cmd, &(*buf));
		}
	}
	else if (cmd[j] == '\'')
	{
		while (cmd[++j] != '\'')
			ft_charjoin(j, cmd, &(*buf));
	}
	else if (cmd[j] == '$')
		j = cha_env(&(*buf), cmd, env, ++j);
	else
		ft_charjoin(j, cmd, &(*buf));
	return (j);
}

void	cha_print(int i, t_env *env, char **cmd)
{
	int		j;
	char	*buf;

	buf = "";
	j = -1;
	while (cmd[i][++j])
		j = cha_cmd(&buf, cmd[i], env, j);
	cmd[i] = buf;
}

int	ft_echo(char **cmd)
{
	int	i;
	int	option_n;

	i = 1;
	option_n = 0;
	while (cmd[i] && check_option_n(cmd[i]) == 1)
	{
		option_n = 1;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[++i])
			printf(" ");
	}
	if (option_n == 0)
		printf("\n");
	return (0);
}
