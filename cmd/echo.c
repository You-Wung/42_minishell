#include "../minishell.h"

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
		else
			printf("%s", cmd[i]);
		if (cmd[i + 1] && cmd[i + 1][0] != '\0')
			printf(" ");
		i++;
	}
	if (option_n == 0)
		printf("\n");
	return (0);
}
