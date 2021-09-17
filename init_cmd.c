#include "minishell.h"

extern t_ext	g_var;

static int	comma_check(t_match *m)
{
	int	i;

	i = 0;
	if (m->comma % 2 == 1 && ++i)
		printf("quote: ");
	if (m->dcomma % 2 == 1 && ++i)
		printf("double quote: ");
	if (!i)
		return (0);
	g_var.qmark = 1;
	return (ERROR);
}

/*
	따옴표, 쌍따옴표, 백틱 갯수가 안맞음에 따라
	에러코드를 뱉어야한다.
	이 함수에서 에러처리해줘야함.
*/
int	count(char *input)
{
	t_match	m;
	int		rt;

	rt = 1;
	ft_memset(&m, 0, sizeof(t_match));
	while (*input && *input == ' ')
		input++;
	while (check_input(input, &m))
	{
		set_comma_index(*input, &m);
		if (*input == ' ' && check_comma_index(m))
		{
			while (*input == ' ')
				input++;
			if (!is_flag(*input))
				rt++;
			if (*input == '\0')
				return (rt);
		}
		else
			input++;
	}
	if (comma_check(&m) == ERROR)
		return (ERROR);
	return (rt);
}

static int	check_size(char *input)
{
	t_match	m;
	int		rt;

	rt = 0;
	ft_memset(&m, 0, sizeof(t_match));
	while (*input)
	{
		if ((*input == ' ' && check_comma_index(m))
			|| (is_flag(*input) && check_comma_index(m)))
			break ;
		set_comma_index(*input, &m);
		rt++;
		input++;
	}
	return (rt);
}

static char	*input_cmd(t_cmd *c, char *input, int size)
{
	int		i;
	int		j;
	int		phrase;

	i = -1;
	j = 0;
	while (*input && *input == ' ')
		input++;
	while (++i < size && *input)
	{
		phrase = check_size(input);
		if (phrase == 0)
			break ;
		c->cmd[j] = (char *)malloc(phrase + 1);
		ft_strlcpy(c->cmd[j++], input, phrase);
		check_qmark(&(c->cmd[j - 1]));
		input += phrase;
		while (*input && *input == ' ')
			input++;
		input = set_flag(c, input, &j);
		if (ft_strcmp(c->cmd[0], "./minishell") == 0)
			return (NULL);
	}
	return (input);
}

/*실제로 cmd에 인덱스 넣어주는과정*/
char	*init_cmd(t_cmd *c, char **input)
{
	char	*tmp;
	int		size;
	int		i;

	i = 0;
	while ((*input)[i] && (*input)[i] == ' ')
		i++;
	size = count(*input);
	if (size == ERROR)
		return (NULL);
	if (ft_strchr(*input, '>') || ft_strchr(*input, '<'))
	{
		tmp = *input;
		*input = edit_input(input);
		if (*input == NULL)
			return (NULL);
		if (tmp != *input)
			g_var.fre = *input;
		size = count(*input);
	}
	c->cmd = (char **)malloc(sizeof(char *) * (size + 1));
	c->cmd[size] = NULL;
	return (input_cmd(c, *input, size));
}
