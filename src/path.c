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

void	free_path(char **path)
{
	char	**runner;

	runner = path;
	while (*runner)
		free(*runner++);
	free(path);
}

char	*get_abs_path(char *cmd)
{
	char	*abs;
	char	**path;
	char	**runner;

	path = ft_split(getenv("PATH"), ':');
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
	return (cmd); /* tolto ft_strdup(cmd) creava leak*/
}
