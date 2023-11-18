#include "minishell.h"

int			g_var;

static char	*create_abs_path(char *path, char *cmd)
{
	int		path_len;
	int		cmd_len;
	char	*abs;

	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	abs = (char *)malloc(sizeof(char) * (cmd_len + path_len + 2));
	ft_strncpy(abs, path, path_len);
	ft_strncpy(abs + path_len, "/", 1);
	ft_strncpy(abs + path_len + 1, cmd, cmd_len);
	ft_strncpy(abs + path_len + cmd_len + 1, "\0", 1);
	return (abs);
}

static void	free_path(char **path)
{
	char	**runner;

	runner = path;
	while (*runner)
		free(*runner++);
	free(path);
}

char	*get_abs_path(char *cmd)
{
	char	*abs;
	char	**path;
	char	**runner;

	path = ft_split(getenv("PATH"), ':');
	if (path == NULL)
		return (ft_strdup(cmd));
	runner = path;
	while (*runner)
	{
		abs = create_abs_path(*runner, cmd);
		if (access(abs, X_OK) == 0)
		{
			free_path(path);
			return (abs);
		}
		free(abs);
		abs = NULL;
		runner++;
	}
	if (abs)
		free(abs);
	free_path(path);
	return (ft_strdup(cmd));
}

void	init_shell(t_shell *shell, char **envp)
{
	shell->prompt = ft_strdup("minishell$ ");
	shell->envp = envp;
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
		return (0);
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	init_shell(&shell, envp);
	run_shell(&shell);
	clean_shell(&shell);
	return (0);
}
