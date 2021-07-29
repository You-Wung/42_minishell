#include "minishell.h"

int	put_oldpwd(t_env *env)
{
	char	cwd[256];
	int		i;

	if (getcwd(cwd, 256) == NULL)
		return (ERROR);
	while (env && env->next)
	{
		if (ft_strcmp(env->name, "OLDPWD") == 0)
		{
			i = 0;
			while (cwd[i])
			{
				env->content[i] = cwd[i];
				i++;
			}
			env->content[i] = '\0';
			return (SUCCESS);
		}
		env = env->next;
	}
	printf("minishell: OLDPWD not set.\n");
	return (ERROR);
}

int	move_home(t_env *env, char **cmd)
{
	put_oldpwd(env);
	while (env && env->next)
	{
		if (ft_strcmp(env->name, "HOME") == 0)
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
	printf("minishell: HOME not set.\n");
	return (ERROR);
}

int	move_oldpwd(t_env *env, char **cmd)
{
	char	move[256];
	int		i;

	while (env && env->next)
	{
		if (ft_strcmp(env->name, "OLDPWD") == 0)
		{
			i = 0;
			while (env->content[i])
			{
				move[i] = env->content[i];
				i++;
			}
			move[i] = '\0';
			put_oldpwd(env);
			if (chdir(move) != 0)
			{
				printf("minishell: No such file or directory.\n");
				return (ERROR);
			}
			return (SUCCESS);
		}
		env = env->next;
	}
	printf("minishell: OLDPWD not set.\n");
	return (ERROR);
}

int	ft_cd(t_env *env, char **cmd)
{
	if (cmd[1] == NULL)
		return (move_home(env, cmd));
	if (ft_strcmp(cmd[1], "-") == 0)
		return (move_oldpwd(env, cmd));
	else
	{
		put_oldpwd(env);
		if (chdir(cmd[1]) != 0)
		{
			printf("minishell: No such file or directory.\n");
			return (1);
		}
	}
	return (0);
}
