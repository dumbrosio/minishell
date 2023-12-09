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
int	export_core(t_shell *shell, t_command *cmd)
{
	int 	i;
	char	**env_entry;
	t_entry	entry;

	i = 1;
	while (i < cmd->argc)
	{
		if (ft_setenv_entry(cmd->argv[i], &entry))
			return (0);
		if (entry.value)
		{
			ft_setenv(shell, entry.key, entry.value);
			env_entry = ft_getenv_entry(shell->localenvp, entry.key);
			if (env_entry && *env_entry)
			{
				ft_add_entry(&shell->envp, *env_entry);
				pop_env_entry(&shell->localenvp, entry.key);
			}
		}
		clean_split(env_entry);
		clean_entry(&entry);
		i++;
	}
return (0);
}

int	ft_unset(t_shell *shell, t_command *cmd)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (cmd->argc == 1)
		return (1);
	else
	{
		while (i < cmd->argc)
		{
			if (pop_env_entry(&shell->envp, cmd->argv[i]))
			{
				i++;
				continue ;
			}
			if (pop_env_entry(&shell->localenvp, cmd->argv[i++]))
				continue ;
			ret++;
		}
		return (ret);
	}
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
