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

int	ft_export(t_shell *shell, t_command *cmd)
{
	if (cmd->argc == 1)
		print_export_entry(shell);
	else
		export_core(shell, cmd);
	return (0);
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
int	find_var_index(t_shell *shell, char *key)
{
	int i = 0;

	while (shell->envp[i] != NULL)
	{
		if (ft_strncmp(shell->envp[i], key, ft_strlen(key)) == 0 && shell->envp[i][ft_strlen(key)] == '=')
		{
			//free(shell->envp[i]);
			return i;
		}
		i++;
	}
	return -1;
}
char	**create_new_envp(t_shell *shell, int var_index)
{
	int i = 0;
	int j = 0;
	int envp_len = 0;
	char **new_envp;

	while (shell->envp[envp_len] != NULL)
		envp_len++;
	new_envp = (char **)malloc(sizeof(char *) * (envp_len + 1));
	if (new_envp == NULL)
	{
		return NULL;
	}
	while (shell->envp[i] != NULL)
	{
		if (i != var_index)
		{
			new_envp[j] = shell->envp[i];
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	return new_envp;
}

int	ft_unset(t_shell *shell, t_command *cmd)
{
	int		var_index;
	int		arg;
	char	**new_envp;

	arg = 1;
	while (arg < cmd->argc)
	{
		var_index = find_var_index(shell, cmd->argv[arg]);
		if (var_index == -1)
		{
			arg++;
			continue;
		}
		 new_envp = create_new_envp(shell, var_index);
		if (new_envp == NULL)
			return (1);

		free(shell->envp[var_index]);
		free(shell->envp);
		shell->envp = new_envp;
		arg++;
    }
	return (0);
}

int	ft_cd(t_shell *shell, t_command *cmd)
{
	char	*path;

	if (cmd->argc == 1)
	{
		path = ft_strdup(ft_getenv(shell, "HOME"));
		if (path == NULL)
			path = ft_strdup(ft_getenv(shell, "PWD"));
	}
	else
		path = set_new_path(shell, cmd->argv[1]);
	if (chdir(path) == -1)
	{
		perror(cmd->argv[1]);
		free(path);
		return (1);
	}
	update_pwd(shell, path);
	free(path);
	return (0);
}
