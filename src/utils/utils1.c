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

void	print_error_2(t_shell *shell, char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	shell->exit_code = 2;
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

int	write_error(t_shell *shell, char *token)
{
	(void)shell;
	write(2, "minishell: ", 11);
	write(2, "syntax error near unexpected token '", 35);
	write(2, token, strlen(token));
	write(2, "'\n", 2);
	return (1);
}
// int	write_error(t_shell *shell, char *token)
// {
// 	(void)shell;
// 	write(2, "minishell: ", 11);
// 	write(2, "syntax error near unexpected token '", 35);
// 	if (shell->buffer[0] == '\0')
// 		write(2, "newline", 7);
// 	else
// 		write(2, token, strlen(token));
// 	write(2, "'\n", 2);
// 	return (1);
// }
