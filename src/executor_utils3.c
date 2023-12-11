#include "minishell.h"

void	reset_filename(char *filename)
{
	int	i;

	i = 0;
	while (i < MAXFNAME)
		filename[i++] = 0;
}

void	set_file(t_command *cmd)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (cmd->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	cmd->dstfd = open(cmd->dstfile, flags, 0644);
}

void	set_exit_status(t_shell *shell, int status)
{
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else if (errno == 2)
		shell->exit_code = 130;
}
