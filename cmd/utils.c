#include "../minishell.h"

int	vaild_env_name(char c)
{
	if (!('a' <= c && c <= 'z')
		&& !('A' <= c && c <= 'Z')
		&& !(c == '_'))
		return (0);
	return (1);
}

void	ft_charjoin(int j, char *cmd, char **buf)
{
	char	c[2];

	c[0] = cmd[j];
	c[1] = '\0';
	*buf = ft_strjoin(*buf, c);
}
