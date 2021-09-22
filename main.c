#include "minishell.h"

t_ext	g_var;

static void	mark2(void)
{
	printf("                        __---__\n");
	printf("                      _-       /--______\n");
	printf("                 __--( /     \\ )XXXXXXXXXXX\\v.\n");
	printf("               .-XXX(   o   o  )XXXXXXXXXXXXXXX-\n");
	printf("              /XXX(       u     )        XXXXXXX\\\n");
	printf("            /XXXXX(              )--_  XXXXXXXXXXX\\\n");
	printf("           /XXXXX/ (      O     )   XXXXXXXXXXXXXXX\\\n");
	printf("           XXXXX/   /                __   \\__ \\XXXXX\n");
	printf("           XXXXXX__/                    \\   \\------>\n");
	printf("  ----___  XXX__/         MINISHELL      \\__   ---->/\n");
	printf("     \\-  --__/   ___/\\                     \\_____---/\n");
	printf("      \\-\\    ___/     \\                  '--- XXXXXX\n");
	printf("         \\-\\/XXX\\ XXXXXX                 '--- /XXXX\n");
	printf("           \\XXXXXXXXX   \\                '- /XXXXX/\n");
	printf("            \\XXXXXX      >               ' _/XXXX/\n");
	printf("              \\XXXXX--__/              __-- XXXX/\n");
	printf("               -XXXXXXXX---------------  XXXXXX-\n");
	printf("                  \\XXXXXXXXXXXXXXXXXXXXXXXXXX/\n");
	printf("                    \"\"VXXXXXXXXXXXXXXXXXXV\"\"\n\n");
}

static void	our_mark(void)
{
	printf("\033[2J");
	printf(COLOR_SET);
	// printf("───────────────────────────────────────────────────────────────\n");
	// printf("─────                                                     ─────\n");
	// printf("─────                                                     ─────\n");
	// printf("─────  ███████  █  █   █  █     ████  █  █  ███  █    █   ─────\n");
	// printf("─────  █  █  █  █  ██  █  █     █     █  █  █    █    █   ─────\n");
	// printf("─────  █  █  █  █  █ █ █  █     ████  ████  ███  █    █   ─────\n");
	// printf("─────  █  █  █  █  █  ██  █        █  █  █  █    █    █   ─────\n");
	// printf("─────  █  █  █  █  █   █  █     ████  █  █  ███  ███  ███ ─────\n");
	// printf("─────                                                     ─────\n");
	// printf("─────                                                     ─────\n");
	// printf("───────────────────────────────────────────────────────────────\n\n");
	mark2();
	printf("───────────────────────────────────────────────────────────────\n");
	printf("─────                                                     ─────\n");
	printf("─────┌        STARTED CODING 2021 JULY 19TH MONDAY       ┐─────\n");
	printf("─────│           CREATED BY 'tyou' AND 'yujung'          │─────\n");
	printf("─────└           ───────── MINISHELL ─────────           ┘─────\n");
	printf("─────                                                     ─────\n");
	printf("───────────────────────────────────────────────────────────────\n");
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
	g_var.writing = 0;
	g_var.qmark = 0;
	g_var.n_env = env;
	g_var.fre = NULL;
	g_var.first_input_size = 0;
	init_env(env);
	init_signal();
	start_read();
}
