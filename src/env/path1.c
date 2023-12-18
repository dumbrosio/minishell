#include "minishell.h"

void	get_envp_path(t_shell *shell, char ***path)
{
	char	*path_envp;

	path_envp = ft_getenv(shell, "PATH");
	if (!path_envp)
	{
		*path = NULL;
		shell->unset_path = 1;
	}
	else
	{
		*path = ft_split(path_envp, ':');
		shell->unset_path = 0;
	}
}

int	check_file(char *absolute, char ***path, char **copy)
{
	if (access(absolute, F_OK) == 0)
	{
		free_path(*path);
		free(*copy);
		return (1);
	}
	return (0);
}

char	*handle_absolute_path(char *copy)
{
	if (access(copy, F_OK) == 0)
		return (copy);
	else
	{
		free(copy);
		return (NULL);
	}
}

char	*handle_relative_path(t_shell *shell, char *copy)
{
	char	**path;
	char	*absolute;
	char	**runner;

	get_envp_path(shell, &path);
	path = handle_null_path(path, copy);
	if (path == NULL)
		return (NULL);
	runner = path;
	while (runner && *runner)
	{
		absolute = build_abs_path(*runner, copy);
		if (check_file(absolute, &path, &copy))
			return (absolute);
		free(absolute);
		absolute = NULL;
		runner++;
	}
	clean_abs_path(&absolute, &path, &copy);
	return (NULL);
}

char	*get_abs_path(t_shell *shell, char *command)
{
	char	*copy;

	expand_command(shell, command, &copy);
	if (copy[0] == '/')
		return (handle_absolute_path(copy));
	else
		return (handle_relative_path(shell, copy));
}
