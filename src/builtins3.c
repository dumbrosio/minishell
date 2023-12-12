#include "minishell.h"

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
			continue ;
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

int	find_var_index(t_shell *shell, char *key)
{
	int i = 0;

	while (shell->envp[i] != NULL)
	{
		if (ft_strncmp(shell->envp[i], key, ft_strlen(key)) == 0 && shell->envp[i][ft_strlen(key)] == '=')
		{
			return i;
		}
		i++;
	}
	return (-1);
}
char	**create_new_envp(t_shell *shell, int var_index)
{
	int		i;
	int		j;
	int		envp_len;
	char	**new_envp;

	i = 0;
	j = 0;
	envp_len = 0;
	while (shell->envp[envp_len] != NULL)
		envp_len++;
	new_envp = (char **)malloc(sizeof(char *) * (envp_len + 1));
	if (new_envp == NULL)
		return (NULL);
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

int	check_exit_arg(int *arg, t_shell *shell, t_command *cmd, int *i)
{
	if (!ft_isdigit(cmd->argv[1][(*i)++]))
	{
		write(2, "minishell: exit: numeric argument required\n", 43);
		shell->exit_code = 2;
		*arg = 1;
		return (1);
	}
	return (0);
}

int	ft_exit(t_shell *shell, t_command *cmd)
{
	int	i;
	int	num_arg_error_found;

	num_arg_error_found = 0;
	write(2, "exit\n", 5);
	if (cmd->argc > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		shell->exit_code = 1;
	}
	else if (cmd->argc == 2)
	{
		i = 0;
		while (cmd->argv[1][i])
			if (check_exit_arg(&num_arg_error_found, shell, cmd, &i))
				break ;
		if (!num_arg_error_found)
			shell->exit_code = ft_atoi(cmd->argv[1]);
	}
	else
		shell->exit_code = 0;
	free(shell->command);
	clean_shell(shell);
	_exit(shell->exit_code);
}
