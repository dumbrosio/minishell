#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT && errno != 2)
	{
		g_var = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGINT)
		printf("\n");
	else if (sig == SIGQUIT && errno == 2)
		g_var = 131;
}
