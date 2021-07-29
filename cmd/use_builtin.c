#include "minishell.h"

/* result 값은 $? */
int	use_builtin(t_env *env, cahr **cmd)
{
	int	result;

	result = 0;
	if (ft_strcmp(cmd[0], "exit") == 0)
		result = ft_exit(cmd);
	if (ft_strcmp(cmd[0], "cd") == 0)
		result = ft_cd(env, cmd);
	if (ft_strcmp(cmd[0], "echo") == 0)
		result = ft_echo(cmd);
	if (ft_strcmp(cmd[0], "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp(cmd[0], "env") == 0)
		result = ft_env(env);
	if (ft_strcmp(cmd[0], "export") == 0)
		result = ft_export(env, cmd);
	if (ft_strcmp(cmd[0], "unset") == 0)
		result = ft_unset(env, cmd);
	return (result);
}
