#include "minishell.h"

int		g_var;

void	init_shell(t_shell *shell, char **envp)
{
	shell->prompt = ft_strdup("minishell$ ");
	shell->envp = copy_environment(envp);
	shell->buffer = malloc(sizeof(char) * BUFFERSIZE);
	shell->command_pos = 0;
	shell->main_pid = getpid();
	shell->exit_code = 0;
	shell->expand = 1;
	shell->token_error = 1;
}

void	run_shell(t_shell *shell)
{
	char	*command;
	char	**split_command;
	int		i;

	command = readline(shell->prompt);
	while (command)
	{
		if (g_var == 130 || g_var == 131)
		{
			shell->exit_code = g_var;
			g_var = 0;
		}
		if (add_to_rl(command))
			add_history(command);
		split_command = ft_split(command, ';');
		i = 0;
		while (split_command[i])
		{
			shell->command = split_command[i++];
			exec_command(shell);
		}
		clean_split(split_command);
		free(command);
		command = readline(shell->prompt);
	}
}

void	exec_command(t_shell *shell)
{
	pid_t	pid;
	t_token	term;

	shell->command_pos = 0;
	term = command(shell, &pid, 0, NULL);
	if (term == T_ERROR)
	{
		print_error_2(shell, "Syntax error");
		term = T_NL;
	}
	else if (pid > 0)
		wait_command(shell, pid);
}

void	clean_shell(t_shell *shell)
{
	free(shell->prompt);
	free(shell->buffer);
	clean_split(shell->envp);
	if (access("/tmp/ms_tmp", F_OK) == 0)
		unlink("/tmp/ms_tmp");
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc != 1)
	{
		printf("minishell: %s: No such file or directory\n", argv[1]);
		return (1);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	init_shell(&shell, envp);
	run_shell(&shell);
	clean_shell(&shell);
	return (0);
}
