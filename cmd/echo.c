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

int	vaild_env_name(char c)
{
	if (!(('0' <= c && c <= '9')
		|| ('a' <= c && c <= 'z')
		|| ('A' <= c && c <= 'Z')
		|| (c == '_')))
		return (0);
	return (1);
}

int echo_env(char *cmd, t_env *env, int j)
{
	int	i;
	char env_name[256];

	i = 0;
	if (vaild_env_name(cmd[j]) == 0)
	{
		printf("$");
		return (j - 1);
	}
	while (cmd[j] && vaild_env_name(cmd[j]) == 1)
		env_name[i++] = cmd[j++];
	env_name[i] = '\0';
	while (env && env->next)
	{
		if (ft_strcmp(env->name, env_name) == 0)
		{
			printf("%s", env->content);
			return (j - 1);
		}
		env = env->next;
	}
	return (j - 1);
}

int	ft_echo(t_env *env, char **cmd)
{
	int	i;
	int	j;
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
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '\"')
			{
				while (cmd[i][++j] != '\"')
				{
					if (cmd[i][j] == '$')
						j = echo_env(cmd[i], env, ++j);
					else
						printf("%c", cmd[i][j]);
				}
			}
			else if(cmd[i][j] == '\'')
			{
				while (cmd[i][++j] != '\'')
					printf("%c", cmd[i][j]);
			}
			else if (cmd[i][j] == '$')
				j = echo_env(cmd[i], env, ++j);
			else
				printf("%c", cmd[i][j]);

			j++;
		}
		printf(" ");
		i++;
	}
	if (option_n == 0)
		printf("\n");
	return (0);
}
