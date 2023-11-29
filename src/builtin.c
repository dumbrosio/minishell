#include "minishell.h"

int	ft_echo(t_command *cmd)
{
	(void)cmd;
	printf("eseguo echo!\n");
	return (0);
}

int	ft_env(t_command *cmd)
{
	(void)cmd;
	printf("eseguo env!\n");
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
		return (ft_env(cmd));
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (ft_pwd(cmd));
	return (1);
}