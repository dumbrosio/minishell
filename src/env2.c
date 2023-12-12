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

void	strcat_union(char *str, char *key, char *value)
{
	ft_strcat(str, key);
	ft_strcat(str, "=");
	ft_strcat(str, value);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return NULL;
	}
	else if (!ptr)
		return malloc(new_size);
	else if (new_size <= old_size)
		return ptr;
	else
	{
		new_ptr = malloc(new_size);
		if (new_ptr)
		{
			ft_memcpy(new_ptr, ptr, old_size);
			free(ptr);
		}
		return new_ptr;
	}
}

void ft_setenv_export(t_shell *shell, char *key, char *value)
{
	int i = 0;
	char **new_envp;
	char *new_entry = ft_strjoin(key, "=");
	char *temp = new_entry;

	new_entry = ft_strjoin(new_entry, value);
	free(temp);  // free the memory allocated in the previous ft_strjoin

	while (shell->envp[i] != NULL)
		{
			if (strncmp(shell->envp[i], key, strlen(key)) == 0 && shell->envp[i][strlen(key)] == '=')
			{
				// Variable exists, update its value
				free(shell->envp[i]);
				shell->envp[i] = new_entry;
				return;
			}
			i++;
		}

	new_envp = (char **)ft_realloc(shell->envp, sizeof(char *) * i, sizeof(char *) * (i + 2));
	if (new_envp == NULL)
	{
		// handle error
		return;
	}

	new_envp[i] = new_entry;
	new_envp[i + 1] = NULL;

	shell->envp = new_envp;
}

int	ft_setenv(t_shell *shell, char *key, char *value)
{
	char	**entry;
	char	*tmp;
	char	*new;

	new = (char *)malloc(sizeof(char) * (ft_strlen(key)+ ft_strlen(value) + 2));
	new[0] = 0;
	strcat_union(new, key, value);
	entry = ft_getenv_entry(shell->envp, key);
	if (!*entry)
		entry = ft_getenv_entry(shell->localenvp, key);
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
	//size_t	token_len;

	//token_len = ft_strlen(token);
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

	entry->key = ft_strndup(token, pos);
	entry->value = ft_strdup(sep + 1);
	// entry->key = (char *)malloc(sizeof(char) * (pos + 1));
	// entry->value = (char *)malloc(sizeof(char) * (token_len - pos));
	// ft_strncpy(entry->key, token, pos);
	// entry->key[pos] = '\0';
	// ft_strcpy(entry->value, token + pos + 1);
	// entry->value[token_len - pos - 1] = '\0';
	return (0);
}
char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (!dup)
		return NULL;

	for (i = 0; i < n && s[i] != '\0'; i++)
		dup[i] = s[i];

	dup[i] = '\0';

	return dup;
}
