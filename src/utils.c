#include "minishell.h"

char	**copy_environment(char **env)
{
	char	**environment;
	int		i;

	i = 0;
	while (env[i])
		i++;
	environment = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHELL", 5) == 0)
			environment[i] = ft_strdup("SHELL=./minishell");
		else
			environment[i] = ft_strdup(env[i]);
		i++;
	}
	environment[i] = NULL;
	return (environment);
}

void	print_error(t_shell *shell, char **str)
{
	int	len;

	while (*str)
	{
		len = ft_strlen(*str);
		write(shell->stderr_fd, *str, len);
		if (*(str + 1))
			write(shell->stderr_fd, " ", 1);
		str++;
	}
	write(shell->stderr_fd, "\n", 1);
}
