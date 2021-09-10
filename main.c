#include "minishell.h"

t_ext	g_var;

static void	our_mark(void)
{
	printf(COLOR_SET);
	printf("┌        STARTED CODING 2021 JULY 19TH MONDAY       ┐\n");
	printf("│           CREATED BY 'tyou' AND 'yujung'          │\n");
	printf("└           ───────── MINISHELL ─────────           ┘\n");
	printf("─────────────────────────────────────────────────────\n");
	printf("  ███████  █  █   █  █     ████  █  █  ███  █    █   \n");
	printf("  █  █  █  █  ██  █  █     █     █  █  █    █    █   \n");
	printf("  █  █  █  █  █ █ █  █     ████  ████  ███  █    █   \n");
	printf("  █  █  █  █  █  ██  █        █  █  █  █    █    █   \n");
	printf("  █  █  █  █  █   █  █     ████  █  █  ███  ███  ███ \n");
	printf("─────────────────────────────────────────────────────\n");
}

int	main(int argc, char **argv, char **env)
{
	int	i;

	our_mark();
	if (argc != 1 || &(argv[1]) == NULL)
	{
		printf("minishell: error\n");
		printf(COLOR_RESET);
		return (0);
	}
	i = -1;
	while (++i < 100)
		g_var.pid[i] = 0;
	g_var.size_pi = 0;
	g_var.size_se = 0;
	g_var.writing = 0;
	g_var.qmark = 0;
	g_var.n_env = env;
	g_var.fre = NULL;
	init_env(env);
	init_signal();
	start_read();
}
