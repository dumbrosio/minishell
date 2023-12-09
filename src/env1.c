#include "minishell.h"

char	*ft_getenv(t_shell *shell, char *key)
{
	char	**entry;

	entry = ft_getenv_entry(shell->envp, key);
	if (!*entry)
		entry = ft_getenv_entry(shell->localenvp, key);
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

int	pop_env_entry(char ***env, char *key)
{
	int		i;
	int		j;
	char	**tmp;
	char	**splitted_entries;

	i = 0;
	while ((*env)[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	j = 0;
	while ((*env)[i])
	{
		splitted_entries = ft_split((*env)[i], '=');
		if (ft_strcmp(splitted_entries[0], key))
			tmp[j++] = (*env)[i++];
		else
			i++;
		clean_split(splitted_entries);
	}
	tmp[j] = NULL;
	*env = tmp;
	return (i == (j + 1));
}
