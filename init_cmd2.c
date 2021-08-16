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
