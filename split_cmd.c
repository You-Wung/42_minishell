#include "minishell.h"

extern t_ext var;

static int	is_flag(char c)
{
	if (c == '|' || c == '>'
	|| c == '<' || c == ';')
		return (1);
	return (0);
}

static int	find_error(char *c)
{
	if ((*c == '|' && is_flag(*(c + 1)))
		|| (*c == ';' && is_flag(*(c + 1)))
		|| (is_flag(*c) && is_flag(*(c + 1) && is_flag(*(c - 1))))
		|| (is_flag(*c) && is_flag(*(c + 1) && is_flag(*(c - 1))))
		|| (*c == '>' && *(c + 1) == '<')
		|| (*c == '<' && *(c + 1) == '>'))
		return (ERROR);
	if (is_flag(*c))
	{
		if ((*c == '>' && *(c + 1) == '>')
			|| (*c == '<' && *(c + 1) == '<'))
			c += 2;
		else
			c++;
		while (*c == ' ')
			c++;
		if (*c && is_flag(*c))
			return (ERROR);
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
		if (find_error(&input[i]) == ERROR)
			return (ERROR);
		if (is_flag(input[i]) && !c)
			rt++;
		if ((input[i] == '>' && input[i + 1] == '>')
		|| (input[i] == '<' && input[i + 1] == '<'))
			i++;
	}
	printf("count_cmd returns %d\n\n",rt);
	return (rt);
}

void	fill_cmd(t_cmd *c, char *input)
{
	int	size;
	int	i;

	i = -1;
	size = count_cmd(input);
	while (input && ++i < size)
	{
		input = init_cmd(&c[i], input);
		if (c[i].cmd[0])
			printf("cmd[0] %s\n",c[i].cmd[0]);
		printf("======================\n");
		if (c[i].cmd[1])
			printf("cmd[1] %s\n",c[i].cmd[1]);
		printf("======================\n");
		if (c[i].flag)
			printf("flag : %d\n",c[i].flag);
		printf("\n");
	}
	i = -1;
	var.size_pi = 0;
	while (++i < size)
	{
		if (c[i].flag == PIPE)
			var.size_pi++;
	}
	//printf("size_pi : %d\n",var.size_pi);
}
