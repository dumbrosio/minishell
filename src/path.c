#include "minishell.h"

char	*create_abs_path(char *path, char *cmd)
{
	int		path_len;
	int		cmd_len;
	char	*abs;

	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	abs = (char *)malloc(sizeof(char) * (cmd_len + path_len + 2));
	ft_strncpy(abs, path, path_len);
	ft_strncpy(abs + path_len, "/", 1);
	ft_strncpy(abs + path_len + 1, cmd, cmd_len);
	ft_strncpy(abs + path_len + cmd_len + 1, "\0", 1);
	return (abs);
}

char	*get_abs_path(t_shell *shell, char *cmd)
{
	char	*abs;
	char	**path;
	char	**runner;

	path = ft_split(ft_getenv(shell, "PATH"), ':');
	if (path == NULL)
		return (ft_strdup(cmd));
	runner = path;
	while (*runner)
	{
		abs = create_abs_path(*runner, cmd);
		if (access(abs, X_OK) == 0)
		{
			free_path(path);
			return (abs);
		}
		free(abs);
		abs = NULL;
		runner++;
	}
	if (abs)
		free(abs);
	free_path(path);
	return (cmd);
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
