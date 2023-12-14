#include "minishell.h"

int	ft_export(t_shell *shell, t_command *cmd)
{
	if (cmd->argc == 1)
		print_export_entry(shell);
	else
		export_core(shell, cmd);
	return (0);
}

void	print_export_var(char *env_var)
{
	char	*key;
	char	*value;

	key = env_var;
	value = ft_strchr(key, '=');
	if (value != NULL)
	{
		*value = '\0';
		value++;
		printf("declare -x %s=\"%s\"\n", key, value);
	}
	else
	{
		printf("declare -x %s\n", key);
	}
}

int	print_export_entry(t_shell *shell)
{
	int		i;
	char	**copied_envp;
	char	*env_var;

	i = 0;
	copied_envp = shell->envp;
	bubble_sort(copied_envp, ft_envp_len(copied_envp));
	while (copied_envp[i] != NULL )
	{
		env_var = ft_strdup(copied_envp[i]);
		print_export_var(env_var);
		i++;
		free(env_var);
	}
	return (1);
}

void	handle_export_arg(t_shell *shell, char *arg)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		if (*(equal_sign + 1) == '\0')
		{
			ft_setenv(shell, arg, "");
		}
		else
		{
			*equal_sign = '\0';
			key = arg;
			value = equal_sign + 1;
			ft_setenv(shell, key, value);
			*equal_sign = '=';
		}
	}
	else
	{
		ft_setenv(shell, arg, "");
	}
}

int	export_core(t_shell *shell, t_command *cmd)
{
	int	i;

	i = 1;
	while (i < cmd->argc)
	{
		if (export_checker(cmd, i))
		{
			export_error(shell, cmd->argv[i], &i);
			continue ;
		}
		handle_export_arg(shell, cmd->argv[i]);
		i++;
	}
	return (0);
}
