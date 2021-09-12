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
	if (c == '\'' && m->dcomma % 2 == 0)
		m->comma++;
	else if (c == '\"' && m->comma % 2 == 0)
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
	int		smth;
	t_match	m;

	ft_memset(&m, 0, sizeof(t_match));
	while (*str)
	{
		smth = 0;
		set_comma_index(*str, &m);
		if (is_flag(*str) && *(str + 1))
		{
			if (*str == *(str + 1))
				str++;
			str++;
			while (*str == ' ')
				str++;
			while (*str && *str != ' ' && !is_flag(*str) && ++smth)
				str++;
			if (*str && is_flag(*str) && check_comma_index(m) && !smth)
				return (ERROR);
		}
		if (!*str)
			break ;
		str++;
	}
	return (0);
}

int	g_var_set(void)
{
	g_var.size_pi = 0;
	g_var.size_se = 0;
	g_var.pnum = 0;
	g_var.fre = NULL;
	return (1);
}

int	full_check(char *str)
{
	while (*str && *str == ' ')
		str++;
	if ((*str >= 33
			&& *str <= 46 && *str != '$') || (*str == ':' || *str == ';'
			|| *str == '=') || (*str >= 63 && *str <= 64)
		|| (*str >= 91 && *str <= 96) || (*str >= 123 && *str <= 126))
	{
		g_var.qmark = 1;
		return (1);
	}
	return (0);
}
