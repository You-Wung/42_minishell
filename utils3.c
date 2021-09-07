#include "minishell.h"

int	check_comma_index(t_match m)
{
	if (m.comma % 2 == 0 && m.dcomma % 2 == 0)
		return (1);
	return (0);
}

void	set_comma_index(char c, t_match *m)
{
	if (c == '\'')
		m->comma++;
	else if (c == '\"')
		m->dcomma++;
}
