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
char** handle_null_path(char **path, char *copy)
{
	if (path == NULL)
	{
		free(copy);
		return (NULL);
	}
	return path;
}


char	*get_abs_path(t_shell *shell, char *command)
{
	char	**path;
	char	*absolute;
	char	**runner;
	char	*copy;

	expand_command(shell, command, &copy);
	get_envp_path(shell, &path);
	path = handle_null_path(path, copy);
	if (path == NULL)
		return (NULL);
	if (copy[0] == '/')
		return (copy);
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
void	clean_abs_path(char **absolute, char ***path, char **copy)
{
	if (*absolute)
		free(*absolute);
	free_path(*path);
	free(*copy);
	*copy = NULL;
}

