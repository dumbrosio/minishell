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

int	ft_export(t_shell *shell, t_command *cmd)
{
	if (cmd->argc == 1)
		print_export_entry(shell);
	else
		export_core(shell, cmd);
	return (0);
}

int	print_export_entry(t_shell *shell)
{
	int		i;
	char	**copied_envp;
	char	*env_var;
	char	*key;
	char	*value;

	i = 0;
	copied_envp = shell->envp;
	while (copied_envp[i] != NULL )
	{
		env_var = ft_strdup(copied_envp[i]);
		key = env_var;
		value = ft_strchr(key, '=');
		if (value != NULL)
		{
			*value = '\0';
			value++;
			printf("declare -x %s=\"%s\"\n", key, value);
		}
		i++;
		free(env_var);
	}
	return (1);
}

int	export_checker(t_command *cmd, int i)
{
	if (cmd->argv[i][0] == '=' || cmd->argv[i][0] == '/'|| cmd->argv[i][0] == '-' || ft_isdigit((unsigned char)cmd->argv[i][0]))
		return (1);
	return (0);
}

int	export_core(t_shell *shell, t_command *cmd)
{
	int		i;
	char	*key;
	char	*value;
	char	*equal_sign;

	i = 1;
	while (i < cmd->argc)
	{
		if (export_checker(cmd, i))
		{
			i++;
			continue;
		}
		equal_sign = ft_strchr(cmd->argv[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			key = cmd->argv[i];
			value = equal_sign + 1;
			ft_setenv_export(shell, key, value);
			*equal_sign = '=';
		}
		i++;
	}
	return (0);
}
