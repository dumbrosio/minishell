#include "minishell.h"

int		g_var;

void	init_sh(t_shell *shell, char **envp)
{
	shell->prompt = ft_strdup("mini$ ");
	shell->envp = copy_env(envp);
	shell->buffer = malloc(sizeof(char) * BUFFERSIZE);
	shell->command_pos = 0;
	shell->main_pid = getpid();
	shell->exit_code = 0;
	shell->localenvp = (char **)malloc(sizeof(char *));
	shell->localenvp[0] = NULL;
}

void run_sh(t_shell *shell)
{
	pid_t   pid;
	t_token term;

	term = T_NL;
	shell->command = readline(shell->prompt);
	while (shell->command)
	{
		if (!handle_input(shell, term))
			continue;
		handle_command(shell, &term, &pid);
		free(shell->command);
		shell->command = readline(shell->prompt);
	}
}

void	clean_sh(t_shell *shell)
{
	free(shell->prompt);
	free(shell->buffer);
	ft_clean(shell->envp);
	ft_clean(shell->localenvp);
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

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc > 1)
	{
		if (ft_strncmp(argv[1], "parser", 6) == 0)
		{
			init_sh(&shell, envp);
			test_parser(&shell);
			return (0);
		}
		else
		{
			printf("Usage:\n./minishell: Run minishell\n");
			printf("./minishell parser: Test parser\n");
			return (1);
		}
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	init_sh(&shell, envp);
	run_sh(&shell);
	clean_sh(&shell);
	return (0);
}

