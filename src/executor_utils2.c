#include "minishell.h"

int	is_terminal_token(t_token token)
{
	if (token == T_PIPE || token == T_NL)
		return (1);
	return (0);
}

void	redirect(t_command *cmd)
{
	if (cmd->srcfile[0] != '\0')
		cmd->srcfd = open(cmd->srcfile, O_RDONLY, 0);
	dup2(cmd->srcfd, STDIN_FILENO);
	if (cmd->srcfd != STDIN_FILENO)
		close(cmd->srcfd);
	if (cmd->dstfile[0] != '\0')
		set_file(cmd);
	dup2(cmd->dstfd, STDOUT_FILENO);
	if (cmd->dstfd != STDOUT_FILENO)
		close(cmd->dstfd);
	return ;
}

void	free_command_args(t_command *cmd)
{
	while (--cmd->argc >= 0)
		free(cmd->argv[cmd->argc]);
}

int	wait_command(t_shell *shell, pid_t pid)
{
	pid_t	wpid;
	int		status;

	wpid = waitpid(-1, &status, 0);
	set_exit_status(shell, status);
	while (wpid != pid)
	{
		wpid = waitpid(-1, &status, 0);
		set_exit_status(shell, status);
	}
	while (waitpid(-1, &status, WUNTRACED) != -1);
	set_exit_status(shell, status);
	return (1);
}

void	set_pipe(t_command *cmd)
{
	pipe(cmd->pfd);
	*cmd->pipefdp = cmd->pfd[1];
	cmd->srcfd = cmd->pfd[0];
}
