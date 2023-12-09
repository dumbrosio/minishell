#include "minishell.h"

void	ft_add_entry(char ***env, char *entry)
{
	int		i;
	char	**tmp;
	char	*entry_dup;

	entry_dup = ft_strdup(entry);

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
	tmp[i++] = entry_dup;
	tmp[i] = NULL;
	free(*env);
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
	{
		entry = ft_getenv_entry(shell->localenvp, key);
	}
	if (*entry)
	{
		tmp = *entry;
		*entry = ft_strdup(new);
		free (tmp);
		free (new);
		return (0);
	}
	else
	{
		ft_add_entry(&shell->localenvp, new);
		free(new);
	}
	return (0);
}

void	clean_entry(t_entry *entry)
{
	free(entry->entry);
	free(entry->key);
	free(entry->value);
}

int	ft_setenv_entry(char *token, t_entry *entry)
{
	char	*sep;
	int		pos;
	size_t	token_len;

	token_len = ft_strlen(token);
	if (token[0] == '=' || ft_isdigit(token[0]))
		return (1);
	entry->entry = ft_strdup(token);
	sep = ft_strchr(token, '=');
	if (!sep)
	{
		entry->key = ft_strdup(token);
		entry->value = NULL;
		clean_entry(entry);
		return (1);
	}
	pos = (int)(sep - token);
	entry->key = (char *)malloc(sizeof(char) * (pos + 1));
	entry->value = (char *)malloc(sizeof(char) * (token_len - pos));
	ft_strncpy(entry->key, token, pos);
	entry->key[pos] = '\0';
	ft_strcpy(entry->value, token + pos + 1);
	entry->value[token_len - pos - 1] = '\0';
	return (0);
}

