#include "minishell.h"

t_token	command(t_shell *shell, pid_t *wpid, int makepipe, int *pipefdp)
{
	t_command	cmd;
	int			result;

	init_command(&cmd, wpid, makepipe, pipefdp);
	while (42)
	{
		cmd.tk = get_token(shell, &cmd);
		result = switch_tokens(shell, &cmd);
		if (result == 2)
			break ;
		else if (result == 1)
			continue ;
		if (is_terminal_tk(cmd.tk))
		{
			result = cmd_special(shell, &cmd);
			if (result)
				break ;
			return (cmd.term);
		}
		free_command_args(&cmd);
		return (T_ERROR);
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
			print_error_2(shell, "Piping error");
			return (1);
		}
		cmd->term = command(shell, cmd->wpid, 1, &cmd->dstfd);
		if (cmd->term == T_ERROR)
			return (-1);
	}
	else
		cmd->term = cmd->tk;
	if (cmd->makepipe)
		set_pipe(cmd);
	cmd->pid = invoke(shell, cmd);
	if (cmd->tk != T_PIPE)
		*cmd->wpid = cmd->pid;
	if (cmd->argc == 0 && (cmd->tk != T_NL || cmd->srcfd > 1))
		print_error_2(shell, "Syntax error");
	free_command_args(cmd);
	return (0);
}

pid_t	invoke(t_shell *shell, t_command *cmd)
{
	pid_t	pid;
	char	*abs_path;

	if (cmd->argc == 0 || other_builtins(shell, cmd))
		return (0);
	else
	{
		abs_path = get_abs_path(shell, cmd->argv[0]);
		pid = fork();
		if (pid == -1)
		{
			print_error("Can't create new process");
			return (0);
		}
		if (pid == 0)
			invoke_child(shell, cmd, abs_path);
	}
	free(abs_path);
	if (cmd->srcfd > STDOUT_FILENO)
		close(cmd->srcfd);
	if (cmd->dstfd > STDOUT_FILENO)
		close(cmd->dstfd);
	return (pid);
}

void	invoke_child(t_shell *shell, t_command *cmd, char *abs_path)
{
	if (cmd->pfd[1] != -1)
		close(cmd->pfd[1]);
	redirect(cmd);
	if (is_builtin(cmd))
		exit(exec_builtin(shell, cmd));
	if (abs_path == NULL)
	{
		write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
		if (shell->unset_path)
			write(2, ": No such file or directory\n", 28);
		else
			write(2, ": command not found\n", 20);
		exit(127);
	}
	if (access(abs_path, X_OK) != 0)
	{
		write(2, "minishell: ", 11);
		write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(2, ": Permission denied\n", 20);
		exit(126);
	}
	execve(abs_path, cmd->argv, shell->envp);
	perror(cmd->argv[0]);
	exit(EXIT_FAILURE);
}
