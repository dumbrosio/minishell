#include "minishell.h"

int	other_builtins(t_shell *shell, t_command *cmd)
{
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
	{
		ft_exit(shell);
		return (1);
	}
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
	{
		ft_export(shell, cmd);
		return (1);
	}
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
	{
		ft_unset(shell, cmd);
		return (1);
	}
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
	{
		ft_cd(shell, cmd);
		return (1);
	}
	return (0);
}

int	ft_exit(t_shell *shell)
{
	free(shell->command);
	clean_shell(shell);
	_exit(EXIT_SUCCESS);
}

int	ft_export(t_shell *shell, t_command *cmd)
{
	(void)shell;
	(void)cmd;
	printf("eseguo export\n");
	return (0);
}

int	ft_unset(t_shell *shell, t_command *cmd)
{
	(void)shell;
	(void)cmd;
	printf("eseguo unset\n");
	return (0);
}

int	ft_cd(t_shell *shell, t_command *cmd)
{
	(void)shell;
	(void)cmd;
	printf("eseguo cd\n");
	return (0);
}
