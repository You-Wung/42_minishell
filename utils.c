#include "minishell.h"

extern t_ext	g_var;

int	is_flag(char c)
{
	if (c == '|' || c == '>'
		|| c == '<' || c == ';')
		return (1);
	return (0);
}
