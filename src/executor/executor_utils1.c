#include "minishell.h"

void	init_command(t_command *cmd, pid_t *wpid, int makepipe, int *pipefdp)
{
	cmd->argc = 0;
	cmd->pfd[0] = -1;
	cmd->pfd[1] = -1;
	cmd->srcfd = STDIN_FILENO;
	cmd->dstfd = STDOUT_FILENO;
	reset_filename(cmd->srcfile);
	reset_filename(cmd->dstfile);
	cmd->makepipe = makepipe;
	cmd->wpid = wpid;
	cmd->pipefdp = pipefdp;
	cmd->tmp_arg[0] = 0;
}

int	switch_tokens(t_shell *shell, t_command *cmd)
{
	if (cmd->tk == T_WORD)
	{
		add_word_token(shell, cmd);
		return (1);
	}
	else if (cmd->tk == T_LESS)
	{
		if (set_red_in(shell, cmd))
			return (2);
		return (1);
	}
	else if (cmd->tk == T_HEREDOC)
	{
		if (set_heredoc(shell, cmd))
			return (2);
		return (1);
	}
	else if (cmd->tk == T_GREAT || cmd->tk == T_APPEND)
	{
		if (set_red_out(shell, cmd))
			return (2);
		return (1);
	}
	return (0);
}

void	add_word_token(t_shell *shell, t_command *cmd)
{
	if (cmd->argc >= MAXARG - 1)
	{
		print_error("Too many args");
		return ;
	}
	if (shell->expand)
		expand(shell);
	ft_strcat(cmd->tmp_arg, shell->buffer);
	if (shell->token_error != 1)
	{
		copy_tmp_arg(cmd);
	}
}

int	set_red_in(t_shell *shell, t_command *cmd)
{
	char	*abs_path;
	char	buffer[4096];

	buffer[0] = 0;
	if (get_token(shell, cmd) != T_WORD)
		return (write_error(shell, "<"));
	if (shell->expand)
		expand(shell);
	if (shell->buffer[0] != '/')
		ft_strcat(buffer, "./");
	ft_strcat(buffer, shell->buffer);
	abs_path = get_abs_path(shell, buffer);
	if (access(abs_path, F_OK) != 0)
	{
		write(2, "minishell: ", 11);
		write(2, shell->buffer, ft_strlen(shell->buffer));
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	cmd->srcfd = -1;
	ft_strcpy(cmd->srcfile, shell->buffer);
	return (0);
}

int	set_red_out(t_shell *shell, t_command *cmd)
{
	int	flags;

	if (get_token(shell, cmd) != T_WORD)
	{
		if (cmd->tk == T_GREAT)
			return (write_error(shell, ">"));
		else if (cmd->tk == T_APPEND)
			return (write_error(shell, ">>"));
	}
	if (shell->expand)
		expand(shell);
	flags = O_CREAT;
	if (cmd->tk == T_APPEND)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	close(open(shell->buffer, flags, 0644));
	cmd->dstfd = -1;
	ft_strcpy(cmd->dstfile, shell->buffer);
	cmd->append = (cmd->tk == T_APPEND);
	return (0);
}
