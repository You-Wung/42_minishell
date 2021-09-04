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

static void	pull_input(char *input)
{
	char	*copied;
	int		i;
	int		j;

	i = 0;
	j = 0;
	copied = ft_strdup(input);
	while (copied[i] && copied[i] != ' ')
		i++;
	while (copied[i])
		input[j++] = copied[i++];
	input[j] = '\0';
	free(copied);
}

static char	*save_cmd(char *input)
{
	char	*cmd;
	int		i;
	int		j;
	int		pull_point;

	j = 0;
	i = 0;
	cmd = malloc(10);
	while (is_flag(input[i]))
		i++;
	while (input[i] && input[i] == ' ')
		i++;
	while (input[i] && input[i] != ' ')
		i++;
	while (input[i] && input[i] == ' ')
		i++;
	pull_point = i;
	while (input[i] && input[i] != ' ')
		cmd[j++] = input[i++];
	cmd[j] = '\0';
	pull_input(&input[pull_point]);
	return (cmd);
}

char	*edit_input(char **input)
{
	char	*ret;
	char	*cmd;
	int		i;
	int		j;

	if ((**input == '<' && *(*input + 1) == '<') || **input == ';')
		return (NULL);
	i = 0;
	while (is_flag(*(*input + i)) || (*(*input + i) == ' '))
		i++;
	if (*(*input + i) == 0)
		return (NULL);
	cmd = save_cmd(*input);
	ret = malloc(ft_strlen(*input) + 1);
	i = 0;
	j = 0;
	while (cmd[i])
		ret[j++] = cmd[i++];
	i = 0;
	while (*(input + i) && i < (int)ft_strlen(*input))
		ret[++j] = *(*input + i++);
	//free(*input);
	//printf("ret : %s\n", ret);
	return (ret);
}
