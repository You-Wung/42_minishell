#include "../minishell.h"

int	use_redirect(t_cmd *c)
{
	int	result;

	result = -2;
	if (c->flag == 2)
		result = ft_redirect_R(c);
	if (c->flag == 3)
		result = ft_redirect_L(c);
	if (c->flag == 4)
		result = ft_redirect_RR(c);
	if (c->flag == 5)
		result = ft_redirect_LL(c);
	return (result);
}

int	use_builtin(t_cmd *c, t_env *e)
{
	int	result;

	result = -2;
	if (ft_strcmp(c->cmd[0], "exit") == 0)
		result = ft_exit(c->cmd, c->flag);
	if (ft_strcmp(c->cmd[0], "cd") == 0)
		result = ft_cd(e, c->cmd);
	if (ft_strcmp(c->cmd[0], "echo") == 0)
		result = ft_echo(e, c->cmd);
	if (ft_strcmp(c->cmd[0], "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp(c->cmd[0], "env") == 0)
		result = ft_env(e);
	if (ft_strcmp(c->cmd[0], "export") == 0)
		result = ft_export(e, c->cmd);
	if (ft_strcmp(c->cmd[0], "unset") == 0)
		result = ft_unset(&e, c->cmd);
	return (result);
}
