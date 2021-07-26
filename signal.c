#include "minishell.h"

extern t_ext var;

void sigint_handler(int signo)
{
	char		*prompt;
	int			len;

	//printf("%c[1A",27);
	//printf("%c[K", 27);
	//printf("%c[1B",27);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void sigquit_handler(int signo)
{
	rl_on_new_line();
	rl_redisplay();
}

void	init_signal()
{
	struct termios attributes;

    tcgetattr(STDIN_FILENO, &attributes);
	var.restore = attributes;
	//attributes.c_lflag &= (~ECHOCTL);
	//ctrl + d 는 시그널이 아님. input이 null이냐 아니냐에 따라 처리
    tcsetattr(STDIN_FILENO, TCSANOW, &attributes);
	
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}