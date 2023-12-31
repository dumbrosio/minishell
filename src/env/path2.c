#include "minishell.h"

char	*build_abs_path(char *path, char *command)
{
	int		path_len;
	int		command_len;
	char	*absolute;

	path_len = ft_strlen(path);
	command_len = ft_strlen(command);
	absolute = (char *)malloc(sizeof(char) * (command_len + path_len + 2));
	ft_strncpy(absolute, path, path_len);
	ft_strncpy(absolute + path_len, "/", 1);
	ft_strncpy(absolute + path_len + 1, command, command_len);
	ft_strncpy(absolute + path_len + command_len + 1, "\0", 1);
	return (absolute);
}

void	expand_cmd_cycle(char **copy, char *curpath, int *i, int *j)
{
	while ((*copy)[*i])
	{
		if (!ft_strncmp((*copy) + *i, "./", 2))
			*i += 2;
		else if (!ft_strncmp((*copy) + *i, "../", 3))
		{
			if (curpath[*j - 1] == '/' && *j > 1)
				curpath[--(*j)] = 0;
			*i += 3;
			while (curpath[*j - 1] != '/' && *j > 1)
				curpath[(*j)--] = 0;
		}
		else
		{
			while ((*copy)[*i] && (*copy)[*i] != '/')
				curpath[(*j)++] = (*copy)[(*i)++];
			if ((*copy)[*i] == '/')
				curpath[(*j)++] = (*copy)[(*i)++];
		}
	}
	curpath[*j] = 0;
	free(*copy);
	*copy = ft_strdup(curpath);
}

void	expand_command(t_shell *shell, char *command, char **copy)
{
	char	curpath[4096];
	int		i;
	int		j;

	i = 0;
	j = 0;
	*copy = ft_strdup(command);
	if (!ft_strncmp((*copy) + i, "./", 2) || !ft_strncmp((*copy) + i, "../", 3))
	{
		ft_strcpy(curpath, ft_getenv(shell, "PWD"));
		ft_strcat(curpath, "/");
		j += ft_strlen(curpath);
	}
	expand_cmd_cycle(copy, curpath, &i, &j);
	curpath[j] = 0;
	free(*copy);
	*copy = ft_strdup(curpath);
}

void	free_path(char **path)
{
	char	**runner;

	runner = path;
	while (*runner)
		free(*runner++);
	free(path);
}
