#include "../minishell.h"

int	ft_pwd(void)
{
	char	cwd[256];

	if (getcwd(cwd, 256))
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
		return (1);
}
