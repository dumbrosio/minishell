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

void	print_error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
}

void	clean_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

int	write_error(t_shell *shell)
{
	write(2, "minishell: ", 11);
	write(2, "errore di sintassi vicino al token non atteso \"", 47);
	write(2, shell->buffer, ft_strlen(shell->buffer));
	write(2, "\"\n", 2);
	return (1);
}
