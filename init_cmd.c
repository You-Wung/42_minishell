#include "minishell.h"

static int	comma_check(t_match *m)
{
	int	i;

	i = 0;
	if (m->comma % 2 == 1 && ++i)
		printf("quote %d\n", i);
	if (m->dcomma % 2 == 1 && ++i)
		printf("double quote");
	if (m->backtick % 2 == 1 && ++i)
		printf("backtick");
	if (!i)
		return (0);
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
		if (*input == ' ' && *(input + 1) != ' ' && *(input - 1) != ' '
			&& m.comma % 2 == 0 && m.dcomma % 2 == 0 && m.backtick % 2 == 0)
			rt++;
		input++;
	}
	if (comma_check(&m) == ERROR)
		return (ERROR);
	printf("[COUNT] ONE PHRASE SPLITED %d\n", rt);
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
		if ((*input == ' ' && comma % 2 == 0) || *input == '\0'
			|| *input == '<' || *input == '>' || *input == ';'
			|| *input == '|')
			break ;
		if (*input == '\'' || *input == '\"' || *input == '`')
			comma++;
		if (*input != ' ' && *input != '\0')
			rt++;
		input++;
	}
	if (rt != 0)
		printf("[CHECK SIZE] a word counted %d\n", rt);
	return (rt);
}

static char	*input_cmd(t_cmd *c, char *input, int size)
{
	int		i;
	int		j;
	int		phrase;

	i = -1;
	j = 0;
	printf("input_cmd : %s\n", input);
	while (*input && *input == ' ')
		input++;
	while (++i < size && *input)
	{
		phrase = check_size(input);
		if (phrase == 0)
			break ;
		c->cmd[j] = (char *)malloc(phrase + 1);
		ft_strlcpy(c->cmd[j++], input, phrase);
		input += phrase;
		while (*input && *input == ' ')
			input++;
		input = set_flag(c, input, &j);
	}
	return (input);
}

/*실제로 cmd에 인덱스 넣어주는과정*/
char	*init_cmd(t_cmd *c, char *input)
{
	int	size;

	while (*input && *input == ' ')
		input++;
	if (is_flag(*input))
		input = edit_input(&input);
	if (input == NULL)
		return (NULL);
	size = count(input);
	if (size == ERROR)
		return (NULL);
	//i = -1;
	//while (input[++i]);
	//if (is_flag(input[i - 1]))
		//size--;
	c->cmd = (char **)malloc(sizeof(char *) * (size + 1));
	c->cmd[size] = NULL;
	return (input_cmd(c, input, size));
}
