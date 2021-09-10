#include "../minishell.h"

extern t_ext	g_var;

int	ft_pipe(t_cmd *c)
{
	int	i;

	int (*fd)[2];
	g_var.size_pi++;
	fd = malloc(sizeof(int) * 2 * g_var.size_pi);
	i = 0;
	while (i < g_var.size_pi)
		pipe(fd[i++]);
	use_pipe(c, fd);
	free(fd);
	return (0);
}
