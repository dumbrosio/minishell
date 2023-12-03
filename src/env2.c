#include "minishell.h"

void	ft_add_entry(char ***env, char *entry)
{
	int		i;
	char	**tmp;

	i = 0;
	while ((*env)[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*env)[i])
	{
		tmp[i] = (*env)[i];
		i++;
	}
	tmp[i++] = ft_strdup(entry);
	tmp[i] = NULL;
	*env = tmp;
}

int	ft_setenv(t_shell *shell, char *key, char *value)
{
	char	**entry;
	char	*tmp;
	char	*new;

	new = (char *)malloc(sizeof(char) * (ft_strlen(key)+ ft_strlen(value) + 2));
	new[0] = 0;
	ft_strcat(new, key);
	ft_strcat(new, "=");
	ft_strcat(new, value);
	entry = ft_getenv_entry(shell->envp, key);
	if (!*entry)
		entry = ft_getenv_entry(shell->localenvp, key);
	if (*entry)
	{
		tmp = *entry;
		*entry = ft_strdup(new);
		free (new);
		free (tmp);
		return (0);
	}
	else
		ft_add_entry(&shell->localenvp, new);
	return (0);
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
