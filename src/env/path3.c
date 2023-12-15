#include "minishell.h"

void	clean_abs_path(char **absolute, char ***path, char **copy)
{
	if (*absolute)
		free(*absolute);
	free_path(*path);
	free(*copy);
	*copy = NULL;
}

char	**handle_null_path(char **path, char *copy)
{
	if (path == NULL)
	{
		free(copy);
		return (NULL);
	}
	return (path);
}
