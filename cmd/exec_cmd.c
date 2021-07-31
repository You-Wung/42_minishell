#include "../minishell.h"

extern t_ext var;

/* result 값은 $? */
int	use_builtin(t_cmd *c, t_env *e)
{
	int	result;
	
	result = -1;
	/* flag */
	// printf("\n\nflag === %d\n", c->flag);
	// if (c->flag == 1)
	// 	ft_pipe();
	// if (c->flag == 2)
	// 	ft_redirect_R(c->cmd, c->cmd[0]);
	// if (c->flag == 3)
	// 	ft_redirect_L(c->cmd, c->cmd[0]);
	// if (c->flag == 4)
	// 	ft_redirect_RR(c->cmd, c->cmd[0]);
	// if (c->flag == 5)
	// 	ft_redirect_LL(c->cmd, c->cmd[0]);

	if (ft_strcmp(c->cmd[0], "exit") == 0)
		result = ft_exit(c->cmd);
	if (ft_strcmp(c->cmd[0], "cd") == 0)
		result = ft_cd(e, c->cmd);
	if (ft_strcmp(c->cmd[0], "echo") == 0)
		result = ft_echo(c->cmd);
	if (ft_strcmp(c->cmd[0], "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp(c->cmd[0], "env") == 0)
		result = ft_env(e);
	if (ft_strcmp(c->cmd[0], "export") == 0)
		result = ft_export(e, c->cmd);
	if (ft_strcmp(c->cmd[0], "unset") == 0)
		result = ft_unset(e, c->cmd);
	return (result);
}

void	run_cmd(char **cmd)
{
    const char *path;
    
	path = ft_strjoin("/bin/", cmd[0]);
	execve(path, cmd, NULL);
	path = ft_strjoin("/usr/local/bin/", cmd[0]);
	execve(path, cmd, NULL);
	path = ft_strjoin("/usr/bin/", cmd[0]);
	execve(path, cmd, NULL);
	path = ft_strjoin("/user/sbin/", cmd[0]);
	execve(path, cmd, NULL);
	path = ft_strjoin("/sbin/", cmd[0]);
	execve(path, cmd, NULL);
	printf("Error: command does not exist.\n");
	exit(1);
}

void	exec_cmd(t_cmd *c)
{
	int		pid;
	int		status;
	int		result;
	t_env	*e;

	e = var.env;
	result = use_builtin(c, e);
	if (result == -1)
	{
		if (c->cmd[0])
		{
			pid = fork();
			if (pid > 0)
				waitpid(pid, &status, 0);
			else if (pid == 0)
				run_cmd(c->cmd);
		}
	}
}