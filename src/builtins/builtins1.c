#include "minishell.h"

int	ft_echo(t_command *cmd)
{
	int	i;
	int	is_n;

	i = 1;
	is_n = 0;
	if (cmd->argc == 1)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (i < cmd->argc && ft_strncmp("-n", cmd->argv[i], 2) == 0)
	{
		is_n = 1;
		i++;
	}
	while (i < cmd->argc)
	{
		write(1, cmd->argv[i], ft_strlen(cmd->argv[i]));
		if (cmd->argv[++i])
			write(1, " ", 1);
	}
	if (!is_n)
		write(1, "\n", 1);
	return (0);
}

int	ft_env(t_shell *shell)
{
	int		i;
	char	*equal_sign;

	i = 0;
	while (shell->envp[i])
	{
		equal_sign = ft_strchr(shell->envp[i], '=');
		if (equal_sign)
		{
			printf("%s\n", shell->envp[i]);
		}
		i++;
	}
	return (0);
}

int	ft_pwd(t_shell *shell)
{
	char	pwd[PATH_MAX];

	(void)shell;
	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		write(1, pwd, strlen(pwd));
		write(1, "\n", 1);
	}
	else
	{
		perror("getcwd() error");
		return (1);
	}
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
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (ft_env(shell));
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (ft_pwd(shell));
	return (1);
}
