#include "minishell.h"

void	add_last_exit(t_shell *shell, int *i, int *j)
{
	char	*buffer;
	char	*value;
	int		len;

	buffer = shell->buffer;
	(*i) = *i + 1;
	if (shell->buffer[*i] == '?')
		value = ft_itoa(shell->exit_code);
	else
		value = ft_itoa(shell->main_pid);
	len = 0;
	while (value[len])
		len++;
	(*i) += len;
	ft_memcpy(buffer + *j, value, ft_strlen(value));
	(*j) += ft_strlen(value);
	ft_memcpy(buffer + *j, "\0", 1);
	(*j)++;
	free(value);
}

void	add_expanded_value(t_shell *shell, char *buffer_copy, int *i, int *j)
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
	char	*buffer_copy;
	int		i;
	int		j;

	buffer_copy = ft_strdup(shell->buffer);
	i = 0;
	j = 0;
	while (buffer_copy[i])
	{
		if (buffer_copy[i] != '$')
			shell->buffer[j++] = buffer_copy[i++];
		else if (buffer_copy[i + 1] == ' ' || buffer_copy[i + 1] == 0)
			shell->buffer[j++] = buffer_copy[i++];
		else if (buffer_copy[i + 1] == '?' || buffer_copy[i + 1] == '$')
			add_last_exit(shell, &i, &j);
		else
			add_expanded_value(shell, buffer_copy, &i, &j);
	}
	shell->buffer[j] = '\0';
	free(buffer_copy);
}
