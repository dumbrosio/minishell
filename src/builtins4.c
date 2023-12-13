#include "minishell.h"

int	ft_cd(t_shell *shell, t_command *cmd)
{
	char	*path;

	if (cmd->argc == 1)
	{
		path = ft_strdup(ft_getenv(shell, "HOME"));
		if (path == NULL)
		{
			print_error("Minishell: cd: HOME not set");
			shell->exit_code = 1;
			return (0);
		}
	}
	else
		path = set_new_path_cd(shell, cmd->argv[1]);
	if (chdir(path) == -1)
	{
		perror(cmd->argv[1]);
		shell->exit_code = 1;
		free(path);
		return (1);
	}
	update_pwd_cd(shell, path);
	free(path);
	return (0);
}

void	update_pwd_cd(t_shell *shell, char *path)
{
	char	*pwd;
	char	*oldpwd;
	char	*currentpwd;

	currentpwd = ft_getenv(shell, "PWD");
	oldpwd = ft_getenv(shell, "OLDPWD");
	if (oldpwd && *oldpwd && currentpwd && *currentpwd)
		ft_setenv_export(shell, "OLDPWD", currentpwd);
	else
	{
		if (currentpwd)
		{
			pwd = ft_strdup(currentpwd);
			ft_setenv_export(shell, "OLDPWD", pwd);
			free(pwd);
		}
	}
	if (path)
		ft_setenv_export(shell, "PWD", path);
}

char	*set_new_path_cd(t_shell *shell, char *str)
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
	return (build_new_path_cd(path, str));
}

char	*build_new_path_cd(char *curpath, char *str)
{
	char	path[4096];
	char	**splitted;
	int		i;

	ft_strcpy(path, curpath);
	splitted = ft_split(str, '/');
	i = 0;
	build_path_cd(splitted, i, path);
	clean_split(splitted);
	return (ft_strdup(path));
}

void	build_path_cd(char **splitted, int i, char *path)
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
