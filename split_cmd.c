#include "minishell.h"

static int	is_sep(char c)
{
	if (c == '|' || c == '>'
		|| c == '<' || c == ';')
	{
		if (c == '<')
			return (3);
		if (c == '>')
			return (2);
		return (1);
	}
	return (0);
}
/* | > < ; 기준으로 커맨드 몇개로 잘릴까 */
int	count_cmd(char *input)
{
	int		rt;
	int		i;
	char	c;

	if (input[0] == '\0')
		return (0);
	c = 0;
	rt = 1;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '\"' || input[i] == '`')
		{
			if (c == input[i])
				c = 0;
			else if (!c)
				c = input[i];
		}
		if (is_sep(input[i]) && !c)
			rt++;
	}
	printf("count_cmd returns %d\n\n",rt);
	return (rt);
}

void	fill_cmd(t_cmd *c, char *input)
{
	int	size;
	int	i;

	i = -1;
	while (++i < size && input)
	{
		input = init_cmd(&c[i], input);
		printf("cmd[0] %s\n",c[i].cmd[0]);
		printf("cmd[1] %s\n",c[i].cmd[1]);
		printf("flag : %d\n\n",c[i].flag);
	}
}
