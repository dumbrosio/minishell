#include "minishell.h"

t_token	command(t_shell *shell, pid_t *wpid, int makepipe, int *pipefdp)
{
	t_command	cmd;
	int			result;

	init_command(&cmd, wpid, makepipe, pipefdp);
	while (1)
	{
		cmd.tk = get_token(shell);
		result = switch_simple_tokens(shell, &cmd);
		if (result == 2)
			break ;
		else if (result == 1)
			continue ;
		if (is_terminal_token(cmd.tk))
		{
			result = cmd_special(shell, &cmd);
			if (result)
				break ;
			return (cmd.term);
		}
		exit(EXIT_SUCCESS);
	}
	return (T_ERROR);
}

int	cmd_special(t_shell *shell, t_command *cmd)
{
	cmd->argv[cmd->argc] = NULL;
	if (cmd->tk == T_PIPE)
	{
		if (cmd->dstfd != STDOUT_FILENO)
		{
			print_error("> or >> conflicts with |");
			return (1);
		}
		cmd->term = command(shell, cmd->wpid, 1, &cmd->dstfd);
		if (cmd->term == T_ERROR)
			return (-1);
	}
	else
		cmd->term = cmd->tk;
	if (cmd->makepipe)
		setpipe(cmd);
	cmd->pid = invoke(shell, cmd);
	if (cmd->tk != T_PIPE)
		*cmd->wpid = cmd->pid;
	if (cmd->argc == 0 && (cmd->tk != T_NL || cmd->srcfd > 1))
		print_error("Missing command");
	free_command_args(cmd);
	return (0);
}

pid_t	invoke(t_shell *shell, t_command *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_error("Can't create new process");
		return (0);
	}
	if (pid == 0)
		invoke_child(shell, cmd);
	if (cmd->srcfd > STDOUT_FILENO)
		close(cmd->srcfd);
	if (cmd->dstfd > STDOUT_FILENO)
		close(cmd->dstfd);
	return (pid);
}

void	invoke_child(t_shell *shell, t_command *cmd)
{
	if (cmd->pfd[1] != -1)
		close(cmd->pfd[1]);
	redirect(cmd);
	if (is_builtin(cmd))
		_exit(exec_builtin(shell, cmd));
	execve(get_abs_path(shell, cmd->argv[0]), cmd->argv, shell->envp);
	perror(cmd->argv[0]);
	_exit(EXIT_FAILURE);
}
