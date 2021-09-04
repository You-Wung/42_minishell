#include "minishell.h"

extern t_ext	g_var;

static int	comma_check(t_match *m)
{
	int	i;

	i = 0;
	if (m->comma % 2 == 1 && ++i)
		printf("quote\n");
	if (m->dcomma % 2 == 1 && ++i)
		printf("double quote\n");
	if (m->backtick % 2 == 1 && ++i)
		printf("backtick\n");
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
static int	count(char *input)
{
	t_match	m;
	int		rt;

	rt = 1;
	ft_memset(&m, 0, sizeof(t_match));
	while (*input && *input == ' ')
		input++;
	while (check_input(input, &m))
	{
		if (*input == '\'' && m.dcomma % 2 == 0 && m.backtick % 2 == 0)
			m.comma++;
		if (*input == '\"' && m.comma % 2 == 0 && m.backtick % 2 == 0)
			m.dcomma++;
		if (*input == '`' && m.dcomma % 2 == 0 && m.comma % 2 == 0)
			m.backtick++;
		if (*input == ' ' && *(input + 1) != ' ' && !is_flag(*(input + 1))
			&& !(m.comma % 2) && !(m.dcomma % 2) && !(m.backtick % 2))
			rt++;
		input++;
	}
	if (comma_check(&m) == ERROR)
		return (ERROR);
	return (rt);
}

static int	check_size(char *input)
{
	int	comma;
	int	rt;

	rt = 0;
	comma = 0;
	while (*input)
	{
		if ((*input == ' ' && !(comma % 2))
			|| (is_flag(*input) && !(comma % 2)))
			break ;
		if (*input == '\'' || *input == '\"' || *input == '`')
			comma++;
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
		//printf("_________SIGN_________\n");
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
	}
		//printf("_________SIGN2_________\n");
	return (input);
}

/*실제로 cmd에 인덱스 넣어주는과정*/
char	*init_cmd(t_cmd *c, char **input)
{
	int	size;
	int	i;

	i = 0;
	while ((*input)[i] && (*input)[i] == ' ')
		i++;
	if (is_flag(**input))
		edit_input(input);
	if (*input == NULL)
		return (NULL);
	size = count(*input);
	if (size == ERROR)
		return (NULL);
	c->cmd = (char **)malloc(sizeof(char *) * (size + 1));
	c->cmd[size] = NULL;
	//printf("_________SIGN3_________\n");
	return (input_cmd(c, *input, size));
}
