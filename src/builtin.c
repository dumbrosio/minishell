#include "minishell.h"

int	ft_echo(t_command *cmd)
{
	int	i;

	i = 0;

	while (++i < cmd->argc)
		{
			write(1, cmd->argv[i], ft_strlen(cmd->argv[i]));
			if (cmd->argv[i + 1])
				write(1," ", 1);
		}
	write(1, "\n", 1);
	return (0);
}

int	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
		printf("%s\n",shell->envp[i++]);
	return (0);
}

int	ft_pwd(t_command *cmd)
{
	(void)cmd;
	printf("eseguo pwd!\n");
	return (0);
}

int	is_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_shell *shell, t_command *cmd)
{
	(void)shell;
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (ft_env(shell));
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (ft_pwd(cmd));
	return (1);
}
