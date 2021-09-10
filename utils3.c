#include "minishell.h"

extern t_ext	g_var;

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

/*
		기존의 실패 원인.
		
		모든 문자열 검색하는 flag_check() 에서
		잘못된 예외처리를 했기에, init_cmd() 에서
		실제 cmd 에 들어가기전에, 다음 플래그까지 검사를 진행한다.
		example.
				1. > < echo hi
				2. echo hi > test
	*/
int	error_check(char *str)
{
	int	smth;

	while (*str)
	{
		smth = 0;
		if (is_flag(*str) && *(str + 1))
		{
			if (*str == *(str + 1))
				str++;
			str++;
			while (*str == ' ')
				str++;
			while (*str && *str != ' ' && !is_flag(*str) && ++smth)
				str++;
			if (*str && is_flag(*str) && !smth)
				return (ERROR);
		}
		str++;
	}
	return (0);
}

void	g_var_set(void)
{
	g_var.size_pi = 0;
	g_var.size_se = 0;
	g_var.pnum = 0;
	g_var.fre = NULL;
}
