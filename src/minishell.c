#include "minishell.h"

int		g_var;

void	init_shell(t_shell *shell, char **envp)
{
	shell->prompt = ft_strdup("minishell$ ");
	shell->envp = copy_environment(envp);
	shell->buffer = malloc(sizeof(char) * BUFFERSIZE);
	shell->command_pos = 0;
	shell->stdin_fd = STDIN_FILENO;
	shell->stdout_fd = STDOUT_FILENO;
	shell->stderr_fd = STDERR_FILENO;
}

static void	free_cmds(t_shell *shell)
{
	int	i;

	free(shell->cmd);
	i = 0;
	while (shell->args[i])
		free(shell->args[i++]);
	free(shell->args);
	free(shell->path_cmd);
	shell->cmd = NULL;
	shell->args = NULL;
	shell->path_cmd = NULL;
}

void	run_shell(t_shell *shell)
{
	pid_t	pid;

	while (1)
	{
		shell->cmd = readline(shell->prompt);
		if (!shell->cmd)
			break ;
		if (ft_strlen(shell->cmd) == 0)
		{
			free(shell->cmd);
			continue ;
		}
		shell->args = ft_split(shell->cmd, ' ');
		shell->path_cmd = get_abs_path(shell->args[0]);
		add_history(shell->cmd);
		pid = fork();
		if (!pid)
		{
			execve(shell->path_cmd, shell->args, shell->envp);
			perror(shell->path_cmd);
			exit(1);
		}
		wait(NULL);
		free_cmds(shell);
	}
}

void	clean_shell(t_shell *shell)
{
	free(shell->prompt);
	free(shell->buffer);
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
