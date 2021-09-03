#include "../minishell.h"

extern t_ext	g_var;

void	ft_charjoin(int j, char *cmd, char **buf)
{
	char	c[2];

	c[0] = cmd[j];
	c[1] = '\0';
	*buf = ft_strjoin(*buf, c);
}

int	cha_env(char **buf, char *cmd, t_env *env, int j)
{
	int		i;
	char	env_name[256];

	i = 0;
	if (vaild_env_name(cmd[j]) == 0)
	{
		if ('0' <= cmd[j] && cmd[j] <= '9')
			return (j);
		*buf = ft_strjoin(*buf, "$");
		return (j - 1);
	}
	while (cmd[j] && vaild_env_name(cmd[j]) == 1)
		env_name[i++] = cmd[j++];
	env_name[i] = '\0';
	while (env && env->next)
	{
		if (ft_strcmp(env->name, env_name) == 0)
		{
			*buf = ft_strjoin(*buf, env->content);
			return (j - 1);
		}
		env = env->next;
	}
	return (j - 1);
}

int	cha_cmd(char **buf, char *cmd, t_env *env, int j)
{
	if (cmd[j] == '\"')
	{
		while (cmd[++j] != '\"')
		{
			if (cmd[j] == '$')
				j = cha_env(buf, cmd, env, ++j);
			else
				ft_charjoin(j, cmd, buf);
		}
	}
	else if (cmd[j] == '\'')
	{
		while (cmd[++j] != '\'')
			ft_charjoin(j, cmd, buf);
	}
	else if (cmd[j] == '$')
		j = cha_env(buf, cmd, env, ++j);
	else
		ft_charjoin(j, cmd, buf);
	return (j);
}

void	cha_chlid(int i, t_cmd *c, int fd[2])
{
	char	*buff;
	int		j;
	int		size;

	j = -1;
	buff = "";
	while (c->cmd[i][++j])
		j = cha_cmd(&buff, c->cmd[i], g_var.env, j);
	size = ft_strlen(buff);
	write(fd[1], buff, size);
	exit(size);
}

void	cha_print(int i, t_cmd *c)
{
	int		size;
	char	buf[256];
	pid_t	pid;
	int		fd[2];
	int		wstatus;

	pipe(fd);
	pid = fork();
	g_var.pid[g_var.pnum++] = pid;
	if (pid == 0)
		cha_chlid(i, c, fd);
	else if (pid > 0)
	{
		waitpid(pid, &wstatus, 0);
		close(fd[1]);
		read(fd[0], buf, 256);
		size = WEXITSTATUS(wstatus);
		buf[size] = '\0';
		free(c->cmd[i]);
		if (ft_strcmp(buf, "\0") != 0)
			c->cmd[i] = ft_strjoin("", buf);
		else
			c->cmd[i] = ft_strdup("");
		close(fd[0]);
	}
}
