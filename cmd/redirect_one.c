#include "../minishell.h"

extern t_ext	g_var;

int	redirect_one(char *str, int flag)
{
	int		file;

	file = 0;
	if (flag == L_APP)
	{
		redi_L_APP(str, 0, NULL);
		return (0);
	}
	else if (flag == L_RE)
		file = open(str, O_RDONLY);
	else if (flag == R_APP)
		file = open(str, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (flag == R_RE)
		file = open(str, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file < 0)
	{
		printf("minishell: no such file or directory: %s\n", str);
		return (1);
	}
	close(file);
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
	while (input[i] && input[i] != ' ')
		i++;
	if (!input[i])
		return (0);
	return (1);
}

int	single_redirection(char *input)
{
	int	i;
	int	flag;
	int	cp;

	i = 0;
	if (check_conditon(input))
		return (0);
	while (input[i] && input[i] == ' ')
		i++;
	if (flagg(input, &flag, i))
		return (0);
	while (input[i] && (input[i] == '>' || input[i] == '<' || input[i] == ' '))
		i++;
	cp = i;
	while (input[i] && input[i] != ' ')
		i++;
	while (input[i] && input[i] == ' ')
		input[i++] = '\0';
	if (!input[i])
	{
		g_var.qmark = redirect_one(&input[cp], flag);
		return (1);
	}
	return (0);
}
