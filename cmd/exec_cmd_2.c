#include "../minishell.h"

extern t_ext	g_var;

void	notbui_child(t_cmd *c, int *fd)
{
	int		i;
	char	*buf;
	char	buff[4];

	buf = ft_itoa(run_cmd(c->cmd, g_var.env));
	i = -1;
	while (buf[++i])
		buff[i] = buf[i];
	buff[++i] = '\0';
	write(fd[1], buff, ft_strlen(buff));
	exit(0);
}

void	not_builtin(t_cmd *c)
{
	int		pid;
	int		fd[2];
	int		status;
	char	buff[4];

	if (pipe(fd) == -1)
	{
		perror("pipe\n");
		exit(0);
	}
	pid = fork();
	g_var.pid[g_var.pnum++] = pid;
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		close(fd[1]);
		read(fd[0], buff, 4);
		close(fd[0]);
		if (buff[0] != '\0')
			g_var.qmark = ft_atoi(buff);
	}
	else if (pid == 0)
		notbui_child(c, fd);
}

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
	int	i;

	result = -2;
	if (ft_strcmp(c->cmd[0], "export") == 0)
		result = ft_export(e, c->cmd);
	if (ft_strcmp(c->cmd[0], "unset") == 0)
		result = ft_unset(&e, c->cmd);
	i = 0;
	while (c->cmd[++i])
		cha_print(i, e, c->cmd);
	if (ft_strcmp(c->cmd[0], "echo") == 0)
		result = ft_echo(c->cmd);
	if (ft_strcmp(c->cmd[0], "exit") == 0)
		result = ft_exit(c->cmd, c->flag);
	if (ft_strcmp(c->cmd[0], "cd") == 0)
		result = ft_cd(e, c->cmd);
	if (ft_strcmp(c->cmd[0], "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp(c->cmd[0], "env") == 0)
		result = ft_env(e);
	return (result);
}
