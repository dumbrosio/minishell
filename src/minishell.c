#include "minishell.h"

int	g_var;

void	init_shell(t_shell *shell)
{
	shell->prompt = ft_strdup("minishell$ ");
}

void	run_shell(t_shell *shell)
{
	while (1)
	{
		shell->command = readline(shell->prompt);
		if (!shell->command)
			break ;
		if (ft_strlen(shell->command) == 0)
		{
			free(shell);
			continue ;
		}
		add_history(shell->command);
	}
	free(shell->command);
}

void	clean_shell(t_shell *shell)
{
	free(shell->prompt);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_var = 1;
	}
}

int	main( void)
{
	t_shell	shell;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	init_shell(&shell);
	run_shell(&shell);
	clean_shell(&shell);
	return (0);
}
