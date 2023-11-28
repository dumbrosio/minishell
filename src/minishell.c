#include "minishell.h"

int		g_var;

void	init_shell(t_shell *shell, char **envp)
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

void	run_shell(t_shell *shell)
{
	pid_t	pid;
	t_token	term;

	term = T_NL;
	shell->command = readline(shell->prompt);
	while (shell->command)
	{
		if (term == T_NL)
		{
			shell->command_pos = 0;
			if (ft_strlen(shell->command) && !is_empty_str(shell->command))
				add_history(shell->command);
		}
		term = command(shell, &pid, 0, NULL);
		if (term == T_ERROR)
		{
			print_error("Bad command");
			term = T_NL;
		}
		else if (pid > 0)
			wait_command(shell, pid);
		free(shell->command);
		shell->command = readline(shell->prompt);
	}
}

void	clean_shell(t_shell *shell)
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
				init_shell(&shell, envp);
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
	init_shell(&shell, envp);
	run_shell(&shell);
	clean_shell(&shell);
	return (0);
}
