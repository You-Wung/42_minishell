#include "minishell.h"

char	*set_flag(t_cmd *c, char *input, int *sign)
{
	if (*input == '>' && *(input + 1) == '>')
		c->flag = R_APP;
	else if (*input == '<' && *(input + 1) == '<')
		c->flag = L_APP;
	else if (*input == '>')
		c->flag = R_RE;
	else if (*input == '<')
		c->flag = L_RE;
	else if (*input == '|')
		c->flag = PIPE;
	else if (*input == ';')
		c->flag = SEMI;
	else
		c->flag = 0;
	while (*input == '>' || *input == '<'
		|| *input == ';' || *input == '|')
	{
		input++;
		*sign = -1;
	}
	printf("c->flag : %d\n", c->flag);
	return (input);
}

int	check_input(char *input, t_match *m)
{
	int	c;
	int	dc;
	int	b;

	c = m->comma % 2;
	dc = m->dcomma % 2;
	b = m->backtick % 2;
	if (*input && ((c || dc || b) || *input != '>')
		&& ((c || dc || b) || *input != ';')
		&& ((c || dc || b) || *input != '<')
		&& ((c || dc || b) || *input != '|'))
		return (1);
	return (0);
}

//static void	pull_input(char *input)
//{
//	char	*copied;
//	int		i;
//	int		j;

//	i = 0;
//	j = 0;
//	copied = ft_strdup(input);
//	while (copied[i] && copied[i] != ' ')
//		i++;
//	while (copied[i])
//		input[j++] = copied[i++];
//	input[j] = '\0';
//	free(copied);
//}

//static char	*save_cmd(char *input)
//{
//	char	*cmd;
//	int		i;
//	int		j;
//	int		pull_point;

//	j = 0;
//	i = 0;
//	cmd = malloc(ft_strlen(input));
//	while (is_flag(input[i]))
//		i++;
//	while (input[i] && input[i] == ' ')
//		i++;
//	while (input[i] && input[i] != ' ')
//		i++;
//	while (input[i] && input[i] == ' ')
//		i++;
//	pull_point = i;
//	while (input[i] && input[i] != ' ')
//		cmd[j++] = input[i++];
//	cmd[j] = '\0';
//	pull_input(&input[pull_point]);
//	return (cmd);
//}

static char	*set_after(char *input)
{
	char	*rt;
	int		i;

	i = -1;
	rt = malloc(ft_strlen(input));
	while (is_flag(input[++i]))
		rt[i] = input[i];
	while (input[i] && input[i] == ' ')
	{
		rt[i] = ' ';
		i++;
	}
	while (input[i] && input[i] != ' ')
	{
		rt[i] = input[i];
		i++;
	}
	rt[i] = '\0';
	return (rt);
}

static char	*save_cmd(char *input, int i)
{
	int		in;
	int		in2;
	char	*ret;
	char	*after;

	ret = malloc(ft_strlen(input));
	in = -1;
	in2 = 0;
	while (++in < (int)ft_strlen(input) - 1)
		ret[in] = ' ';
	in = -1;
	while (!is_flag(input[++in]))
		ret[in2++] = input[in];
	after = set_after(&(input[in]));
	while (is_flag(input[in]))
		in++;
	while (input[in] && input[in] == ' ')
		in++;
	while (input[in] && input[in] != ' ')
		in++;
	while (input[in] && in < i)
	{
		ret[in2++] = input[in];
		in++;
	}
	ret[in2++] = ' ';
	input_plus_after(&(ret[in2]), after, &in2);
	while (input[in])
	{
		ret[in2++] = input[in];
		in++;
	}
	ret[in2] = '\0';
	return (ret);
}

char	*edit_input(char **input)
{
	int		i;
	int		comma;
	int		cnt;

	i = 0;
	comma = 0;
	cnt = 0;
	printf("EDIT INPUT STARTS\n");
	if ((**input == '<' && *(*input + 1) == '<') || **input == ';')
		return (NULL);
	while (*(*input + i))
	{
		if (*(*input + i) == '\"' || *(*input + i) == '\'' || *(*input + i) == '`')
			comma++;
		if (is_flag(*(*input + i)) && comma % 2 == 0)
			cnt++;
		if (*(*input + i) == '\0' || ((is_flag(*(*input + i)) && comma % 2 == 0 && cnt == 2)))
			break ;
		i++;
	}
	printf("[%s] changed ", *input);
	*input = save_cmd(*input, i);
	printf("[%s]\n", *input);
	return (*input);
}

//char	*edit_input(char **input)
//{
//	char	*ret;
//	char	*cmd;
//	int		i;
//	int		j;

//	if ((**input == '<' && *(*input + 1) == '<') || **input == ';')
//		return (NULL);
//	i = 0;
//	while (is_flag(*(*input + i)) || (*(*input + i) == ' '))
//		i++;
//	if (*(*input + i) == 0)
//		return (NULL);
//	cmd = save_cmd(*input);
//	ret = malloc(ft_strlen(*input) + 1);
//	i = 0;
//	j = 0;
//	while (cmd[i])
//		ret[j++] = cmd[i++];
//	i = 0;
//	while (*(input + i) && i < (int)ft_strlen(*input))
//		ret[++j] = *(*input + i++);
//	printf("ret : %s\n", ret);
//	return (ret);
//}
