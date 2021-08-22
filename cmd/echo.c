#include "../minishell.h"

t_ext	g_var;

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

void	echo_env(t_env *env, char *env_name)
{
	int	i;

	i = -1;
	if (ft_strcmp(env_name, "$?") == 0)
	{
		printf("%d", g_var.qmark);
		g_var.qmark = 0;
		return ;
	}
	while (env_name[(++i) + 1])
		env_name[i] = env_name[i + 1];
	env_name[i] = '\0';
	while (env && env->next)
	{
		if (ft_strcmp(env->name, env_name) == 0)
		{
			printf("%s", env->content);
			return ;
		}
		env = env->next;
	}
}

void	echo_env_plus(t_env *env, char *tmp)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(tmp) - 2)
	{			
		tmp[i] = tmp[i + 1];
		i++;
	}
	tmp[i] = '\0';
	echo_env(env, tmp);
}

void	echo_str(char *tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (tmp[0] == '\"' || tmp[0] == '\'')
	{
		j = 1;
		while (i < (int)ft_strlen(tmp) - (j * 2))
		{			
			printf("%c", tmp[i + j]);
			i++;
		}
	}
	else
		printf("%s", tmp);
}

int	ft_echo(t_env *env, char **cmd)
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
		if (cmd[i][0] == '$')
			echo_env(env, cmd[i]);
		else if (cmd[i][0] == '\"' && cmd[i][1] == '$')
			echo_env_plus(env, cmd[i]);
		else
			echo_str(cmd[i]);
		if (cmd[i + 1] && cmd[i + 1][0] != '\0')
			printf(" ");
		i++;
	}
	if (option_n == 0)
		printf("\n");
	return (0);
}
