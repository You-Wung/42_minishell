#include "../minishell.h"

int	make_oldpwd(t_env *env, char *cwd)
{
	t_env	*e;
	char	*name;
	int		i;

	name = "OLDPWD";
	e = (t_env *)malloc(sizeof(t_env));
	e->next = NULL;
	i = -1;
	while (name[++i])
		e->name[i] = name[i];
	e->name[i] = '\0';
	i = -1;
	while (cwd[++i])
		e->content[i] = cwd[i];
	e->content[i] = '\0';
	while (env && env->next)
		env = env->next;
	env->next = e;
	return (1);
}

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
			i = -1;
			while (cwd[++i])
				env->content[i] = cwd[i];
			env->content[i] = '\0';
			return (SUCCESS);
		}
		env = env->next;
	}
	make_oldpwd(env, cwd);
	return (SUCCESS);
}

int	move_env_path(t_env *env, char *env_name)
{
	put_oldpwd(env);
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

int	move_oldpwd(t_env *env)
{
	char	move[256];
	int		i;

	while (env && env->next)
	{
		if (ft_strcmp(env->name, "OLDPWD") == 0)
		{
			i = -1;
			while (env->content[++i])
				move[i] = env->content[i];
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
	return (ERROR);
}

int	ft_cd(t_env *env, char **cmd)
{
	int		i;

	if (cmd[1] == NULL || ft_strcmp(cmd[1], "~") == 0)
		return (move_env_path(env, "HOME"));
	if (ft_strcmp(cmd[1], "-") == 0)
		return (move_oldpwd(env));
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
		put_oldpwd(env);
		if (chdir(cmd[1]) != 0)
		{
			printf("minishell: No such file or directory.\n");
			return (1);
		}
	}
	return (0);
}
