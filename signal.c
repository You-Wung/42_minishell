#include "minishell.h"

extern t_ext var;

void sigint_handler(int signo)
{
	char		*prompt;
	int			len;

	//printf("%c[1A",27);
	//printf("%c[K", 27);
	//printf("%c[1B",27);
	struct termios attributes;

    tcgetattr(STDIN_FILENO, &attributes);
	var.save = attributes;
	attributes.c_lflag &= (~ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &attributes);
	
	prompt = make_prompt();
	len = ft_strlen(prompt);
	write(STDOUT_FILENO, "\n", 1);
    write(STDOUT_FILENO, prompt, len);
}

static void sigquit_handler(int signo)
{
	//printf("ctrl D\n");
	//signal(SIGQUIT, SIG_DFL);
}

void	init_signal()
{

	
	signal(SIGINT, sigint_handler);
	//signal(SIGQUIT, sigquit_handler);
}