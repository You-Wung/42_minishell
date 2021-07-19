#include "minishell.h"

char *make_prompt(void)
{
	/*getcwd 버퍼는 malloc 후 사용*/
	char *prompt;
	int	i;

	prompt = (char *)malloc(sizeof(char) * (1024 + 2));
	getcwd(prompt, 1024);
	i = 0;
	while (prompt[i])
		i++;
	prompt[i++] = '$';
	prompt[i++] = ' ';
	prompt[i] = '\0';
	return (prompt);
}

int	start_read(void)
{
	char *input;

	input = readline(make_prompt());
	while (input)
	{
		input = readline(make_prompt());
		add_history(input);
	}
	return (0);
}