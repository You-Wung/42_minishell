#include "../minishell.h"

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

int	equl_num(char *c)
{
	int	num;

	num = 0;
	while (*c)
	{
		if (*c == '=')
			num++;
		c++;
	}
	return (num);
}

void	print_env(t_env *env)
{
	while (env && env->next)
	{
		if (env->print == 1)
			printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
	if (env && env->print == 1)
		printf("%d_%s=%s\n", env->print, env->name, env->content);
}

void	put_env(t_env *env, char *tmp)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	env->flag = 1;
	env->print = 1;
	if (tmp == NULL)
	{
		env->content[j] = '\0';
		return ;
	}
	while (i < (int)ft_strlen(tmp))
	{
		if (tmp[i] != '\"' || tmp[i] != '\'')
		{
			env->content[j] = tmp[i];
			j++;
		}
		i++;
	}
	env->content[i] = '\0';
}
