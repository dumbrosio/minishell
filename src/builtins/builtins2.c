#include "minishell.h"

int	other_builtins(t_shell *shell, t_command *cmd)
{
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
	{
		ft_exit(shell, cmd);
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

int	export_checker(t_command *cmd, int i)
{
	if (cmd->argv[i][0] == '=' || cmd->argv[i][0] == '/' || \
	cmd->argv[i][0] == '-' || ft_isdigit((unsigned char)cmd->argv[i][0]))
		return (1);
	return (0);
}

void	export_error(t_shell *shell, char *key, int *i)
{
	write(2, "minishell: export: '", 20);
	write(2, key, ft_strlen(key));
	write(2, "': not a valid identifier\n", 26);
	shell->exit_code = 1;
	(*i)++;
}

void	cd_write_error(t_shell *shell, char *arg)
{
	write(2, "minishell: cd: ", 15);
	write(2, arg, strlen(arg));
	write(2, ": No such file or directory", 28);
	write(2, "\n", 2);
	shell->exit_code = 1;
}
