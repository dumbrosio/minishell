#include "minishell.h"

void	add_expanded_env_var(t_shell *shell, char *buffer_copy, int *i, int *j)
{
	char	*buffer;
	char	*key;
	char	*env_var_value;
	int		key_len;

	buffer = shell->buffer;
	(*i) = *i + 1;
	key_len = 0;
	while (ft_isalnum(buffer_copy[*i + key_len]))
		key_len++;
	key = ft_substr(buffer_copy, *i, key_len);
	(*i) += key_len;
	env_var_value = ft_getenv(shell, key);
	if (!env_var_value)
		env_var_value = "";
	ft_memcpy(buffer + *j, env_var_value, ft_strlen(env_var_value));
	(*j) += ft_strlen(env_var_value);
	free(key);
}

void	expand(t_shell *shell)
{
	char *buffer_copy;
	int i;
	int j;

	buffer_copy = ft_strdup(shell->buffer);
	i = 0;
	j = 0;
	while (buffer_copy[i])
	{
		if (buffer_copy[i] != '$')
			shell->buffer[j++] = buffer_copy[i++];
		else
			add_expanded_env_var(shell, buffer_copy, &i, &j);
	}
	shell->buffer[j] = '\0';
}