#include "minishell.h"

void	ft_add_entry(char ***env, char *entry)
{
	int		i;
	char	**tmp;

	//printf("%s\n",entry);
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
	//int i = 0;

	printf("key %s value %s\n", key,value);
	printf("len key %ld len value %ld\n",ft_strlen(key) , ft_strlen(value));
	printf("malloc size %ld\n",(ft_strlen(key)+ ft_strlen(value) + 2) );

	new = (char *)malloc(sizeof(char) * (ft_strlen(key)+ ft_strlen(value) + 2));
	new[0] = 0;
	ft_strcat(new, key);
	ft_strcat(new, "=");
	ft_strcat(new, value);
	entry = ft_getenv_entry(shell->envp, key);
	// while (entry[i])
	// 	{
	// 		printf("printf entry %s\n",entry[i]);
	// 		i++;
	// 	}
	if (!*entry)
	{
		entry = ft_getenv_entry(shell->localenvp, key);
		printf("if not entry\n");
	}
	if (*entry)
	{
		printf("if entry\n");
		tmp = *entry;
		*entry = ft_strdup(new);
		free (new);
		free (tmp);
		return (0);
	}
	else
	{
		printf("add entry locale\n");
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
	{
		printf("esco token numerico\n");
		return (1);
	}

	entry->entry = ft_strdup(token);
	sep = ft_strchr(token, '=');
	if (!sep)
	{
		printf("not sep\n");
		//entry->entry = ft_strdup(token);
		entry->key = ft_strdup(token);
		entry->value = NULL;
		clean_entry(entry);
		return (1);
	}
	printf("vado avanti esistono chiave e valore\n");
	pos = (int)(sep - token);
	printf("pos fine key %d\n",pos + 1);
	entry->key = (char *)malloc(sizeof(char) * (pos + 1));
	printf("token_len - pos fine value %ld\n", (token_len - pos));
	entry->value = (char *)malloc(sizeof(char) * (token_len - pos));
	ft_strncpy(entry->key, token, pos);
	ft_strcpy(entry->value, token + pos + 1);
	printf("copio da %d in poi\n", ( pos + 1));
	printf("finisco setenventry \n");
	return (0);
}
