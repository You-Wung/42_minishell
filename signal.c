#include "minishell.h"

extern t_ext	g_var;

static void	sigint2(void)
{
	int	i;

	i = 0;
	if (g_var.writing == 2)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	else if (g_var.writing == 3)
	{
		while (i < 256)
		{
			if (g_var.pid[i] > 0)
				kill(g_var.pid[i], SIGINT);
			g_var.pid[i++] = 0;
		}
	}
}

void	sigint_handler(int signo)
{
	int	i;

	signo = 0;
	if (g_var.writing == 2 || g_var.writing == 3)
		sigint2();
	else if (g_var.writing)
	{
		write(STDOUT_FILENO, "^C\n", 3);
		i = 0;
		while (i < 256)
		{
			if (g_var.pid[i] > 0)
				kill(g_var.pid[i], SIGINT);
			g_var.pid[i] = 0;
			i++;
		}
	}
	else if (g_var.writing == 0)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	sigquit_handler(int signo)
{
	signo = 0;
	if (g_var.writing == 1)
	{
		write(STDOUT_FILENO, "^\\Quit: 3\n", 11);
		g_var.sig_qmark = 131;
	}
	else if (g_var.writing == 0 || g_var.writing == 2)
	{
		rl_on_new_line();
		 rl_replace_line("", 0);
		rl_redisplay();
	}
	 rl_replace_line("", 0);
}

void	init_signal(void)
{
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	g_var.restore = attributes;
	attributes.c_lflag &= (~ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &attributes);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
