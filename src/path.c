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

char	*get_abs_path(t_shell *shell, char *command)
{
	char	**path;
	char	*absolute;
	char	**runner;
	char	*copy;

	expand_command(shell, command, &copy);
	get_envp_path(shell, &path);
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
}

char	*set_new_path(t_shell *shell, char *str)
{
	char	path[4096];

	if (str[0] != '/')
		ft_strcpy(path, ft_getenv(shell, "PWD"));
	else
		ft_strcpy(path, "");
	while (str[ft_strlen(str) - 1] == '/')
		str[ft_strlen(str) - 1] = 0;
	while (str[0] == '/')
		str++;
	return (build_new_path(path, str));
}

char	*build_new_path(char *curpath, char *str)
{
	char	path[4096];
	char	**splitted;
	int		i;

	ft_strcpy(path, curpath);
	splitted = ft_split(str, '/');
	i = 0;
	build_path(splitted, i, path);
	clean_split(splitted);
	return (ft_strdup(path));
}

void	build_path(char **splitted, int i, char *path)
{
	while (splitted[i])
	{
		if (ft_strcmp(".", splitted[i]) == 0)
		{
			i++;
			continue ;
		}
		else if (ft_strcmp("..", splitted[i]) == 0)
		{
			if (ft_strrchr(path, '/') && ft_strrchr(path, '/') != path)
				*ft_strrchr(path, '/') = 0;
			else
				ft_strcpy(path, "/");
			i++;
			continue ;
		}
		if (ft_strcmp("/", path) != 0)
			ft_strcat(path, "/");
		ft_strcat(path, splitted[i++]);
	}
}
