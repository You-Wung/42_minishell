#include "minishell.h"

t_ext var;

static void	our_mark(void)
{
	printf(COLOR_SET);
	printf("┌        STARTED CODING 2021 JULY 19TH MONDAY       ┐\n");
	printf("│           CREATED BY 'tyou' AND 'yujung'          │\n");
	printf("└           ───────── MINISHELL ─────────           ┘\n\n");
	printf("─────────────────────────────────────────────────────\n");
	printf("  ███████  █  █   █  █     ████  █  █  ███  █    █\n");
	printf("  █  █  █  █  ██  █  █     █     █  █  █    █    █\n");
	printf("  █  █  █  █  █ █ █  █     ████  ████  ███  █    █\n");
	printf("  █  █  █  █  █  ██  █        █  █  █  █    █    █\n");
	printf("  █  █  █  █  █   █  █     ████  █  █  ███  ███  ███\n");
	printf("─────────────────────────────────────────────────────\n");
	printf(COLOR_RESET);
}

int main(int argc, char **argv, char **env)
{
	our_mark();
	init_env(env);
	init_signal();
	start_read();
}