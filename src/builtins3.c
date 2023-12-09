#include "minishell.h"

int	ft_exit(t_shell *shell)
{
	free(shell->command);
	clean_shell(shell);
	_exit(EXIT_SUCCESS);
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

void	update_pwd(t_shell *shell, char *path)
{
	char	*pwd;
	char	*oldpwd;

	if (*ft_getenv_entry(shell->envp, "OLDPWD"))
		ft_setenv(shell, "OLDPWD", ft_getenv(shell, "PWD"));
	else
	{
		pwd = ft_strdup(ft_getenv(shell, "PWD"));
		oldpwd = (char *)malloc(sizeof(char) * ft_strlen(pwd) + 8);
		ft_strcat(oldpwd, "OLDPWD=");
		ft_strcat(oldpwd, pwd);
		ft_add_entry(&shell->envp, oldpwd);
		free(pwd);
		free(oldpwd);
	}
	ft_setenv(shell, "PWD", path);
}
