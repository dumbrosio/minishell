#include "minishell.h"

char	**copy_env(char **env)
{
	char	**environ;
	int		i;

	i = 0;
	while (env[i])
		i++;
	environ = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHELL", 5) == 0)
			environ[i] = ft_strdup("SHELL=./mini");
		else
			environ[i] = ft_strdup(env[i]);
		i++;
	}
	environ[i] = NULL;
	return (environ);
}

void	print_error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
}

void	ft_clean(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

int	is_space(int c)
{
	return (c == 32 || c == 9 || c == 10);
}

int	is_empty_str(char *str)
{
	while (*str)
	{
		if (!is_space((unsigned char)*str))
			return (1);
		str++;
	}
	return (0);
}
