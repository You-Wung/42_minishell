#include "../minishell.h"

int	move_env_path(t_env *env, char *env_name)
{
	while (env && env->next)
	{
		if (ft_strcmp(env->name, env_name) == 0)
		{
			if (chdir(env->content) != 0)
			{
				printf("minishell: No such file or directory.\n");
				return (ERROR);
			}
			return (SUCCESS);
		}
		env = env->next;
	}
	printf("minishell: %s not set.\n", env_name);
	return (ERROR);
}

int	ft_cd(t_env *env, char **cmd)
{
	int		i;

	if (cmd[1] == NULL)
		return (move_env_path(env, "HOME"));
	if (cmd[1][0] == '$')
	{
		i = -1;
		while (cmd[1][(++i) + 1])
			cmd[1][i] = cmd[1][i + 1];
		cmd[1][i] = '\0';
		return (move_env_path(env, cmd[1]));
	}
	else
	{
		if (chdir(cmd[1]) != 0)
		{
			printf("minishell: No such file or directory.\n");
			return (1);
		}
	}
	return (0);
}
