#include "minishell.h"

char	*ft_getenv(t_shell *shell, char *key)
{
	char	**entry;

	entry = ft_getenv_entry(shell->envp, key);
	if (!*entry)
		return (NULL);
	return (ft_strchr(*entry, '=') + 1);
}

char	**ft_getenv_entry(char **env, char *key)
{
	int		i;
	char	**splitted_entry;

	i = 0;
	while (env[i])
	{
		splitted_entry = ft_split(env[i], '=');
		if (ft_strcmp(splitted_entry[0], key) == 0)
		{
			clean_split(splitted_entry);
			return (&env[i]);
		}
		clean_split(splitted_entry);
		i++;
	}
	return (&env[i]);
}

char	*create_env_entry(char *key, char *value)
{
	char	*new_entry;
	char	*temp;

	if (value && *value)
	{
		new_entry = ft_strjoin(key, "=");
		temp = new_entry;
		new_entry = ft_strjoin(new_entry, value);
		free(temp);
	}
	else
	{
		new_entry = ft_strdup(key);
	}
	return (new_entry);
}

void	ft_setenv(t_shell *shell, char *key, char *value)
{
	int		i;
	char	**new_envp;
	char	*new_entry;

	i = 0;
	new_entry = create_env_entry(key, value);
	while (shell->envp[++i] != NULL)
	{
		if (ft_strncmp(shell->envp[i], key, ft_strlen(key)) == 0 \
		&& (shell->envp[i][ft_strlen(key)] == '=' \
		|| shell->envp[i][ft_strlen(key)] == '\0'))
		{
			free(shell->envp[i]);
			shell->envp[i] = new_entry;
			return ;
		}
	}
	new_envp = (char **)ft_realloc(shell->envp, sizeof(char *) * i, \
	sizeof(char *) * (i + 2));
	new_envp[i] = new_entry;
	new_envp[i + 1] = NULL;
	shell->envp = new_envp;
}
