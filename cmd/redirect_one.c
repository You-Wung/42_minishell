#include "../minishell.h"

extern t_ext	g_var;

void	redi_L_APP(char *str, int flag, t_redi *re)
{
	int		wstatus;
	int		pid;

	pid = fork();
	g_var.writing = 2;
	if (pid == 0)
		redi_L_APP_op(flag, str, re);
	else if (pid > 0)
	{
		g_var.writing = 3;
		waitpid(pid, &wstatus, 0);
		//g_var.writing = 0;
	}
}

int	redirect_one(char *str, int flag)
{
	int	ret;

	ret = redi_one(str, flag);
	if (ret == 0)
	{
		redi_L_APP(str, 0, NULL);
		return (0);
	}
	close(ret);
	return (0);
}

static int	flagg(char *input, int *flag, int i)
{
	if (input[i] && input[i] == '>' && input[i + 1] == '>')
		*flag = R_APP;
	else if (input[i] && input[i] == '<' && input[i + 1] == '<')
		*flag = L_APP;
	else if (input[i] && input[i] == '<' && !is_flag(input[i + 1]))
		*flag = L_RE;
	else if (input[i] && input[i] == '>' && !is_flag(input[i + 1]))
		*flag = R_RE;
	else
		*flag = 0;
	if (*flag)
		return (0);
	return (1);
}

int	check_conditon(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	while (input[i] && (input[i] == '>' || input[i] == '<' || input[i] == ' '))
		i++;
	while (input[i] && input[i] != ' ' && input[i] != '|')
		i++;
	while (input[i] && input[i] == ' ')
		i++;
	if (!input[i] || input[i] == '|')
		return (0);
	return (1);
}

char	*single_redirection(char *input)
{
	char	buf[125];
	int		i;
	int		in;
	int		flag;
	int		cp;

	i = 0;
	if (check_conditon(input))
		return (input);
	while (input[i] && input[i] == ' ')
		i++;
	if (flagg(input, &flag, i))
		return (input);
	while (input[i] && (input[i] == '>' || input[i] == '<' || input[i] == ' '))
		i++;
	cp = i;
	in = 0;
	while (input[i] && input[i] != ' ' && input[i] != '|'
		&& !is_re(input[i]) && in < 124)
		buf[in++] = input[i++];
	buf[in] = '\0';
	while (input[i] && (input[i] == ' ' || input[i] == '|' ))
		i++;
	g_var.qmark = redirect_one(&buf[0], flag);
	return (&input[i]);
}
