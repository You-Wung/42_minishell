#include "../minishell.h"

extern t_ext	g_var;

int	redi_wri(int flag, char *buf, t_redi *re, int *i)
{
	int	wri;

	wri = 1;
	if (flag == 0)
		wri = 0;
	else
	{
		if (re[0].lapp == 1)
			wri = 0;
		if (*i == re[0].i - 1)
			wri = 0;
		if (ft_strcmp(buf, re[0].str[*i]) == 0)
			*i = *i + 1;
		if (*i == re[0].i)
			exit(0);
	}
	if (!buf)
		exit(0);
	return (wri);
}

void	redi_L_APP_op(int flag, char *str, t_redi *re)
{
	int		file;
	char	*buf;
	int		i;
	int		wri;

	i = 0;
	if (flag == 1)
		file = open("./cmd/user_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		buf = readline(" > ");
		if (!buf)
			printf("%c[1A %c[3C", 27, 27);
		wri = redi_wri(flag, buf, re, &i);
		if (flag == 0 && ft_strcmp(buf, str) == 0)
			exit(0);
		if (buf && flag == 1 && wri == 0)
		{
			write(file, buf, ft_strlen(buf));
			write(file, "\n", 1);
		}
		free(buf);
	}
	if (flag == 1)
		close(file);
}

int	redi_one(char *str, int flag)
{
	int		file;
	char	*buf;

	buf = "";
	file = 0;
	if (flag == R_APP)
		file = open(str, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (flag == R_RE)
		file = open(str, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (flag == L_APP)
		return (0);
	if (flag == L_RE)
		file = open(str, O_RDONLY);
	if (file < 0)
	{
		if (g_var.size_pi == 0)
		{
			buf = ft_strjoin(buf, "minishell: ");
			buf = ft_strjoin(buf, str);
			buf = ft_strjoin(buf, ": no such file or directory\n");
			write(2, buf, ft_strlen(buf));
		}
		return (-1);
	}
	return (file);
}

int	redi_plus(t_cmd *c, t_redi *re, int s_re)
{
	int	file;

	if (c[s_re - 1].flag == L_APP)
	{
		re[0].str[re[0].i++] = c[s_re].cmd[0];
		re[0].lapp = s_re;
	}
	re[0].str[re[0].i] = NULL;
	redi_L_APP(c[re[0].lapp].cmd[0], 1, re);
	file = open("./cmd/user_tmp", O_RDONLY);
	re[0].in = file;
	return (file);
}

int	redi_child(t_cmd *c, t_redi *re, int s_re)
{
	int	file;

	if (re[0].lapp != -2 || c[s_re - 1].flag == L_APP)
		file = redi_plus(c, re, s_re);
	file = redi_one(c[s_re].cmd[0], c[s_re - 1].flag);
	if (file == -1)
		exit(1);
	if (c[s_re - 1].flag == L_RE || c[s_re - 1].flag == L_APP)
	{
		if (re[0].out != 0)
			dup2(re[0].out, STDOUT_FILENO);
		dup2(file, STDIN_FILENO);
		if (s_re == re[0].lapp)
			dup2(re[0].in, STDIN_FILENO);
	}
	else if (c[s_re - 1].flag == R_APP || c[s_re - 1].flag == R_RE)
	{
		if (re[0].in != 0)
			dup2(re[0].in, STDIN_FILENO);
		dup2(file, STDOUT_FILENO);
	}
	g_var.qmark = use_redi_cmd(c);
	close(file);
	return (g_var.qmark);
}
