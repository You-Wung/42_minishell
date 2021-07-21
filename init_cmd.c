#include "minishell.h"

static int comma_check(t_match *m)
{
	int	i;

	i = 0;
	if (m->comma % 2 == 1 && ++i)
		printf("quote");
	if (m->dcomma % 2 == 1 && ++i)
		printf("double quote");
	if (m->backtick % 2 == 1 && ++i)
		printf("backtick");
	if (!i)
		return (0);
	printf("\n");
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
	while (*input)
	{
		if (*input == '\'' && m.dcomma % 2 == 0 && m.backtick % 2 == 0)
			m.comma++;
		if (*input == '\"' && m.comma % 2 == 0 && m.backtick % 2 == 0)
			m.dcomma++;
		if (*input == '`' && m.dcomma % 2 == 0 && m.comma % 2 == 0)
			m.backtick++;
		if (*input == ' ' && m.comma % 2 == 0
			&& m.dcomma % 2 == 0 && m.backtick % 2 == 0)
			rt++;
		input++;
	}
	if (comma_check(&m) == ERROR)
		return (ERROR);
	return (rt);
}

static int check_size(char *input)
{
	int comma;
	int	rt;

	rt = 0;
	comma = 0;
	while (*input != ';' && *input != '>' && *input != '<'
			&& *input != '|')
	{
		if (*input == '\'' || *input == '\"' || *input == '`')
			comma++;
		if (*input != ' ' && *input != '\0')
			rt++;
		if ((*input == ' ' && comma % 2 == 0) || *input == '\0')
			break ;
		input++;
	}
	printf("returns %d\n",rt);
	return (rt);
}

static char	*input_cmd(t_cmd *c, char *input, int size)
{
	int	i;
	int j;
	int	phrase;

	i = 0;
	j = 0;
	while (input[i] && input[i] != ';' && input[i] != '>'
		&& input[i] != '<' && input[i] != '|')
	{
		phrase = check_size(input + i);
		if (phrase > 0)
		{
			c->cmd[j] = (char *)malloc(phrase + 1);
			ft_strlcpy(c->cmd[j++], &input[i], phrase);
		}
		while(input[i] == ' ')
			i++;
		i += phrase + 1;
	}
	if (input[i] != '>' || input[i] != '<')
		i++;
	printf("%s !\n",c->cmd[0]);
	printf("%s !\n",c->cmd[1]);
	return (&(input[i]));
}

/*실제로 cmd에 인덱스 넣어주는과정*/
char	*init_cmd(t_cmd *c, char *input, char **env)
{
	int	size;
	int	i;

	size = count(input);
	if (size == ERROR)
		return (NULL);
	c->cmd = (char **)malloc(sizeof(char *) * size + 1);
	c->cmd[size] = NULL;
	return (input_cmd(c, input, size));
}