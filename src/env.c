#include "minishell.h"

char	*ft_getenv(t_shell *shell, char *key)
{
	char	**entry;

	entry = get_env_entry(shell->envp, key);
	if (!*entry)
		entry = get_env_entry(shell->localenvp, key);
	if (!*entry)
		return (NULL);
	return (ft_strchr(*entry, '=') + 1);
}

char	**get_env_entry(char **env, char *key)
{
	int		i;
	char	**split_entry;

	i = 0;
	while (env[i])
	{
		split_entry = ft_split(env[i], '=');
		if (ft_strcmp(split_entry[0], key) == 0)
		{
			ft_clean(split_entry);
			return (&env[i]);
		}
		ft_clean(split_entry);
		i++;
	}
	return (&env[i]);
}
